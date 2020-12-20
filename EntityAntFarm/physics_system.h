#pragma once
#include "EntityManager.h"
#include "Managers.h"
#include <iostream>

class PhysicsSystem {
private:
	const EntityManager* entityManager;
	PositionManager* positionManager;
	VelocityManager* velocityManager;
	HistoryManager* historyManager;

	void _update_positions();
public:
	PhysicsSystem(
		EntityManager* _entityManager,
		PositionManager* _position,
		VelocityManager* _velocity,
		HistoryManager* _history
	) : entityManager{ _entityManager },
		positionManager{ _position },
		velocityManager{ _velocity },
		historyManager{ _history } {}

	void step();
};
