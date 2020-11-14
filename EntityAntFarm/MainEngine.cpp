#include "MainEngine.h"

MainEngine::MainEngine() {
	// Name you application
	sAppName = "Example";
}

bool MainEngine::OnUserCreate() {
	// Called once at the start, so create things here
	screenOffset = ScreenOffset{ ScreenWidth() / 2, ScreenHeight() / 2 };
	entityManager = EntityManager();
	positionManager = PositionManager();
	velocityManager = VelocityManager();
	colorManager = ColorManager();
	foodManager = FoodManager();

	antGenerator = AntGenerator(
		&entityManager,
		&positionManager,
		&colorManager,
		&foodManager,
		&velocityManager
	);
	trailGenerator = TrailGenerator(
		&entityManager,
		&positionManager,
		&colorManager,
		&trailManager
	);
	foodGenerator = FoodGenerator(
		&entityManager,
		&positionManager,
		&colorManager,
		&foodManager
	);

	for (int i{}; i < 20; i++) {
		int x = rand() % ScreenWidth();
		int y = rand() % ScreenHeight();
		x -= screenOffset.xOffset;
		y -= screenOffset.yOffset;
		antGenerator.new_ant({ x, y, 1 });
	}
	for (int i{}; i < 5; i++) {
		int x = rand() % ScreenWidth();
		int y = rand() % ScreenHeight();
		x -= screenOffset.xOffset;
		y -= screenOffset.yOffset;
		foodGenerator.new_food_cluster(3, 50, { x, y, 1 });
	}
	Entity home = this->entityManager.create_entity();
	this->positionManager.add_entity_component({ home, {0,0,1} });
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
	input_system(this, this->screenOffset, fElapsedTime);
	render_system(this->entityManager, this->positionManager, this->colorManager, this->screenOffset, this);
	std::vector<std::vector<Collision>> collisions = collision_system(entityManager, positionManager, velocityManager);
	resource_system(this->entityManager, this->positionManager, this->trailManager, this->colorManager, collisions);
	ai_system(this->entityManager, this->velocityManager);
	physics_system(this->entityManager, this->positionManager, this->velocityManager, collisions);
	return true;
}
