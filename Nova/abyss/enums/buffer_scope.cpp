#include "npch.h"
#include "abyss/buffer_scope.h"

nova_meta_enum_str(Nova::abyss::buffer::Scope, scope) {
	using Type = decltype(scope);
	switch (scope) {
	case Type::None:	return "None";
	case Type::Bind:	return "Bind";
	case Type::Read:	return "Read";
	case Type::Write:	return "Write";
	default:
		nova_bark_warn("Unknown Case: [Buffer Scope]: {}", cpp::to_underlying(scope));
		return "Unknown";
	}
}
