#pragma once
#include "../head.h"
#include "../pack.h"
#include "../vpack.h"

namespace Nova::meta {

	// Type => Value

	namespace pair {
		template<typename K, auto v, typename V = decltype(v)>
		struct TV {
			using key_type = K;
			using value_type = V;
			using key = K;
			static constexpr value_type value = v;
		};
	}

	namespace map {

		namespace __I {
			template<typename T>
			concept TVPair = requires {
				typename T::key_type;
				typename T::value_type;
				typename T::key;
				requires std::same_as<typename T::key_type, typename T::key>;
				{ T::value } -> std::convertible_to<const typename T::value_type>;
			};
		} // namespace __I

		template<typename ...Pairs> requires (__I::TVPair<Pairs> && ...)
			struct TV {
			using pairs = meta::pack<Pairs...>;
			using key_types = meta::pack<typename Pairs::key_type...>;
			using value_types = meta::pack<typename Pairs::value_type...>;
			using keys = meta::pack<typename Pairs::key...>;
			using values = meta::vpack<Pairs::value...>;

			protected:
				template<typename T>
				static consteval auto index() {
					constexpr auto index = keys::template index<T>();
					static_assert(index != keys::index_null, "Type is not in TVMap");
					return index;
				}
			public:
				template<typename T>
				using pair = pairs::template get<index<T>()>;

				template<typename T>
				NODISCARD static consteval auto get() { return pair<T>::value; }

		};

	}
}