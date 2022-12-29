#pragma once
#include "../head.h"
#include "../pack.h"

namespace Nova::meta {

	// Type => Type

	namespace pair {
		template<typename K, typename V>
		struct TT {
			using key_type = K;
			using value_type = V;
			using key = K;
			using value = V;
		};
	}

	namespace map {

		namespace __I {
			template<typename T>
			concept TTPair = requires {
				typename T::key_type;
				typename T::value_type;
				typename T::key;
				typename T::value;
				requires std::same_as<typename T::key_type, typename T::key>;
				requires std::same_as<typename T::value_type, typename T::value>;
			};
		} // namespace __I

		template<typename ...Pairs> requires (__I::TTPair<Pairs> && ...)
			struct TT {
			using pairs = meta::pack<Pairs...>;
			using key_types = meta::pack<typename Pairs::key_type...>;
			using value_types = meta::pack<typename Pairs::value_type...>;
			using keys = meta::pack<typename Pairs::key...>;
			using values = meta::pack<typename Pairs::value...>;

			protected:
				template<typename T>
				static consteval auto index() {
					constexpr auto index = keys::template index<T>();
					static_assert(index != keys::index_null, "Type is not in TTMap");
					return index;
				}
			public:
				template<typename T>
				using pair = pairs::template get<index<T>()>;

				template<typename T>
				using get = pair<T>::value;

		};

	}
}