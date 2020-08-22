#include "Entity.h"

Entity::Entity(uint32_t _idx, uint32_t _generation)
{
	this->id = (_generation & ENTITY_GENERATION_MASK) << ENTITY_INDEX_BITS;
	this->id += (_idx & ENTITY_INDEX_MASK);
}

uint32_t Entity::index() const { return id & ENTITY_INDEX_MASK; }

uint32_t Entity::generation() const { return (id >> ENTITY_INDEX_BITS) & ENTITY_GENERATION_MASK; }

bool operator<(const Entity& lhs, const Entity& rhs)
{
	return lhs.index() < rhs.index();
}

bool operator==(const Entity& lhs, const Entity& rhs)
{
	return lhs.index() == rhs.index();
}
