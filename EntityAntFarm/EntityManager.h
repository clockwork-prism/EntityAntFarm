#pragma once
#include <vector>
#include <deque>
#include "Entity.h"
class EntityManager
{
public:
	EntityManager();

	bool is_alive(const Entity e) const;

	Entity create_entity();

	void destroy_entity(Entity e);

	size_t size() const {
		return this->_registry.size();
	}

private:
	std::vector <char> _registry;
	std::deque <uint32_t> _freeIndeces;
	static const uint32_t MIN_FREE{ 1024 };
};
