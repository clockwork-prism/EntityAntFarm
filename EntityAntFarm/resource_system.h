#pragma once

#include "Managers.h"
#include "Generators.h"
#include "EntityManager.h"
#include "ColorManager.h"
#include "misc.h"

class ResourceSystem {
private:
	EntityManager* entityManager;
	PositionManager* positionManager;
	ColorManager* colorManager;
	TrailManager* trailManager; 
	FoodManager* foodManager;
	VelocityManager* velocityManager;
	AIManager* aiManager;
	CollisionManager* collisionManager;
	
	AntGenerator* antGenerator;

	void _update_trails();

	void _transfer_food(uint32_t frameNumber);

	void _incremenet_trail(std::vector<Trail>::iterator& trailIterator, std::pair<bool, std::array<int32_t, 3Ui64>>& newTrail);

	void _update_trail_color(std::vector<Color>::iterator& cit, std::vector<Trail>::iterator& it);
public:
	ResourceSystem(
		EntityManager* _entityManager,
		PositionManager* _positionManager,
		ColorManager* _colorManager,
		TrailManager* _trailManager,
		FoodManager* _foodManager,
		VelocityManager* _velocityManager,
		AIManager* _aiManager,
		AntGenerator* _antGenerator,
		CollisionManager* _collisionManager
	) : entityManager{ _entityManager },
		positionManager{ _positionManager },
		colorManager{ _colorManager },
		trailManager{ _trailManager },
		foodManager{ _foodManager },
		velocityManager{ _velocityManager },
		aiManager{ _aiManager },
		antGenerator{ _antGenerator },
		collisionManager{ _collisionManager } {}

	void step(uint32_t frameNumber);
};