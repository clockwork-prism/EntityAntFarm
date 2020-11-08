#pragma once
#include "ComponentManager.h"
#include <cstdint>
#include <unordered_map>

template <typename T, template <typename...> class A>
class StaticComponentManager : public ComponentManager<T, A>
{
private:
	std::unordered_map<int64_t, size_t> _positionMap;
	int64_t _get_key(int32_t x, int32_t y) const {
		unsigned UI_MASK = ~(1 << 31);
		int64_t key{x};
		key = key << 32;
		key += y;
		return key;
	}

public:
	T at(int32_t x, int32_t y) {
		int64_t key = this->_get_key(x, y);
		size_t idx = this->_positionMap.at(key);
		auto it = this->begin();
		std::advance(it, idx);
		return *it;
	}

	const T cat(int32_t x, int32_t y) const {
		int64_t key = this->_get_key(x, y);
		size_t idx = this->_positionMap.at(key);
		auto it = this->cbegin();
		std::advance(it, idx);
		return *it;
	}

	auto iter_at(int32_t x, int32_t y) {
		int64_t key = this->_get_key(x, y);
		size_t idx = this->_positionMap.at(key);
		auto it = this->_components.begin();
		std::advance(it, idx);
		return it;
	}

	auto citer_at(int32_t x, int32_t y) const {
		int64_t key = this->_get_key(x, y);
		size_t idx = this->_positionMap.at(key);
		auto it = this->_components.cbegin();
		std::advance(it, idx);
		return it;
	}
};