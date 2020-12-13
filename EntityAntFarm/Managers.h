#pragma once
#include "ComponentManager.h"
#include "EntityManager.h"
#include "ArrayComponentManager.h"
#include "ColorManager.h"
#include <vector>
#include <array>
#include <cstdint>
#include <utility>

typedef Component<std::array<int32_t, 3>> Position;

typedef ComponentManager<Position, std::vector> PositionManager;

typedef Component<std::array<int, 4>> Velocity;

typedef ComponentManager<Velocity, std::vector> VelocityManager;

typedef Component<uint32_t> Trail;

typedef ComponentManager<Trail, std::vector>  TrailManager;

typedef Component<uint32_t> Food;

typedef ComponentManager<Food, std::vector> FoodManager;

typedef std::pair<Position, double> Collision;

struct AIState {
	bool stationary;
};

typedef Component<AIState> AI;

typedef ComponentManager<AI, std::vector> AIManager;
