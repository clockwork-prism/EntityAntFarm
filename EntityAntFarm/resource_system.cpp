#include "resource_system.h"


void ResourceSystem::step(std::vector<std::vector<Collision>>& collisionMap)
{
	_update_trails(collisionMap);
	_transfer_food(collisionMap);
}


void ResourceSystem::_update_trails(std::vector<std::vector<Collision>>& collisionMap)
{
	TrailGenerator trailGenerator(
		this->entityManager,
		this->positionManager,
		this->colorManager,
		this->trailManager
	);
	for (auto collisionVector : collisionMap) {
		std::pair<bool, std::array<int32_t, 3>> newTrailPosition = { true, collisionVector.at(0).first.data };
		for (size_t i{ 1 }; i < collisionVector.size(); i++) {
			Collision collision = collisionVector.at(i);
			auto it = this->trailManager->find(collision.first.entity);
			if (collision.second == 0 && it != this->trailManager->end()) {
				_incremenet_trail(it, newTrailPosition);
				newTrailPosition.first = false;
			}
		}
		if (newTrailPosition.first) {
			trailGenerator.new_trail(TRAIL_INCR, newTrailPosition.second);
		}
	}
	std::vector<Entity> toDelete{};
	for (auto it = this->trailManager->begin(); it != this->trailManager->end(); it++) {
		if (it->data > TRAIL_DECAY) {
			it->data -= TRAIL_DECAY;
			auto cit = this->colorManager->iter_at(it->entity);
			_update_trail_color(cit, it);
		}
		else {
			toDelete.push_back(it->entity);
		}
	}
	for (auto e : toDelete) {
		this->entityManager->destroy_entity(e);
		this->trailManager->remove_entity_component(e);
		this->positionManager->remove_entity_component(e);
		this->colorManager->remove_entity_component(e);
	}
}

void ResourceSystem::_incremenet_trail(std::vector<Trail>::iterator & trailIterator, std::pair<bool, std::array<int32_t, 3Ui64>>& newTrail)
{
	auto cit = this->colorManager->iter_at(trailIterator->entity);
	trailIterator->data += TRAIL_INCR;
	if (trailIterator->data > TRAIL_MAX) trailIterator->data = TRAIL_MAX;
}

void ResourceSystem::_update_trail_color(std::vector<Color>::iterator& cit, std::vector<Trail>::iterator& it)
{
	cit->data = color_to_int({ 0, 0, (uint8_t)(255 * (double)it->data / TRAIL_MAX), 255 });
}

void ResourceSystem::_transfer_food(std::vector<std::vector<Collision>>& collisionMap) {
	for (auto collisionVector : collisionMap) {
		for (size_t i{ 1 }; i < collisionVector.size(); i++) {
			
		}
	}
}
