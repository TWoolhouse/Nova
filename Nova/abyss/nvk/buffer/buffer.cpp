#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "buffer.h"
#include "../context.h"
#include "meta/string.h"

#define scope_warn(scopes_request, scopes_reject, this_buffer) nova_bark_warn( \
	"Buffer<{}> does not explicitly request Scope[ {} ] : {}", \
	static_cast<void*>((this_buffer)->self), \
	::Nova::abyss::nvk::buffer::__I::scopes_strings( \
		static_cast<::Nova::abyss::nvk::buffer::Scope>(scopes_request), \
		static_cast<::Nova::abyss::nvk::buffer::Scope>(scopes_reject) \
	), \
	::Nova::abyss::nvk::buffer::__I::scopes_string((this_buffer)->scope) \
)

namespace Nova::abyss::nvk::buffer {

	namespace __I {
		std::string scopes_string(Scope scopes) {
			return (scopes == Scope::None) ? std::string(meta::estr(Scope::None)) : meta::estrs(scopes);
		}

		std::string scopes_strings(Scope required, Scope rejected) {
			if ((required | rejected) == Scope::None) return std::string(meta::estr(Scope::None));
			std::vector<std::string> vrb{};
			
			auto req = meta::ebits(required) | std::views::transform([](auto&& e) { return std::string(meta::estr(e)); });
			vrb.insert(vrb.end(), req.begin(), req.end());
			auto ban = meta::ebits(rejected) | std::views::transform([](auto&& e) { return nova_bark_format("!{}", meta::estr(e)); });
			vrb.insert(vrb.end(), ban.begin(), ban.end());

			return meta::str::join(vrb);
		}
	}

	Buffer::~Buffer() {
		nova_bark_term("Buffer");
		vmaDestroyBuffer(nova_abyss_api->vma, self, allocation);
	}

	Buffer::Buffer(size_t size, Type type, Scope scope) : size(size), type(type), scope(scope), self(), allocation() {
		nova_bark_init("VK Buffer");
		vk::BufferCreateInfo info_buffer{
			.size = size,
			.usage = static_cast<vk::BufferUsageFlagBits>(type),
		};
		VmaAllocationCreateInfo info_allocation{
			.flags = cpp::to_underlying(scope),
			.usage = VMA_MEMORY_USAGE_AUTO,
		};

		VmaAllocationInfo info;

		auto info_ptr = &info;
		constexpr auto debug = abyss::def::debug && bark::def::debug;
		if constexpr (!debug)
			info_ptr = nullptr;

		NVK_RESULT(
			vmaCreateBuffer(
				nova_abyss_api->vma,
				reinterpret_cast<VkBufferCreateInfo*>(&info_buffer),
				&info_allocation,
				reinterpret_cast<VkBuffer*>(&self),
				&allocation,
				info_ptr
			), "Failed to create VMA Buffer"
		);

		if constexpr (debug) {
			vk::MemoryPropertyFlagBits flags;
			vmaGetAllocationMemoryProperties(nova_abyss_api->vma, allocation, reinterpret_cast<vk::MemoryPropertyFlags::MaskType*>(&flags));
			nova_bark_debug("VK Buffer<{}>: {} {}B Scopes[ {} ], Memory[ {} ]",
				static_cast<void*>(self),
				type,
				info.size,
				__I::scopes_string(scope),
				meta::estrs(flags)
			);
		}

	}

	void* Buffer::map() {
		if (meta::def::Debug && !variant::mapped(scope))
			scope_warn(Scope::Bind | Scope::Write | Scope::Read, Scope::None, this);
		VmaAllocationInfo info;
		vmaGetAllocationInfo(nova_abyss_api->vma, allocation, &info);
		return info.pMappedData;
	}

	void* Buffer::acquire() {
		if (meta::def::Debug && !variant::acquirable(scope))
			scope_warn(Scope::Write | Scope::Read, Scope::None, this);
		void* ptr;
		vmaMapMemory(nova_abyss_api->vma, allocation, &ptr);
		return ptr;
	}

	void Buffer::release() {
		if (meta::def::Debug && !variant::releasable(scope))
			scope_warn(Scope::Write | Scope::Read, Scope::None, this);
		vmaUnmapMemory(nova_abyss_api->vma, allocation);
	}

}

#endif // NOVA_ABYSS_VULKAN
