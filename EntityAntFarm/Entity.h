#pragma once
#include <cstdint>
/* This code was taken from Bitsquid's explanation on building ECS, 
ref: http://bitsquid.blogspot.com/2014/08/building-data-oriented-entity-system.html,
accessed 7/19/2020*/

inline const uint32_t ENTITY_INDEX_BITS = 24;
inline const uint32_t ENTITY_INDEX_MASK = (1 << ENTITY_INDEX_BITS) - 1;

inline const uint32_t ENTITY_GENERATION_BITS = 8;
inline const uint32_t ENTITY_GENERATION_MASK = (1 << ENTITY_GENERATION_BITS) - 1;

struct Entity
{
	Entity(uint32_t _id) : id{ _id } {}
	Entity(uint32_t _idx, uint32_t _generation);
	uint32_t id;

	uint32_t index() const;
	uint32_t generation() const;
};

bool operator<(const Entity& lhs, const Entity& rhs);
bool operator==(const Entity& lhs, const Entity& rhs);