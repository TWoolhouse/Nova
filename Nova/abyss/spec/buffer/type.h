#pragma once
#include "meta/head.h"
#include "../null.h"
#include "abyss/buffer_vertex.h"
#include "abyss/interface/buffer_vertex.h"
#include "meta/pack.h"

namespace Nova::abyss::spec::buffer {

	template<typename T>
	concept Type = std::is_enum_v<T> && requires {
		T::Index;
		T::Vertex;
		T::TransferSrc;
		T::TransferDst;
	};


}