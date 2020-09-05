#pragma once
#include "EntityManager.h"
#include "ManagerMacros.h"
#include <iostream>

void physics_system(const EntityManager& entityManager, POSITION_MANAGER& position, VELOCITY_MANAGER& velocity, std::vector<std::vector<COLLISION>>& collisionMap);

void _update_positions(VELOCITY_MANAGER& velocity, const EntityManager& entityManager, POSITION_MANAGER& position);
