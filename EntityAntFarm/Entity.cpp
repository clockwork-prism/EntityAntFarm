#include "Entity.h"

Entity::Entity(unsigned _idx, unsigned _generation)
{
	this->id = (_generation & ENTITY_GENERATION_MASK) << ENTITY_INDEX_BITS;
	this->id += (_idx & ENTITY_INDEX_MASK);
}