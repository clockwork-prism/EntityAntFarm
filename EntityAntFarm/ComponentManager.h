#pragma once
#include <map>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include "Entity.h"
#include "Component.h"

template <typename T, template <typename...> class A> 
class ComponentManager {
protected:
	std::map <Entity, size_t> _map;
	A <T> _components;

	auto _get_component_iterator(Entity e) {
		size_t idx = this->_map[e];
		auto it = this->_components.begin();
		std::advance(it, idx);
		return it;
	}

public:
	ComponentManager() = default;

	T operator[] (const Entity e) {
		auto it = this->_get_component_iterator(e);
		return *it;
	}

	T at(Entity e) {
		size_t idx = this->_map.at(e);
		auto it = this->begin();
		std::advance(it, idx);
		return *it;
	}

	const T cat(Entity e) const {
		size_t idx = this->_map.at(e);
		auto it = this->cbegin();
		std::advance(it, idx);
		return *it;
	}

	auto iter_at(Entity e) {
		size_t idx = this->_map.at(e);
		auto it = this->_components.begin();
		std::advance(it, idx);
		return it;
	}

	auto citer_at(Entity e) const {
		size_t idx = this->_map.at(e);
		auto it = this->_components.cbegin();
		std::advance(it, idx);
		return it;
	}

	auto begin() { return this->_components.begin(); }
	auto end() { return this->_components.end(); }

	auto cbegin() const { return this->_components.cbegin(); }
	auto cend() const { return this->_components.cend(); }

	auto find(Entity e) {
		if (this->_map.count(e)) {
			return this->iter_at(e);
		}
		else {
			return this->_components.end();
		}
	}

	bool add_entity_component(T component) {
		if (this->_map.count(component.entity)) {
			auto it = this->_get_component_iterator(component.entity);
			*it = component;
			return true;
		}
		else {
			size_t idx{ this->_components.size() };
			this->_components.push_back(component);
			this->_map[component.entity] = idx;
			return false;
		}
	}

	bool remove_entity_component(const Entity e) {
		if (!this->_map.count(e))
			return false;
		size_t idx = this->_map[e];
		size_t lastIdx = this->_components.size() - 1;
		auto it = this->_get_component_iterator(e);
		auto lastIt = this->_components.end();
		lastIt--;
		*it = *lastIt;
		this->_map[lastIt->entity] = idx;
		this->_components.erase(lastIt);
		this->_map.erase(e);
		return true;
	}

	bool remove_entity_component(const std::vector<Entity> entities) {
		bool out{ true };
		for (auto e : entities) {
			if (!this->remove_entity_component(e))
				out = false;
		}
		return out;
	}

	void sort_components() {
		std::sort(this->_components.begin(), this->_components.end());
		size_t i{ 0 };
		for (auto c : this->_components) {
			this->_map[c.entity] = i;
			i++;
		}
	}

	template <typename F>
	void sort_components(F func) {
		std::sort(this->_components.begin(), this->_components.end(), func);
		size_t i{ 0 };
		for (auto c : this->_components) {
			this->_map[c.entity] = i;
			i++;
		}
	}

	size_t size() const { return this->_components.size(); }
};