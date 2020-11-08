#pragma once

#include "Managers.h"
#include "Generators.h"
#include "EntityManager.h"
#include "ColorManager.h"

void resource_system(EntityManager& entityManager, PositionManager& positions, TrailManager& trails, ColorManager& colors, std::vector<std::vector<Collision>>& collisionMap);

void _update_trails(EntityManager& entityManager, PositionManager& positions, TrailManager& trails, ColorManager& colors, std::vector<std::vector<Collision>>& collisionMap);
void _create_trail(std::pair<bool, std::array<int32_t, 3Ui64>>& newTrailPosition, EntityManager& entityManager, ComponentManager<Component<uint32_t>, std::vector>& trails, ColorManager& colors, ComponentManager<Component<std::array<int32_t, 3Ui64>>, std::vector>& positions);

void _incremenet_trail(std::vector<Component<uint32_t>>::iterator & trailIterator, ComponentManager<Component<int32_t>, std::vector>& colors, std::pair<bool, std::array<int32_t, 3Ui64>>& newTrail);

void _update_trail_color(std::vector<Component<int32_t>>::iterator& cit, std::vector<Component<uint32_t>>::iterator& it);

