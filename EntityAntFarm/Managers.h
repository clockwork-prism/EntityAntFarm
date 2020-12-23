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

typedef Component<int32_t> Trail;

typedef ComponentManager<Trail, std::vector>  TrailManager;

typedef Component<int32_t> Food;

typedef ComponentManager<Food, std::vector> FoodManager;

typedef Component<uint32_t> AI;

typedef ComponentManager<AI, std::vector> AIManager;

typedef Component<std::array<int32_t, 17>> History;

typedef ComponentManager<History, std::vector> HistoryManager;

struct Collision {
	Entity entity;
	std::vector<std::pair<Entity, std::array<double, 2>>> foodCollisions;
	std::vector<std::pair<Entity, std::array<double, 2>>> trailCollisions;
};

typedef ComponentManager<Collision, std::vector> CollisionManager;