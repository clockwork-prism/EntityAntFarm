#include "MainEngine.h"

MainEngine::MainEngine() {
	// Name you application
	sAppName = "Example";
}

bool MainEngine::OnUserCreate() {
	// Called once at the start, so create things here
	entityManager = EntityManager();
	_position = POSITION_MANAGER();
	_velocity = VELOCITY_MANAGER();
	for (int i{}; i < 20; i++) {
		int x = rand() % ScreenWidth();
		int y = rand() % ScreenHeight();
		Entity e = entityManager.create_entity();
		_position.add_entity_component(e, { e, {x, y} });
		_velocity.add_entity_component(e, { e, {0, 0, 0, 0} });
	}
	return true;
}

bool MainEngine::OnUserUpdate(float fElapsedTime) {
	// called once per frame, draws random coloured pixels
	render_system(this->entityManager, this->_position, this);
	ai_system(this->entityManager, this->_velocity);
	physics_system(this->entityManager, this->_position, this->_velocity);
	return true;
}
