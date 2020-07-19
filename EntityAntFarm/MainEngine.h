#pragma once
#include "olcPixelGameEngine.h"
#include "EntityManager.h"
#include <array>
class MainEngine :
	public olc::PixelGameEngine
{
private:
	std::array<float, 3> screenOffset{0., 0., 1.};

public:
	MainEngine();

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;
};

