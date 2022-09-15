#pragma once
#include "vk.h"
#include "meta/bit.h"
#include "meta/smallest.h"

namespace Nova::abyss::nvk {

	struct Q : public OPVK<Q, vk::Queue> {
		// Queue Family Index Type
		using Index = uint32_t;
		// Queue Family Queues Count Type
		using FQCount = uint8_t;
		vk::Queue self;
		Index family;
		enum class Type : meta::smallest::uint<meta::bit(5)> {
			Graphics = meta::bit(1),
			Compute  = meta::bit(2),
			Transfer = meta::bit(3),
			Present  = meta::bit(4),
			Merge    = meta::bit(5),
		} type;
		static inline constexpr auto Invalid = (std::numeric_limits<decltype(family)>::max)();
	};

	struct Queues {
		static constexpr size_t count = 4;
		inline constexpr std::span<Q, count> all() noexcept { return std::span<Q, count>( reinterpret_cast<Q*>(this), count ); }

		Q graphics { {}, VK_NULL_HANDLE, Q::Invalid, Q::Type::Graphics };
		Q compute  { {}, VK_NULL_HANDLE, Q::Invalid, Q::Type::Compute  };
		Q transfer { {}, VK_NULL_HANDLE, Q::Invalid, Q::Type::Transfer };
		Q present  { {}, VK_NULL_HANDLE, Q::Invalid, Q::Type::Present  };
	};

	static_assert(Queues::count == sizeof(Queues) / sizeof(Q), "Queues::count does not match the number of queues provided!");

}

nova_meta_enum_str(Nova::abyss::nvk::Q::Type, type);
