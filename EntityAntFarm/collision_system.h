#pragma once
#include "Managers.h"
#include "EntityManager.h"
#include <cmath>

class CollisionSystem {
private:
	const EntityManager* entityManager;
	const PositionManager* positionManager;
	const VelocityManager* velocityManager;
	const FoodManager* foodManager;
	const TrailManager* trailManager;
	CollisionManager* collisionManager;

public:
	CollisionSystem(
		EntityManager* _entityManager,
		PositionManager* _positionManager,
		VelocityManager* _velcotiyManager,
		CollisionManager* _collisionManager,
		FoodManager* _foodManager,
		TrailManager* _trailManager
	) : entityManager{ _entityManager },
		positionManager{ _positionManager },
		velocityManager{ _velcotiyManager },
		collisionManager{ _collisionManager },
		foodManager{ _foodManager },
		trailManager{ _trailManager } {}

	void step(unsigned collisionRange = 10);
};

