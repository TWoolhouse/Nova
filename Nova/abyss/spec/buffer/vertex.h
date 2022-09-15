#pragma once
#include "meta/head.h"
#include "../null.h"
#include "abyss/buffer_vertex.h"
#include "abyss/interface/buffer_vertex.h"
#include "meta/pack.h"

namespace Nova::abyss::spec::buffer {

	struct _V {
		using Spec = meta::pack<float>;
		float _;
	};

	template<typename T>
	concept _Vertex = Null<T> && std::derived_from<T, abyss::buffer::interface::Vertex> && requires {
		typename T::Spec;
		requires meta::is::pack<typename T::Spec>;
	};

	// TODO: Define index type
	template<template<typename...> typename T>
	concept Vertex = _Vertex<T<_V>>;

}