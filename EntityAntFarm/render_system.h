#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "olcPixelGameEngine.h"
#include "ManagerMacros.h"
#include <iostream>

void render_system(const EntityManager& entityManager, const POSITION_MANAGER &position, const COLOR_MANAGER& color, olc::PixelGameEngine* engine);

std::array<uint8_t, 4> int_to_color(int32_t iColor);

int32_t color_to_int(std::array<uint8_t, 4> aColor);