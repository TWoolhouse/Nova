#pragma once
#include "meta/head.h"
#include "../null.h"
#include "abyss/buffer_type.h"
#include "abyss/buffer_scope.h"

namespace Nova::abyss::spec::buffer {

	template<typename T>
	concept Buffer = Null<T> && requires (T buffer) {
		T{ 0, abyss::buffer::Type::Vertex, abyss::buffer::Scope::None };

		{ buffer.acquire() } -> std::same_as<void*>;
		{ buffer.release() };
		{ buffer.map() } -> std::same_as<void*>;

		requires std::same_as<decltype(buffer.size), size_t>;
		requires std::same_as<decltype(buffer.type), abyss::buffer::Type>;
		requires std::same_as<decltype(buffer.scope), abyss::buffer::Scope>;
	};

}
