#include "EntityManager.h"
#include <iostream>

EntityManager::EntityManager()
{
}

bool EntityManager::is_alive(const Entity e) const
{
	try {
		return this->_registry.at(e.index()) == e.generation();
	} catch (const std::out_of_range& oor) {
		std::cerr << "Entity not found error: " << oor.what() << '\n';
		return false;
	}
}

Entity EntityManager::create_entity()
{
	uint32_t idx;
	if (this->_freeIndeces.size() > this->MIN_FREE) {
		idx = this->_freeIndeces.front();
		this->_freeIndeces.pop_front();
	}
	else {
		idx = (uint32_t) this->_registry.size();
		this->_registry.push_back(0);
	}
	return Entity(idx, this->_registry[idx]);
}

void EntityManager::destroy_entity(Entity e)
{
	if (this->is_alive(e)) {
		this->_registry[e.index()]++;
		this->_freeIndeces.push_back(e.index());
	}
}
