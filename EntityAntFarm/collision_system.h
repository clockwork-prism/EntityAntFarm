#pragma once
#include "Managers.h"
#include "EntityManager.h"
#include <cmath>

std::vector<std::vector<Collision>> collision_system(const EntityManager& entityManager, const PositionManager& position, const VelocityManager & velocity, unsigned collisionRange=10);
