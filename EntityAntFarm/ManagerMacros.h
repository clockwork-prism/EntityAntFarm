#pragma once
#include "ComponentManager.h"
#include "EntityManager.h"
#include "ArrayComponentManager.h"
#include "ColorManager.h"
#include <vector>
#include <array>
#include <cstdint>
#include <utility>

#ifndef POSITION
#define POSITION Component<std::array<int32_t, 3>>
#endif // !POSITION

#ifndef POSITION_MANAGER
#define POSITION_MANAGER ComponentManager<POSITION, std::vector>
#endif // !POSITION_MANAGER

#ifndef VELOCITY
#define VELOCITY Component<std::array<int, 4>>
#endif // !VELOCITY

#ifndef VELOCITY_MANAGER
#define VELOCITY_MANAGER ComponentManager<VELOCITY, std::vector>
#endif // !VELOCITY_MANAGER

#ifndef TRAIL
#define TRAIL Component<uint32_t>
#endif // !TRAIL

#ifndef TRAIL_MANAGER
#define TRAIL_MANAGER ComponentManager<TRAIL, std::vector>
#endif // !TRAIL_MANAGER

#ifndef COLLISION
#define COLLISION std::pair<POSITION, double>
#endif // !COLLISION

struct NewTrail {
	uint32_t trail;
	std::array<int32_t, 3> position;
	int32_t color;
};

Entity new_trail(NewTrail& newTrail, EntityManager& entityManager, TRAIL_MANAGER& trails, ColorManager& colors, POSITION_MANAGER& positions);

struct NewAnt {
	std::array<int32_t, 3> position;
	int32_t color;
	std::array<int, 4> velocity;
};

Entity new_ant(NewAnt& newAnt, EntityManager& entityManager, POSITION_MANAGER& positions, ColorManager& colors, VELOCITY_MANAGER& velocities);