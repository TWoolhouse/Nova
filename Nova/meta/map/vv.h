#pragma once
#include "../head.h"
#include "../pack.h"
#include "../vpack.h"

namespace Nova::meta {

	// Value => Type

	namespace pair {
		template<auto k, auto v, typename K = decltype(k), typename V = decltype(v)>
		struct VV {
			using key_type = K;
			using value_type = V;
			static constexpr key_type key = k;
			static constexpr value_type value = v;
		};
	}

	namespace map {

		namespace __I {
			template<typename T>
			concept VVPair = requires {
				typename T::key_type;
				typename T::value_type;
				{ T::key } -> std::convertible_to<const typename T::key_type>;
				{ T::value } -> std::convertible_to<const typename T::value_type>;
			};
		} // namespace __I

		template<typename ...Pairs> requires (__I::VVPair<Pairs> && ...)
			struct VV {
			using pairs = meta::pack<Pairs...>;
			using key_types = meta::pack<typename Pairs::key_type...>;
			using value_types = meta::pack<typename Pairs::value_type...>;
			using keys = meta::vpack<Pairs::key...>;
			using values = meta::vpack<Pairs::value...>;

			protected:
				template<auto V>
				static consteval auto index() {
					constexpr auto index = keys::template index<V>();
					static_assert(index != keys::index_null, "Value is not in VVMap");
					return index;
				}
			public:
				template<auto V>
				using pair = pairs::template get<index<V>()>;

				template<auto V>
				NODISCARD static consteval auto get() { return pair<V>::value; }

		};

	}
}