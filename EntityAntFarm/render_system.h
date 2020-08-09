#pragma once
#include "Position.h"
#include "EntityManager.h"
#include "olcPixelGameEngine.h"

void render_system(const EntityManager entityManager, const std::vector<PositionComponent>& position, olc::PixelGameEngine* engine);

