#pragma once
#include "ScreenOffset.h"
#include "olcPixelGameEngine.h"

class InputSystem {
private:
	olc::PixelGameEngine* engine;
	ScreenOffset* offset;
public:
	InputSystem(
		olc::PixelGameEngine* _engine,
		ScreenOffset* _offset
	) : engine{ _engine },
		offset{ _offset } {}
	void step(const float fElapsedTime);
};