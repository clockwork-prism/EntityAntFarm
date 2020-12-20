#pragma once
#include <cstdint>
#include <array>
#include "Managers.h"
#include "misc.h"

class TrailGenerator {
private:
	EntityManager* entityManager;
	PositionManager* positionManager;
	ColorManager* colorManager;
	TrailManager* trailManager;
public:
	TrailGenerator(
		EntityManager* _entityManager = nullptr,
		PositionManager* _positionManager = nullptr,
		ColorManager* _colorManager = nullptr,
		TrailManager* _trailManager = nullptr
	) : entityManager{ _entityManager },
		positionManager{ _positionManager },
		colorManager{ _colorManager },
		trailManager{ _trailManager } {}
	Entity new_trail(uint32_t trail, std::array<int32_t, 3> position);
	void destroy_trail(Entity e);
};

class AntGenerator {
private:
	EntityManager* entityManager;
	PositionManager* positionManager;
	ColorManager* colorManager;
	FoodManager* foodManager;
	VelocityManager* velocityManager;
	AIManager* aiManager;
	HistoryManager* historyManager;
	CollisionManager* collisionManager;
public:
	AntGenerator(
		EntityManager * _entityManager, 
		PositionManager * _positionManager, 
		ColorManager * _colorManager, 
		FoodManager * _foodManager, 
		VelocityManager * _velocityManager, 
		AIManager * _aiManager, 
		HistoryManager * _historyManager, 
		CollisionManager* _collisionManager
	) : entityManager{ _entityManager },
		positionManager{ _positionManager },
		colorManager{ _colorManager },
		foodManager{_foodManager},
		velocityManager{ _velocityManager },
		aiManager{ _aiManager },
		historyManager{ _historyManager },
		collisionManager{ _collisionManager } {}

	Entity new_ant(std::array<int32_t, 3> position);
};

class FoodGenerator {
private:
	EntityManager* entityManager;
	PositionManager* positionManager;
	ColorManager* colorManager;
	FoodManager* foodManager;
public:
	FoodGenerator(
		EntityManager* _entityManager = nullptr,
		PositionManager* _positionManager = nullptr,
		ColorManager* _colorManager = nullptr,
		FoodManager* _foodManager = nullptr
	) : entityManager{ _entityManager },
		positionManager{ _positionManager },
		colorManager{ _colorManager },
		foodManager{ _foodManager } {}

	Entity new_food(uint32_t food, std::array<int32_t, 3> position);
	void new_food_cluster(int32_t n, uint32_t food, std::array<int32_t, 3> position); 
	void destroy_food(Entity e);
};