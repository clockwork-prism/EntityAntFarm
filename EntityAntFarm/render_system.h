#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "olcPixelGameEngine.h"
#include "ManagerMacros.h"
#include <iostream>

void render_system(const EntityManager& entityManager, const POSITION_MANAGER &position, const COLOR_MANAGER& color, olc::PixelGameEngine* engine);
