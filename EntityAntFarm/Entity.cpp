#include "Entity.h"

Entity::Entity(unsigned _idx, unsigned _generation)
{
	this->id = (_generation & ENTITY_GENERATION_MASK) << ENTITY_INDEX_BITS;
	this->id += (_idx & ENTITY_INDEX_MASK);
}

unsigned Entity::index() const { return id & ENTITY_INDEX_MASK; }

unsigned Entity::generation() const { return (id >> ENTITY_INDEX_BITS) & ENTITY_GENERATION_MASK; }

bool operator<(const Entity& lhs, const Entity& rhs)
{
	return lhs.index() < rhs.index();
}

bool operator==(const Entity& lhs, const Entity& rhs)
{
	return lhs.index() == rhs.index();
}
