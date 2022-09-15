#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"
#include "device_physical.h"
#include "props.h"
#include "queues.h"
#include "context.h"

#define VERSION_ARGS(version) \
	VK_API_VERSION_MAJOR(version), \
	VK_API_VERSION_MINOR(version), \
	VK_API_VERSION_PATCH(version)

using FeatureType = decltype(vk::PhysicalDeviceFeatures::geometryShader);

template<typename T>
constexpr std::string_view feature_index_name(size_t index) = delete;

#define FeatureOffset(feature) offsetof(vk::PhysicalDeviceFeatures, feature)
template<>
constexpr std::string_view feature_index_name<vk::PhysicalDeviceFeatures>(size_t index) {
	switch (index * sizeof(FeatureType)) {
		case FeatureOffset(geometryShader):	return "Geometry Shader";
		case FeatureOffset(samplerAnisotropy):	return "Sampler Anisotropy";
	default:
		nova_bark_warn("Unknown Case [Feature Name]: {}", index);
		return "Unknown Feature";
	}
};

namespace Nova::abyss::nvk {

	void log_device_info(vk::PhysicalDevice& device, const prop::Setup& properties) {
		if constexpr (Nova::bark::def::info) {
			auto p = device.getProperties();
			auto memory = device.getMemoryProperties();

			struct {
				std::stringstream local{}, shared{};
			} mem_info;

			for (auto&& heap : std::views::counted(memory.memoryHeaps.begin(), memory.memoryHeapCount)) {
				auto& stream = heap.flags & vk::MemoryHeapFlagBits::eDeviceLocal ? mem_info.local : mem_info.shared;
				stream << "\n\t\t" << heap.size / 1024.f / 1024.f / 1024.f << " GiB";
			}

			for (auto stream : { &mem_info.local, &mem_info.shared }) {
				if (stream->tellp() == 0)
					*stream << "\n\t\t0 B";
			}

			struct {
				std::stringstream extensions{}, features{};
				size_t feature_count = 0;
			} extras;

			for (auto&& ext : properties.extensions_device) {
				extras.extensions << "\n\t\t" << ext;
			}
			for (size_t feature_index = 0; feature_index < sizeof(vk::PhysicalDeviceFeatures) / sizeof(FeatureType); ++feature_index) {
				if (*(reinterpret_cast<const FeatureType*>(&properties.device_features) + feature_index) == VK_TRUE) {
					++extras.feature_count;
					extras.features << "\n\t\t" << feature_index_name<vk::PhysicalDeviceFeatures>(feature_index);
				}
			}

			nova_bark_info("VK Device:"
					"\n\tName: {}" "\n\tType: {}"
					"\n\tAPI Version: {}.{}.{}" "\n\tDriver Version: {}.{}.{}"
					"\n\tLocal Memory:{}" "\n\tShared Memory:{}"
					"\n\tExtensions: {}{}"
					"\n\tFeatures: {}{}",
				p.deviceName, p.deviceType,
				VERSION_ARGS(p.apiVersion), VERSION_ARGS(p.driverVersion),
				mem_info.local.str(), mem_info.shared.str(),
				properties.extensions_device.size(),
				extras.extensions.str(),
				extras.feature_count,
				extras.features.str()
			);
		}
	}

