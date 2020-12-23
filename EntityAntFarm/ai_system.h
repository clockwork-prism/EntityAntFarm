#pragma once
#include "Managers.h"
#include "EntityManager.h"
#include "misc.h"
#include <math.h>
#include <algorithm>
#include <random>

class AISystem {
private:
	EntityManager* entityManager;
	PositionManager* positionManager;
	VelocityManager* velocityManager;
	AIManager* aiManager;
	HistoryManager* historyManager;
	CollisionManager* collisionManager;

	std::vector<uint8_t> decisionVector;
public:
	AISystem(
		EntityManager* _entityManager,
		PositionManager* _positionManager,
		VelocityManager* _velocityManager,
		AIManager* _aiManager,
		HistoryManager* _historyManager,
		CollisionManager* _collisionManager
	) : entityManager{ _entityManager },
		positionManager{ _positionManager },
		velocityManager{ _velocityManager },
		aiManager{ _aiManager },
		historyManager{ _historyManager },
		collisionManager{ _collisionManager },
		decisionVector(512) {}

	void step();
private:
	void _ant_ai(std::vector<AI>::iterator& ait);
	uint8_t _ant_seeking(std::vector<uint8_t>& pool);
	void _ant_stationary(std::vector<AI>::iterator& ait, std::vector<Velocity>::iterator& it);
	std::array<int, 2> _choice_to_velocity(const uint8_t& choice);
	uint8_t _velocity_to_choice(const std::array<int, 2> vel);
	bool _choice_valid(const uint8_t& choice, std::vector<History>::iterator& it);
};