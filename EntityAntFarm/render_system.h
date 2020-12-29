#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "olcPixelGameEngine.h"
#include "Managers.h"
#include "ColorManager.h"
#include "misc.h"
#include <iostream>
#include <string>
#include <sstream>

class RenderSystem {
private:
	const EntityManager* entityManager;
	const PositionManager* positionManager;
	const ColorManager* colorManager;
	const ScreenOffset* offset;
	olc::PixelGameEngine* engine;
	std::vector<int> depthBuffer;

	void _render_color(std::vector<Position>::const_iterator& it);

	void _render_pixel(const int32_t& icolor, std::vector<Position>::const_iterator& it);

	void _draw_pixel(int x, int y, int z, const int32_t& icolor);

	void _render_pixel_array(std::vector<Position>::const_iterator& it);

public:
	RenderSystem(
		EntityManager* _entityManager,
		PositionManager* _position,
		ColorManager* _color,
		ScreenOffset* _offset,
		olc::PixelGameEngine* _engine
	) : entityManager{ _entityManager },
		positionManager{ _position},
		colorManager{ _color},
		offset{ _offset},
		engine{ _engine },
		depthBuffer( _engine->ScreenHeight() * _engine->ScreenWidth() + 1 ) {}

	void step(size_t nAnts);
};

