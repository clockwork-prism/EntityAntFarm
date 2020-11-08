#pragma once
#include "olcPixelGameEngine.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "Managers.h"
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

	EntityManager entityManager;

	PositionManager positionManager;
	VelocityManager velocityManager;
	ColorManager colorManager;
	TrailManager _trail;

public:
	MainEngine();

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;
};

