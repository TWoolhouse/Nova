#include "npch.h"
#include "abyss/shader.h"

nova_meta_enum_str(Nova::abyss::Shader::Stage, stage) {
	using Stage = decltype(stage);
	switch (stage) {
		case Stage::Vertex:	return "Vertex";
		case Stage::Fragment:	return "Fragment";
		default:
			nova_bark_warn("Unknown Case: [Shader Stage]: {}", static_cast<std::underlying_type_t<decltype(stage)>>(stage));
			return "Unknown";
	}
}
