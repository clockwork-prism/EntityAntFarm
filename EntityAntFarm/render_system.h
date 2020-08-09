#pragma once
#include "Position.h"
#include "EntityManager.h"
#include "olcPixelGameEngine.h"

#include <array>

static const int32_t CHAR_MASK = (1 << 8) - 1;

void render_system(const EntityManager entityManager, const std::vector<PositionComponent>& position, const std::vector<int32_t>& color, olc::PixelGameEngine* engine);

std::array<uint8_t, 3> convert_color(int32_t);

