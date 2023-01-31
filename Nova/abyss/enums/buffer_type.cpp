#include "npch.h"
#include "abyss/buffer_type.h"

nova_meta_enum_str(Nova::abyss::buffer::Type, type) {
	using Type = decltype(type);
	switch (type) {
		case Type::Vertex:	return "Vertex";
		case Type::Index:	return "Index";
		case Type::TransferSrc:	return "TransferSrc";
		case Type::TransferDst:	return "TransferDst";
		case Type::Uniform:	return "Uniform";
		default:
			nova_bark_warn("Unknown Case: [Buffer Type]: {}", cpp::to_underlying(type));
			return "Unknown";
	}
}
