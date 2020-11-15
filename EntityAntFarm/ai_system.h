#pragma once
#include "Managers.h"
#include "EntityManager.h"

class AISystem {
private:
	EntityManager* entityManager;
	VelocityManager* velocityManager;
public:
	AISystem(
		EntityManager* _entityManager,
		VelocityManager* _velocityManager
	) : entityManager{ _entityManager },
		velocityManager{ _velocityManager } {}

	void step();
};