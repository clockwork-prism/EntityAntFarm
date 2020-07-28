#pragma once
#include "olcPixelGameEngine.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "PositionManager.h"
#include <array>
#include <vector>
class MainEngine :
	public olc::PixelGameEngine
{
private:
	std::array<float, 3> screenOffset{0., 0., 1.};

	EntityManager entityManager;

	PositionManager _position;


public:
	MainEngine();

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;

	void _EAF_RenderSystem(const PositionManager &position);
};

