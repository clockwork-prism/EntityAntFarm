#pragma once
#include "EntityManager.h"
#include "Managers.h"
#include <iostream>

void physics_system(
	const EntityManager& entityManager, 
	PositionManager& position, 
	VelocityManager& velocity, 
	std::vector<std::vector<Collision>>& collisionMap);

void _update_positions(
	VelocityManager& velocity, 
	const EntityManager& entityManager, 
	PositionManager& position);
