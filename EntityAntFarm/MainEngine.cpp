#include "MainEngine.h"

MainEngine::MainEngine() : _physics{ 10 }, entityManager {} {
	// Name you application
	sAppName = "EntityAntFarm";
}

bool MainEngine::OnUserCreate() {
	// Called once at the start
	entityManager = EntityManager();
	for (int i{}; i < 20; i++) {
		int x = rand() % ScreenWidth();
		int y = rand() % ScreenHeight();
		Entity e = entityManager.create_entity();
		_physics.add_transform(PositionComponent{ e, {x, y} });
	}
	return true;
}

bool MainEngine::OnUserUpdate(float fElapsedTime) {
	// called once per frame
	render_system(entityManager, _physics.transform, this);
	ai_system(entityManager, _physics);
	physics_system(entityManager, _physics, fElapsedTime);
	return true;
}
