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
#include <array>
#include <vector>
class MainEngine :
	public olc::PixelGameEngine
{
private:
	std::array<float, 3> screenOffset{0., 0., 1.};

	EntityManager entityManager;

	PositionManager _position;
	VelocityManager _velocity;
	ColorManager _color;
	TrailManager _trail;

public:
	MainEngine();

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;
};