	inline static constexpr size_t REJECTION = 0;
	// Log reason for rejecting a device
	// Feature is not supported
	size_t reject(const vk::PhysicalDeviceFeatures&, size_t index) {
		nova_bark_trace("\tRejection [Feature]: Not supported! {}", index);
		return REJECTION;
	}
	// Device Extension is not supported
	size_t reject(const cstr& extension) {
		nova_bark_trace("\tRejection [Extention]: Not supported! {}", extension);
		return REJECTION;
	}
	// Queue Type is not supported
	size_t reject(const Q::Type& type) {
		nova_bark_trace("\tRejection [Queue Family]: Not supported! {}", type);
		return REJECTION;
	}
	// Surface Format is not supported
	size_t reject(const vk::SurfaceFormatKHR& surface_format) {
		nova_bark_trace("\tRejection [Surface Format]: Not supported! Format: {} Colour Space: {}",
			static_cast<std::underlying_type_t<decltype(surface_format.format)>>(surface_format.format),
			static_cast<std::underlying_type_t<decltype(surface_format.colorSpace)>>(surface_format.colorSpace)
		);
		return REJECTION;
	}
	// Present Mode is not supported
	size_t reject(const vk::PresentModeKHR& present_mode) {
		nova_bark_trace("\tRejection [Present Mode]: Not supported! {}", present_mode);
		return REJECTION;
	}

	// Selects an avalible physical device
	// TODO: Support physical device groups
	vk::PhysicalDevice PhysicalBuilder::select_device(Device::Info& info) {
		nova_bark_init("VK Physical Device");
		auto devices = nova_abyss_api->instance.self.enumeratePhysicalDevices();
		nova_bark_trace("Selecting from Physical Devices: {}", devices.size());
		nova_assert(!devices.empty(), "No Vulkan Devices found on the system!");

		// Obtain only suitable devices
		rank_devices(devices);
		nova_assert(device_ranks.size() > 0, "No devices match the requirements");

		// Find the highest ranked device
		std::ranges::stable_sort(device_ranks, std::ranges::greater{}, &decltype(device_ranks)::value_type::score);
		auto& best = device_ranks.back();
		nova_assert(best.score > REJECTION, "No devices match the requirements");

		log_device_info(best.device, properties);

		info = best.info;
		return best.device;
	}

	// Filter out the devices which do not meet the engine requirements
	void PhysicalBuilder::rank_devices(std::vector<vk::PhysicalDevice>& devices) {
		device_ranks.reserve(devices.size());
		for (auto idx = 0; idx < devices.size(); idx++) {
			auto&& device = devices[idx];
			nova_bark_trace("Device [{0:>0{1}d}/{1:}]: {2:}", idx + 1, devices.size(), device.getProperties().deviceName);
			auto& score = device_ranks.emplace_back(
				device
			).score;
			score = score_device_suitablility(device);
			nova_bark_trace("\tRank: #{}", score);
		}
	}

	// Rank the device (higher is better)
	PhysicalBuilder::Rank::Score PhysicalBuilder::score_device_suitablility(vk::PhysicalDevice& device) {
		Rank::Score score = REJECTION;
		using This = std::remove_cvref_t<decltype(*this)>;
		// Scoring Functions
		for (auto func : { &This::test_features, &This::test_extensions, &This::swapchain_surface_format, &This::swapchain_present_mode, &This::queue_families, &This::rank_type }) {
			if (auto scr = std::invoke(func, this, device); scr == REJECTION) return REJECTION;
			else score += scr;
		}
		return score;
	}

	// Ensure the device has every feature requrested
	PhysicalBuilder::Rank::Score PhysicalBuilder::test_features(vk::PhysicalDevice& device) {
		Rank::Score score = 1;
		auto features = device.getFeatures();

		auto accessor = [&](vk::PhysicalDeviceFeatures features, size_t index) {
			return *(reinterpret_cast<FeatureType*>(&features) + index);
		};

		// TODO: Let features be optional but improve score
		for (auto idx = 0; idx < (sizeof(features) / sizeof(FeatureType)); idx++) {
			// Feature is required
			if (accessor(properties.device_features, idx)) {
				if (accessor(features, idx)) ++score;
				else return reject(features, idx);
			}
		}

		return score;
	}

	PhysicalBuilder::Rank::Score PhysicalBuilder::test_extensions(vk::PhysicalDevice& device) {
		Rank::Score score = 1;
		auto extensions = device.enumerateDeviceExtensionProperties();
		nova_bark_debug("VK Availble Extensions: {}", extensions.size());
		for (auto& ext_name : properties.extensions_device) {
			if (auto it = std::ranges::find_if(extensions, [&](auto&& ext) { return std::strcmp(ext_name, ext.extensionName) == 0; }); it == extensions.end())
				return reject(ext_name);
			++score;
		}
		return score;
	}

