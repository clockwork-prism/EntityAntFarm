#pragma once
#include <cstdint>
#include <array>
#include "Managers.h"

struct NewTrailManagers {
	EntityManager* entityManager;
	TrailManager* trailManager;
	ColorManager* colorManager;
	PositionManager* positionManager;
};

Entity new_trail(uint32_t trail, std::array<int32_t, 3> position, NewTrailManagers &managers);

struct NewAntManagers {
	EntityManager* entityManager;
	PositionManager* positionManager;
	ColorManager* colorManager;
	VelocityManager* velocityManager;
};

Entity new_ant(std::array<int32_t, 3> position, NewAntManagers &managers);
