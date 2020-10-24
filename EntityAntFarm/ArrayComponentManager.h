#pragma once
#include "ComponentManager.h"
#include "Array2D.h"
#include <vector>
#include <cstdint>

template <typename T, typename N, template <typename...> class A>
class ArrayComponentManager : public ComponentManager<T, A>
{
protected:
	A <Array2D<N>> _arrayComponents;
	std::vector<size_t> _freeIndeces;
	
public:
	ArrayComponentManager() = default;

	Array2D<N>& ar_at(Entity e) {
		T component = this->at(e);
		if (T.data < 0) {
			return _arrayComponents.at(-(T.data) - 1);
		}
		static Array2D<N> out(1, 1, T.data);
		return out;
	}

	const Array2D<N>& car_at(Entity e) const {
		T component = this->cat(e);
		if (component.data >= 0) {
			return _arrayComponents.at(component.data);
		}
		static Array2D<N> out(1, 1, component.data);
		return out;
	}

	bool add_entity_component(Entity e, Array2D<N> arr) {
		if (this->_map.count(e)) {
			auto it = this->_get_component_iterator(e);
			this->_arrayComponents.at(it->data) = arr;
			return true;
		}
		N idx{};
		if (this->_freeIndeces.empty()) {
			idx = static_cast<N>(this->_arrayComponents.size());
			this->_arrayComponents.push_back(arr);
		}
		else {
			idx = static_cast<N>(this->_freeIndeces.back());
			this->_freeIndeces.pop_back();
			this->_arrayComponents.at(idx) = arr;
		}
		return this->add_entity_component({ e, idx });
	}

	bool add_entity_component(T component) {
		return ComponentManager<T, A>::add_entity_component(component);
	}

	bool remove_entity_component(const Entity e) {
		// Duplicating code in parent class, but these variables are needed again below
		if (!this->_map.count(e))
			return false;
		size_t idx = this->_map[e];
		size_t lastIdx = this->_components.size() - 1;
		auto it = this->_get_component_iterator(e);
		auto lastIt = this->_components.end();
		lastIt--;
		*it = *lastIt;
		this->_map[lastIt->entity] = idx;
		this->_freeIndeces.push_back(it->data);
		this->_components.erase(lastIt);
		this->_map.erase(e);

		return true;
	}
};