	PhysicalBuilder::Rank::Score PhysicalBuilder::queue_families(vk::PhysicalDevice& device) {
		constexpr Rank::Score WEIGHT_PRIORITY = 50;
		constexpr Rank::Score WEIGHT_DISTICNT = 1;

		Rank::Score score = 1;
		auto families = device.getQueueFamilyProperties();
		// Cache the queue results so they can be used if the device is picked.
		auto& qcache = current_device_info().queues;

		std::array<std::pair<Q*, std::vector<Q::Index>>, Queues::count> queue_priorities;
		std::ranges::transform(qcache.all(), queue_priorities.data(), [&](auto& q){ return std::pair{&q, assign_queues(device, q.type, families)}; });

		std::unordered_map<Q::Index, Q::FQCount> assigned{Queues::count};
		for (auto& [queue, priorities] : queue_priorities) {
			// Device does not support a required queue type
			if (priorities.size() == 0) return reject(queue->type);

			// Attempt to use each queues highest priority without sharing queue familes.
			Rank::Score scr = priorities.size();
			if (auto it = std::ranges::find_if(priorities, [&](auto&& family) { return !assigned.contains(family); }); it != priorities.end()) {
				auto& index = *it;
				assigned[index] = families[index].queueCount - 1;
				queue->family = index;
				scr = std::distance(it, priorities.end());
			}
			else {
				// If all are taken, just share our most prefered family if there is enough queues spare in the family.
				if (auto it = std::ranges::find_if(priorities, [&](auto&& family) { return static_cast<bool>(assigned.at(family)); }); it != priorities.end()) {
					auto& index = *it;
					--assigned[index];
					queue->family = index;
					scr = std::distance(it, priorities.end());
				// If all else, share the most prefered family & queue with another.
				} else {
					auto& index = priorities.front();
					queue->family = index;
					queue->type |= Q::Type::Merge;
				};
			}

			score += scr * WEIGHT_PRIORITY / priorities.size();
		}
		return score * WEIGHT_DISTICNT * assigned.size() / Queues::count;
	}

	// Introduce a bias to different GPU types
	PhysicalBuilder::Rank::Score PhysicalBuilder::rank_type(vk::PhysicalDevice& device) {
		constexpr Rank::Score WEIGHT = 100;
		return [&]() {
			switch (device.getProperties().deviceType) {
				case vk::PhysicalDeviceType::eDiscreteGpu: return 3;
				case vk::PhysicalDeviceType::eIntegratedGpu: return 2;
				case vk::PhysicalDeviceType::eVirtualGpu: return 2;
				case vk::PhysicalDeviceType::eCpu: return 1;
				case vk::PhysicalDeviceType::eOther: [[fallthrough]];
				default:
					nova_bark_warn("Unknown Case [vk Physical Device Type]: {}", static_cast<std::underlying_type_t<vk::PhysicalDeviceType>>(device.getProperties().deviceType));
					return 1;
			}
		}() * WEIGHT;
	}

	PhysicalBuilder::Rank::Score PhysicalBuilder::swapchain_surface_format(vk::PhysicalDevice& device) {
		constexpr Rank::Score WEIGHT = 25;
		auto& cache = current_device_info().swapchain.format;

		auto formats = device.getSurfaceFormatsKHR(nova_abyss_api->instance.surface);
		if (auto it = std::ranges::find_if(formats, [](auto&& format) { return
			format.format == vk::Format::eB8G8R8A8Srgb &&
			format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear;
		}); it != formats.end()) {
			cache = *it;
			return WEIGHT;
		}
		return reject(vk::SurfaceFormatKHR{
			.format = vk::Format::eB8G8R8A8Srgb,
			.colorSpace = vk::ColorSpaceKHR::eSrgbNonlinear,
		});
	}

