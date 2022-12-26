#pragma once
#include "meta/head.h"

namespace Nova::abyss::spec::buffer {

	template<typename T>
	concept Type = std::is_enum_v<T> && requires {
		T::Index;
		T::Vertex;
		T::TransferSrc;
		T::TransferDst;
	};

}