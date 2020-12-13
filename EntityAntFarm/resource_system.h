#pragma once

#include "Managers.h"
#include "Generators.h"
#include "EntityManager.h"
#include "ColorManager.h"

class ResourceSystem {
private:
	EntityManager* entityManager;
	PositionManager* positionManager;
	ColorManager* colorManager;
	TrailManager* trailManager; 
	FoodManager* foodManager;
	VelocityManager* velocityManager;
	AIManager* aiManager;

	void _update_trails(std::vector<std::vector<Collision>>& collisionMap);

	void _transfer_food(std::vector<std::vector<Collision>>& collisionMap);

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
		AIManager* _aiManager
	) : entityManager{ _entityManager },
		positionManager{ _positionManager },
		colorManager{ _colorManager },
		trailManager{ _trailManager },
		foodManager{ _foodManager },
		velocityManager{ _velocityManager },
		aiManager{ _aiManager }{}

	void step(std::vector<std::vector<Collision>>& collisionMap);

	static const uint32_t TRAIL_MAX = 10000;
	static const uint32_t TRAIL_INCR = 2000;
	static const uint32_t TRAIL_DECAY = 50;
};