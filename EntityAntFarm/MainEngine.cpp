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
	_color = COLOR_MANAGER();
	for (int i{}; i < 20; i++) {
		int x = rand() % ScreenWidth();
		int y = rand() % ScreenHeight();
		NewAnt newAnt{
			{x, y, 1},
			{color_to_int({255, 255, 255, 255})},
			{0, 0, 0, 0}
		};
		new_ant(newAnt, entityManager, _position, _color, _velocity);
	}
	return true;
}

bool MainEngine::OnUserUpdate(float fElapsedTime) {
	// called once per frame, draws random coloured pixels
	render_system(this->entityManager, this->_position, this->_color, this);
	std::vector<std::vector<COLLISION>> collisions = collision_system(entityManager, _position, _velocity);
	resource_system(this->entityManager, this->_position, this->_trail, this->_color, collisions);
	ai_system(this->entityManager, this->_velocity);
	physics_system(this->entityManager, this->_position, this->_velocity, collisions);
	return true;
}
