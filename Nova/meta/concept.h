#pragma once
#include "head.h"
#include "function.h"

namespace Nova::meta {

	#define nova_meta_concept(Concept) \
		[]<typename... Ts>() consteval { return Concept<Ts...>; }
	#define nova_meta_concept_exec(ConceptLambda, ...) ConceptLambda.template operator()<__VA_ARGS__>()



	namespace __I {
		template<auto Concept, typename T, typename ...Ts>
		consteval auto all_require() {
			constexpr auto result = nova_meta_concept_exec(Concept, T);
			if constexpr (sizeof...(Ts))
				return result && (all_require<Concept, Ts...>());
			else return result;
		}
	} // namespace __I

	namespace is {
		template<auto Concept, typename T, typename ...Ts>
		concept all_require = __I::all_require<Concept, T, Ts...>();
	} // namespace is



	namespace __I {
		// https://stackoverflow.com/a/17390695/13268833
		template<template<typename...> class TT, typename T>
		struct is_specialisation_of : std::false_type {};

		template<template<typename...> class TT, typename... Ts>
		struct is_specialisation_of<TT, TT<Ts...>> : std::true_type {};
	} // namespace __I

	namespace is {
		template<typename T, template<typename...> typename Base>
		concept specialisation_of = __I::is_specialisation_of<Base, T>::value;
	} // namespace is



	namespace is {
		template<typename ...Ts>
		concept all_same = sizeof...(Ts) < 2 ||
			(std::same_as<std::tuple_element_t<0, std::tuple<Ts...>>, Ts> && ...);
	} // namespace is


	namespace is {
		template<typename T>
		concept Enum = std::is_enum_v<T>;

		template<typename Derived, typename Base>
		concept enum_from = Enum<Derived> && (
			(Enum<Base> && std::same_as<std::underlying_type_t<Derived>, std::underlying_type_t<Base>>) || 
			(std::same_as<std::underlying_type_t<Derived>, Base>)
		);
	} // namespace is

} // namespace Nova::meta
