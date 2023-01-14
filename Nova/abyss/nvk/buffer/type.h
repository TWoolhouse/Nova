#pragma once
#include "meta/head.h"
#include "../vk.h"

namespace Nova::abyss::nvk::buffer {
	
	enum class Type : std::underlying_type_t<vk::BufferUsageFlagBits> {
		Vertex = cpp::to_underlying(vk::BufferUsageFlagBits::eVertexBuffer),
		Index = cpp::to_underlying(vk::BufferUsageFlagBits::eIndexBuffer),
		TransferSrc = cpp::to_underlying(vk::BufferUsageFlagBits::eTransferSrc),
		TransferDst = cpp::to_underlying(vk::BufferUsageFlagBits::eTransferDst),
	};

}

nova_meta_enum_str(Nova::abyss::nvk::buffer::Type, type);
