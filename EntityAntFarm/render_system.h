#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "olcPixelGameEngine.h"
#include "ManagerMacros.h"

void render_system(const EntityManager& entityManager, const POSITION_MANAGER &position, olc::PixelGameEngine* engine);