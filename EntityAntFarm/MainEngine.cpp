#include "MainEngine.h"

MainEngine::MainEngine() {
	// Name you application
	sAppName = "Example";
}

bool MainEngine::OnUserCreate() {
	// Called once at the start, so create things here
	entityManager = EntityManager();
	positionManager = PositionManager();
	velocityManager = VelocityManager();
	colorManager = ColorManager();
	for (int i{}; i < 20; i++) {
		int x = rand() % ScreenWidth();
		int y = rand() % ScreenHeight();
		NewAnt newAnt{
			{x, y, 1},
			{color_to_int({255, 255, 255, 255})},
			{0, 0, 0, 0}
		};
		new_ant(newAnt, entityManager, positionManager, colorManager, velocityManager);
	}
	Entity home = this->entityManager.create_entity();
	this->positionManager.add_entity_component({ home, {100,100,1} });
	int32_t green = color_to_int({ 0, 255, 0, 255 });
	Array2D<int32_t> homeArray(3, 3,
		{ green, green, green,
		 green, 0,     green,
		 green, green, green }
	);
	this->colorManager.add_entity_component(home, homeArray);
	return true;
}

bool MainEngine::OnUserUpdate(float fElapsedTime) {
	// called once per frame, draws random coloured pixels
	render_system(this->entityManager, this->positionManager, this->colorManager, this);
	std::vector<std::vector<Collision>> collisions = collision_system(entityManager, positionManager, velocityManager);
	resource_system(this->entityManager, this->positionManager, this->_trail, this->colorManager, collisions);
	ai_system(this->entityManager, this->velocityManager);
	physics_system(this->entityManager, this->positionManager, this->velocityManager, collisions);
	return true;
}
