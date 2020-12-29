#pragma once
#include "ComponentManager.h"
#include "EntityManager.h"
#include "ArrayComponentManager.h"
#include "ColorManager.h"
#include "PositionManager.h"
#include <vector>
#include <array>
#include <cstdint>
#include <utility>
#ifndef GIVER
#define GIVER 0
#endif
#ifndef RECEIVER
#define RECEIVER 2
#endif
#ifndef TRANSPORTER
#define TRANSPORTER 1
#endif

typedef Component<std::array<int, 4>> Velocity;

typedef ComponentManager<Velocity, std::vector> VelocityManager;

typedef Component<int32_t> Trail;

typedef ComponentManager<Trail, std::vector>  TrailManager;

struct Food {
	Entity entity;
	int32_t data;
	uint8_t kind;
};

typedef ComponentManager<Food, std::vector> FoodManager;

typedef Component<uint32_t> AI;

typedef ComponentManager<AI, std::vector> AIManager;

class History {
private:
	std::array<int32_t, 129> data;
public:
	History(Entity e, int32_t val) : entity{ e }, data{ val } {};
	Entity entity;
	void update_history(int32_t x, int32_t y);
	void reverse();
	int32_t data_at(size_t i) const;
	size_t size() const;
	int32_t back() const;
	void set_back(int32_t val);
};

typedef ComponentManager<History, std::vector> HistoryManager;

struct Collision {
	Entity entity;
	std::vector<std::pair<Entity, std::array<double, 3>>> foodCollisions;
	std::vector<std::pair<Entity, std::array<double, 2>>> trailCollisions;
};

typedef ComponentManager<Collision, std::vector> CollisionManager;