#pragma once
/* This code was taken from Bitsquid's explanation on building ECS, 
ref: http://bitsquid.blogspot.com/2014/08/building-data-oriented-entity-system.html,
accessed 7/19/2020*/

inline const unsigned ENTITY_INDEX_BITS = 24;
inline const unsigned ENTITY_INDEX_MASK = (1 << ENTITY_INDEX_BITS) - 1;

inline const unsigned ENTITY_GENERATION_BITS = 8;
inline const unsigned ENTITY_GENERATION_MASK = (1 << ENTITY_GENERATION_BITS) - 1;

struct Entity
{
	Entity(unsigned _id) : id{ _id } {}
	Entity(unsigned _idx, unsigned _generation);
	unsigned id;

	unsigned index() const;
	unsigned generation() const;
};

bool operator<(const Entity& lhs, const Entity& rhs);
bool operator==(const Entity& lhs, const Entity& rhs);