	PhysicalBuilder::Rank::Score PhysicalBuilder::swapchain_present_mode(vk::PhysicalDevice& device) {
		constexpr Rank::Score WEIGHT = 25;
		auto& cache = current_device_info().swapchain.present_mode;

		auto present_modes = device.getSurfacePresentModesKHR(nova_abyss_api->instance.surface);
		constexpr std::array modes{ vk::PresentModeKHR::eMailbox, vk::PresentModeKHR::eFifoRelaxed, vk::PresentModeKHR::eFifo };
		for (auto idx = 0; idx < modes.size(); ++idx) {
			auto& mode = modes[idx];
			if (auto it = std::ranges::find(present_modes, mode); it != present_modes.end()) {
				cache = mode;
				return (modes.size() - idx) * WEIGHT;
			}
		}
		return reject(vk::PresentModeKHR::eFifo);
	}

	std::vector<Q::Index> PhysicalBuilder::assign_queues(vk::PhysicalDevice& device, Q::Type type, std::vector<vk::QueueFamilyProperties>& families) {
		enum class Priority : uint8_t {
			Lowest, Middle, Highest
		};

		std::vector<std::pair<Q::Index, Priority>> priorities;
		switch (type) {
			case Q::Type::Graphics: {
				for (Q::Index idx = 0; idx < families.size(); ++idx)
					if (families[idx].queueFlags & vk::QueueFlagBits::eGraphics) {
						priorities.emplace_back(
							idx,
							device.getSurfaceSupportKHR(idx, nova_abyss_api->instance.surface) ? Priority::Highest : Priority::Middle
						);
					}
			} break;
			case Q::Type::Compute: {
				for (Q::Index idx = 0; idx < families.size(); ++idx)
					if (families[idx].queueFlags & vk::QueueFlagBits::eCompute) {
						priorities.emplace_back(
							idx, // A family without graphics is dedicated to compute so is prefered.
							// Prefer: Distinct Compute > Graphics
							families[idx].queueFlags & vk::QueueFlagBits::eGraphics ? Priority::Middle : Priority::Highest
						);
					}
			} break;
			case Q::Type::Transfer: {
				for (Q::Index idx = 0; idx < families.size(); ++idx)
					if (families[idx].queueFlags & vk::QueueFlagBits::eTransfer | vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eCompute) {
						priorities.emplace_back(
							idx, // A family without graphics or compute is dedicated to transfer so is prefered.
							// Prefer: Distinct Transfer > Compute > Graphics
							families[idx].queueFlags & vk::QueueFlagBits::eGraphics ? Priority::Lowest
							: families[idx].queueFlags & vk::QueueFlagBits::eCompute ? Priority::Middle : Priority::Highest
						);
					}
			} break;
			case Q::Type::Present: {
				for (Q::Index idx = 0; idx < families.size(); ++idx)
					if (device.getSurfaceSupportKHR(idx, nova_abyss_api->instance.surface)) {
						priorities.emplace_back(
							idx,
							families[idx].queueFlags & vk::QueueFlagBits::eGraphics ? Priority::Highest
							: families[idx].queueFlags & vk::QueueFlagBits::eCompute ? Priority::Middle : Priority::Lowest
						);
					}
			} break;
			default:
				nova_bark_warn("Unahndled Case [Queue Type]: {}", type);
				break;
		}

		std::ranges::stable_sort(priorities, std::ranges::greater{}, &std::remove_cvref_t<decltype(priorities)>::value_type::second);
		std::vector<Q::Index> out;
		out.reserve(priorities.size());
		std::ranges::transform(priorities, std::back_inserter(out), &std::remove_cvref_t<decltype(priorities)>::value_type::first);
		return out;
	}

}  // namespace Nova::abyss::nvk

#endif	// NOVA_ABYSS_VULKAN
