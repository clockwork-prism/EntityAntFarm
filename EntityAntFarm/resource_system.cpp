#include "resource_system.h"

const uint32_t TRAIL_MAX = 10000;
const uint32_t TRAIL_INCR = 2000;
const uint32_t TRAIL_DECAY = 50;


void resource_system(EntityManager& entityManager, PositionManager& positions, TrailManager& trails, ColorManager& colors, std::vector<std::vector<Collision>>& collisionMap)
{
	_update_trails(entityManager, positions, trails, colors, collisionMap);
}


void _update_trails(EntityManager& entityManager, PositionManager& positions, TrailManager& trails, ColorManager& colors, std::vector<std::vector<Collision>>& collisionMap)
{
	NewTrailManagers newTrailManagers{ &entityManager, &trails, &colors, &positions };
	for (auto collisionVector : collisionMap) {
		std::pair<bool, std::array<int32_t, 3>> newTrailPosition = { true, collisionVector.at(0).first.data };
		for (size_t i{ 1 }; i < collisionVector.size(); i++) {
			Collision collision = collisionVector.at(i);
			auto it = trails.find(collision.first.entity);
			if (collision.second == 0 && it != trails.end()) {
				_incremenet_trail(it, colors, newTrailPosition);
				newTrailPosition.first = false;
			}
		}
		if (newTrailPosition.first) {
			new_trail(TRAIL_INCR, newTrailPosition.second, newTrailManagers);
		}
	}
	std::vector<Entity> toDelete{};
	for (auto it = trails.begin(); it != trails.end(); it++) {
		if (it->data > TRAIL_DECAY) {
			it->data -= TRAIL_DECAY;
			auto cit = colors.iter_at(it->entity);
			_update_trail_color(cit, it);
		}
		else {
			toDelete.push_back(it->entity);
		}
	}
	for (auto e : toDelete) {
		entityManager.destroy_entity(e);
		trails.remove_entity_component(e);
		positions.remove_entity_component(e);
		colors.remove_entity_component(e);
	}
}

void _incremenet_trail(std::vector<Component<uint32_t>>::iterator & trailIterator, ComponentManager<Component<int32_t>, std::vector>& colors, std::pair<bool, std::array<int32_t, 3Ui64>>& newTrail)
{
	auto cit = colors.iter_at(trailIterator->entity);
	trailIterator->data += TRAIL_INCR;
	if (trailIterator->data > TRAIL_MAX) trailIterator->data = TRAIL_MAX;
}

void _update_trail_color(std::vector<Component<int32_t>>::iterator& cit, std::vector<Component<uint32_t>>::iterator& it)
{
	cit->data = color_to_int({ 0, 0, (uint8_t)(255 * (double)it->data / TRAIL_MAX), 255 });
}


