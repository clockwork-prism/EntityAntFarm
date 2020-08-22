#pragma once
#include "olcPixelGameEngine.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "ManagerMacros.h"
#include "render_system.h"
#include "physics_system.h"
#include "ai_system.h"
#include <array>
#include <vector>
class MainEngine :
	public olc::PixelGameEngine
{
private:
	std::array<float, 3> screenOffset{0., 0., 1.};

	EntityManager entityManager;

	POSITION_MANAGER _position;
	VELOCITY_MANAGER _velocity;
	COLOR_MANAGER _color;


public:
	MainEngine();

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;
};

