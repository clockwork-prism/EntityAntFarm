#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "olcPixelGameEngine.h"
#include "ManagerMacros.h"
#include "ColorManager.h"
#include <iostream>

void render_system(const EntityManager& entityManager, const POSITION_MANAGER &position, const ColorManager& color, olc::PixelGameEngine* engine);

void _render_color(const ColorManager& color, std::vector<Component<std::array<int32_t, 3Ui64>>>::const_iterator& it, olc::PixelGameEngine* engine);

void _render_pixel(const int32_t& icolor, olc::PixelGameEngine* engine, std::vector<Component<std::array<int32_t, 3Ui64>>>::const_iterator& it);

void _render_pixel_array(const ColorManager& color, olc::PixelGameEngine* engine, std::vector<Component<std::array<int32_t, 3Ui64>>>::const_iterator& it);