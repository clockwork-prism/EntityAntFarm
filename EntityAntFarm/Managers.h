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

typedef std::pair<Position, double> Collision;

struct NewTrail {
	uint32_t trail;
	std::array<int32_t, 3> position;
	int32_t color;
};

Entity new_trail(NewTrail& newTrail, EntityManager& entityManager, TrailManager& trails, ColorManager& colors, PositionManager& positions);

struct NewAnt {
	std::array<int32_t, 3> position;
	int32_t color;
	std::array<int, 4> velocity;
};

Entity new_ant(NewAnt& newAnt, EntityManager& entityManager, PositionManager& positions, ColorManager& colors, VelocityManager& velocities);