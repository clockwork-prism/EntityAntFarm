#pragma once
#include <vector>
#include <deque>
#include "Entity.h"
class EntityManager
{
public:
	EntityManager();

	bool is_alive(const Entity e);

	Entity create_entity();

	void destroy_entity(Entity e);

private:
	std::vector <char> _registry;
	std::deque <unsigned> _freeIndeces;
	static const unsigned MIN_FREE{ 1024 };
};
