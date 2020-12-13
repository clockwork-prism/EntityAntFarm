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
	AIManager* aiManager;

	std::vector<uint8_t> decisionVector;
	void _choice_to_velocity(const uint8_t& choice, std::vector<Velocity>::iterator& it);
public:
	AISystem(
		EntityManager* _entityManager,
		PositionManager* _positionManager,
		VelocityManager* _velocityManager,
		AIManager* _aiManager
	) : entityManager{ _entityManager },
		positionManager{ _positionManager },
		velocityManager{ _velocityManager },
		aiManager{ _aiManager },
		decisionVector(512) {}

	void step(std::vector<std::vector<Collision>>& collisionMap);
};