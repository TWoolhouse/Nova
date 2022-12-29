#pragma once
#include "../head.h"
#include "../pack.h"
#include "../vpack.h"

namespace Nova::meta {

	// Value => Value

	namespace pair {
		template<auto k, typename V, typename K = decltype(k)>
		struct VT {
			using key_type = K;
			using value_type = V;
			using value = V;
			static constexpr key_type key = k;
		};
	}

	namespace map {

		namespace __I {
			template<typename T>
			concept VTPair = requires {
				typename T::key_type;
				typename T::value_type;
				typename T::value;
				requires std::same_as<typename T::value_type, typename T::value>;
				{ T::key } -> std::convertible_to<const typename T::key_type>;
			};
		} // namespace __I

		template<typename ...Pairs> requires (__I::VTPair<Pairs> && ...)
			struct VT {
			using pairs = meta::pack<Pairs...>;
			using key_types = meta::pack<typename Pairs::key_type...>;
			using value_types = meta::pack<typename Pairs::value_type...>;
			using keys = meta::vpack<Pairs::key...>;
			using values = meta::pack<typename Pairs::value...>;

			protected:
				template<auto V>
				static consteval auto index() {
					constexpr auto index = keys::template index<V>();
					static_assert(index != keys::index_null, "Value is not in VTMap");
					return index;
				}
			public:
				template<auto V>
				using pair = pairs::template get<index<V>()>;

				template<auto V>
				using get = pair<V>::value;

		};

	}
}