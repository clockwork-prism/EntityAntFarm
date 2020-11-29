#pragma once
#include "Managers.h"
#include "EntityManager.h"
#include <math.h>
#include <algorithm>
#include <random>

class AISystem {
private:
	EntityManager* entityManager;
	PositionManager* positionManager;
	VelocityManager* velocityManager;

	std::vector<uint8_t> decisionVector;
public:
	AISystem(
		EntityManager* _entityManager,
		PositionManager* _positionManager,
		VelocityManager* _velocityManager
	) : entityManager{ _entityManager },
		positionManager{ _positionManager },
		velocityManager{ _velocityManager }, 
		decisionVector(512) {}

	void step(std::vector<std::vector<Collision>>& collisionMap);
};