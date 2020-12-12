#pragma once
#include <vector>
#include <list>
#include <cstdint>
#include <utility>
#include "Entity.h"
#include "Component.h"
#include "ComponentManager.h"

typedef Component<std::array<int32_t, 3>> Position;

class PositionManager : public ComponentManager<Position, std::vector> {
private:

public:
	static const int32_t PRIME{ 1000003 };
	std::vector<std::list<std::pair<std::array<int32_t, 2>, std::vector<size_t>>>> nodeTable;


};

size_t hash_position(int32_t x, int32_t y, int32_t prime, size_t M);

size_t hash_int(int32_t x, int32_t prime, size_t M);