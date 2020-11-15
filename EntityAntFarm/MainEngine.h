#pragma once
#include "olcPixelGameEngine.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "Managers.h"
#include "Generators.h"
#include "ColorManager.h"
#include "render_system.h"
#include "physics_system.h"
#include "collision_system.h"
#include "resource_system.h"
#include "ai_system.h"
#include "input_system.h"
#include <array>
#include <vector>
class MainEngine :
	public olc::PixelGameEngine
{
private:
	ScreenOffset screenOffset;

	EntityManager* entityManager;
	PositionManager* positionManager;
	VelocityManager* velocityManager;
	ColorManager* colorManager;
	TrailManager* trailManager;
	FoodManager* foodManager;

	AntGenerator* antGenerator;
	TrailGenerator* trailGenerator;
	FoodGenerator* foodGenerator;

	InputSystem* inputSystem;
	RenderSystem* renderSystem;
	ResourceSystem* resourceSystem;
	AISystem* aiSystem;
	PhysicsSystem* physicsSystem;

public:
	MainEngine();

	bool OnUserCreate() override;

	void starting_conditions_setup();

	bool OnUserUpdate(float fElapsedTime) override;

	bool OnUserDestroy() override;
};

