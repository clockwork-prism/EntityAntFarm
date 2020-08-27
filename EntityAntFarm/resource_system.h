#pragma once

#include "ManagerMacros.h"
#include "EntityManager.h"

void resource_system(EntityManager& entityManager, POSITION_MANAGER& positions, TRAIL_MANAGER& trails, COLOR_MANAGER& colors, std::vector<std::vector<COLLISION>>& collisionMap);

void _update_trails(EntityManager& entityManager, POSITION_MANAGER& positions, TRAIL_MANAGER& trails, COLOR_MANAGER& colors, std::vector<std::vector<COLLISION>>& collisionMap);
void _create_trail(std::pair<bool, std::array<int32_t, 3Ui64>>& newTrailPosition, EntityManager& entityManager, ComponentManager<Component<uint32_t>, std::vector>& trails, ComponentManager<Component<int32_t>, std::vector>& colors, ComponentManager<Component<std::array<int32_t, 3Ui64>>, std::vector>& positions);

void _incremenet_trail(std::vector<Component<uint32_t>>::iterator & trailIterator, ComponentManager<Component<int32_t>, std::vector>& colors, std::pair<bool, std::array<int32_t, 3Ui64>>& newTrail);

void _update_trail_color(std::vector<Component<int32_t>>::iterator& cit, std::vector<Component<uint32_t>>::iterator& it);

