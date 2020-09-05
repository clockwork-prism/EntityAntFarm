#pragma once
#include "ManagerMacros.h"
#include "EntityManager.h"
#include <cmath>

std::vector<std::vector<COLLISION>> collision_system(const EntityManager& entityManager, const POSITION_MANAGER& position, const VELOCITY_MANAGER & velocity, unsigned collisionRange=10);
