#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "olcPixelGameEngine.h"
#include "Managers.h"
#include "ColorManager.h"
#include "ScreenOffset.h"
#include <iostream>

void render_system(
	const EntityManager& entityManager, 
	const PositionManager &position, 
	const ColorManager& color,
	const ScreenOffset& offset,
	olc::PixelGameEngine* engine);

void _render_color(
	const ColorManager& color, 
	std::vector<Position>::const_iterator& it,
	const ScreenOffset& offset,
	olc::PixelGameEngine* engine);

void _render_pixel(
	const int32_t& icolor, 
	olc::PixelGameEngine* engine,
	std::vector<Position>::const_iterator& it,
	const ScreenOffset& offset);

void _render_pixel_array(
	const ColorManager& color, 
	olc::PixelGameEngine* engine, 
	std::vector<Position>::const_iterator& it,
	const ScreenOffset& offset);