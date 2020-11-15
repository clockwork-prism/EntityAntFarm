#pragma once
#include "EntityManager.h"
#include "Managers.h"
#include <iostream>

class PhysicsSystem {
private:
	const EntityManager* entityManager;
	PositionManager* positionManager;
	VelocityManager* velocityManager;

	void _update_positions();
public:
	PhysicsSystem(
		EntityManager* _entityManager,
		PositionManager* _position,
		VelocityManager* _velocity
	) : entityManager{ _entityManager },
		positionManager{ _position },
		velocityManager{ _velocity } {}

	void step(std::vector<std::vector<Collision>>& collisionMap);
};
