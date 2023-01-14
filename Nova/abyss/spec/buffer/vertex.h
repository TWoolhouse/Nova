#pragma once
#include "meta/head.h"
#include "../null.h"
#include "abyss/buffer_vertex.h"
#include "meta/pack.h"

namespace Nova::abyss::spec::buffer {

	struct _V {
		using Spec = meta::pack<float>;
		float _;
	};

	template<typename T>
	concept _Vertex = Null<T> && requires (T buffer) {
		typename T::Spec;
		requires meta::is::pack<typename T::Spec>;

		{ static_cast<abyss::buffer::VertexI>(buffer) };
	};

	// TODO: Define index type
	template<template<typename...> typename T>
	concept Vertex = _Vertex<T<_V>>;

	template<typename T>
	concept VertexI = Null<T> && requires (T buffer) {
		{ buffer.size } -> std::convertible_to<size_t>;
		static_cast<abyss::buffer::Vertex<_V>>(buffer);
	};

}
