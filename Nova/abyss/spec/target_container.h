#pragma once
#include "meta/head.h"
#include "null.h"
#include "abyss/target_single.h"

namespace Nova::abyss::spec {

	// TODO: Define index type
	template<typename T>
	concept Targets = Null<T> && requires (T targets, size_t target_index) {
		{ targets[target_index] } -> std::same_as<abyss::Target&>;
	};

}