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
	_color = ColorManager();
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
	Entity home = this->entityManager.create_entity();
	this->_position.add_entity_component({ home, {100,100,1} });
	int32_t green = color_to_int({ 0, 255, 0, 255 });
	Array2D<int32_t> homeArray(3, 3,
		{ green, green, green,
		 green, 0,     green,
		 green, green, green }
	);
	this->_color.add_entity_component(home, homeArray);
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
