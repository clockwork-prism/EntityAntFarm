#include "MainEngine.h"

MainEngine::MainEngine() {
	// Name you application
	sAppName = "Example";
}

bool MainEngine::OnUserCreate() {
	// Called once at the start, so create things here
	screenOffset = ScreenOffset{ ScreenWidth() / 2, ScreenHeight() / 2 };

	// Managers
	entityManager = new EntityManager();
	positionManager = new PositionManager();
	colorManager = new ColorManager();
	foodManager = new FoodManager();
	trailManager = new TrailManager();
	velocityManager = new VelocityManager();
	aiManager = new AIManager();

	// Generators
	antGenerator = new AntGenerator(
		entityManager,
		positionManager,
		colorManager,
		foodManager,
		velocityManager,
		aiManager
	);
	trailGenerator = new TrailGenerator(
		entityManager,
		positionManager,
		colorManager,
		trailManager
	);
	foodGenerator = new FoodGenerator(
		entityManager,
		positionManager,
		colorManager,
		foodManager
	);

	// Systems
	inputSystem = new InputSystem(
		this,
		&(this->screenOffset)
	);
	renderSystem = new RenderSystem(
		entityManager,
		positionManager,
		colorManager,
		&(this->screenOffset),
		this
	);
	resourceSystem = new ResourceSystem(
		entityManager,
		positionManager,
		colorManager,
		trailManager,
		foodManager,
		velocityManager,
		aiManager
	);
	aiSystem = new AISystem(
		entityManager,
		positionManager,
		velocityManager,
		aiManager
	);
	physicsSystem = new PhysicsSystem(
		entityManager,
		positionManager,
		velocityManager
	);
	frameNumber = 0;
	starting_conditions_setup();
	return true;
}

bool MainEngine::OnUserUpdate(float fElapsedTime) {
	frameNumber += 1;
	frameNumber %= 1000000;
	inputSystem->step(fElapsedTime);
	renderSystem->step();
	std::vector<std::vector<Collision>> collisions = collision_system(*entityManager, *positionManager, *velocityManager);
	resourceSystem->step(collisions, this->frameNumber);
	aiSystem->step(collisions);
	physicsSystem->step(collisions);
	return true;
}

bool MainEngine::OnUserDestroy() {

	// Generators
	delete antGenerator;
	delete trailGenerator;
	delete foodGenerator;

	// Systems
	delete inputSystem;
	delete renderSystem;
	delete resourceSystem;
	delete aiSystem;
	delete physicsSystem;

	// Managers
	delete entityManager;
	delete positionManager;
	delete colorManager;
	delete foodManager;
	delete trailManager;
	delete velocityManager;

	return true;
}

void MainEngine::starting_conditions_setup()
{
	/*for (int i{}; i < 20; i++) {
		int x = rand() % (ScreenWidth() / 8);
		int y = rand() % (ScreenHeight() / 8);
		x -= screenOffset.xOffset/8;
		y -= screenOffset.yOffset/8;
		antGenerator->new_ant({ x, y, 1 });
	}*/
	for (int i{}; i < 5; i++) {
		int x = rand() % ScreenWidth();
		int y = rand() % ScreenHeight();
		x -= screenOffset.xOffset;
		y -= screenOffset.yOffset;
		foodGenerator->new_food_cluster(3, 50, { x, y, 1 });
	}
	Entity home = entityManager->create_entity();
	positionManager->add_entity_component({ home,{ 0,0,1 } });
	int32_t green = color_to_int({ 0, 255, 0, 255 });
	Array2D<int32_t> homeArray(3, 3,
		{ green, green, green,
		green, 0,     green,
		green, green, green }
	);
	colorManager->add_entity_component(home, homeArray);
	foodManager->add_entity_component({ home, 100 });
	aiManager->add_entity_component({ home, AICodes::Home });
}
