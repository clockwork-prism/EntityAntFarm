#pragma once
#include "Managers.h"
#include "EntityManager.h"
#include <cmath>

class CollisionSystem {
private:
	const EntityManager* entityManager;
	const PositionManager* positionManager;
	const VelocityManager* velocityManager;
	CollisionManager* collisionManager;

public:
	CollisionSystem(
		EntityManager* _entityManager,
		PositionManager* _positionManager,
		VelocityManager* _velcotiyManager,
		CollisionManager* _collisionManager
	) : entityManager{ _entityManager },
		positionManager{ _positionManager },
		velocityManager{ _velcotiyManager },
		collisionManager{ _collisionManager } {}

	void step(unsigned collisionRange = 10);
};

