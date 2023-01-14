#pragma once
#include "meta/head.h"

namespace Nova::nvtl {

	template<typename Key, typename T>
	class Cache {
	public:
		using key_type = Key;
		using value_type = T;
		using Handle = std::shared_ptr<value_type>;
	protected:
		std::unordered_map<Key, typename Handle::weak_type> map;
	public:

		Handle get(const Key& key) {
			return map.at(key).lock();
		}

		bool contains(const Key& key) {
			return map.contains(key);
		}

		Handle try_get(const Key& key) {
			if (auto it = map.find(key); it != map.cend())
				return it->second.lock();
			return Handle{};
		}

		template<typename ...Ts>
		Handle emplace(const Key& key, Ts&& ...args) {
			auto& [mkey, mptr] = *map.emplace(key, typename Handle::weak_type{}).first;
			auto ptr = Handle(new value_type(std::forward<Ts>(args)...), [&](value_type* p) {
				map.erase(mkey);
				delete p;
			});
			mptr = ptr;
			return ptr;
		}

		void clear() {
			map.clear();
		}

		bool erase(const Key& key) {
			return map.erase(key);
		}

		auto operator[](const Key& key) {
			return get(key);
		}

		size_t size() const {
			return map.size();
		}

		void reserve(size_t size) {
			map.reserve(size);
		}

	};

	template<typename Key, typename T> requires requires (Key key) {
		T(key);
	}
	class CacheConstructor : public Cache<Key, T> {
	protected:
		using Super = Cache<Key, T>;
	public:
		using Handle = Super::Handle;

		Handle get(const Key& key) {
			if (auto it = this->map.find(key); it != this->map.cend())
				return it->second.lock();
			return emplace(key);
		}

		Handle emplace(const Key& key) {
			return Super::emplace(key, key);
		}

		auto operator[](const Key& key) {
			return get(key);
		}
	};

}
