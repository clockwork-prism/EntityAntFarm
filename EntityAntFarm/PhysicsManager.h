#pragma once
#include "Position.h"
#include <vector>
#include <array>
#include <algorithm>

class PhysicsManager
{
private:
	std::map <Entity, unsigned> _map;
public:
	PhysicsManager(unsigned _blockSize) : blockSize{ _blockSize } {}
	unsigned blockSize;

	std::vector<PositionComponent> transform;
	std::vector<std::array<unsigned, 4>> velocity;
	// std::vector<std::vector<std::array<int, 2>>> mask;
	std::vector<int32_t> color;

	void sort_components(unsigned left = 0, unsigned right = 0);

	unsigned add_transform(PositionComponent newPosition);

	template <typename T>
	void delete_component(T del) {
		this->transform_at(del) = { INT_MAX, INT_MAX };
		this->velocity_at(del) = { 0, 0, 0, 0 };
		this->color_at(del) = 0;
	}

	void garbage_collect();

	PositionComponent &transform_at(Entity e);
	PositionComponent &transform_at(unsigned idx);
	std::array<unsigned, 4> &velocity_at(Entity e);
	std::array<unsigned, 4> &velocity_at(unsigned idx);
	int32_t & color_at(Entity e);
	int32_t & color_at(unsigned idx);
};

