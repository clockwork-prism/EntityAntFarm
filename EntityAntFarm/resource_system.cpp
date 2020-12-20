#include "resource_system.h"


void ResourceSystem::step(uint32_t frameNumber)
{
	_update_trails();
	_transfer_food(frameNumber);
}


void ResourceSystem::_update_trails()
{
	TrailGenerator trailGenerator(
		this->entityManager,
		this->positionManager,
		this->colorManager,
		this->trailManager
	);
	for (auto cit = collisionManager->begin(); cit != collisionManager->end(); cit++) {
		auto pit = positionManager->iter_at(cit->entity);
		std::pair<bool, std::array<int32_t, 3>> newTrailPosition = { true, pit->data };
		for (size_t i{ 0 }; i < cit->data.size(); i++) {
			Collision collision = cit->data.at(i);
			auto it = this->trailManager->find(collision.first.entity);
			if (collision.second == 0 && it != this->trailManager->end()) {
				_incremenet_trail(it, newTrailPosition);
				newTrailPosition.first = false;
			}
		}
		if (newTrailPosition.first) {
			trailGenerator.new_trail(TrailIncr::Increase, newTrailPosition.second);
		}
	}
	std::vector<Entity> toDelete{};
	for (auto it = this->trailManager->begin(); it != this->trailManager->end(); it++) {
		if (it->data > TrailIncr::Decay) {
			it->data -= TrailIncr::Decay;
			auto cit = this->colorManager->iter_at(it->entity);
			_update_trail_color(cit, it);
		}
		else {
			toDelete.push_back(it->entity);
		}
	}
	for (auto e : toDelete) {
		trailGenerator.destroy_trail(e);
	}
}

void ResourceSystem::_incremenet_trail(std::vector<Trail>::iterator & trailIterator, std::pair<bool, std::array<int32_t, 3Ui64>>& newTrail)
{
	auto cit = this->colorManager->iter_at(trailIterator->entity);
	trailIterator->data += TrailIncr::Increase;
	if (trailIterator->data > TrailIncr::Max) trailIterator->data = TrailIncr::Max;
}

void ResourceSystem::_update_trail_color(std::vector<Color>::iterator& cit, std::vector<Trail>::iterator& it)
{
	cit->data = color_to_int({ 0, 0, (uint8_t)(255 * (double)it->data / TrailIncr::Max), 255 });
}

void ResourceSystem::_transfer_food(uint32_t frameNumber) {
	FoodGenerator foodGenerator{
		this->entityManager,
		this->positionManager,
		this->colorManager,
		this->foodManager
	};
	std::vector<Entity> toDelete{};
	for (auto cit = collisionManager->begin(); cit != collisionManager->end(); cit++) {
		auto antPit = this->positionManager->iter_at(cit->entity);
		auto antFit = this->foodManager->iter_at(cit->entity);
		for (size_t i{ 0 }; i < cit->data.size(); i++) {
			Collision col = cit->data.at(i);
			if (col.second < 2) {
				auto fit = this->foodManager->find(col.first.entity);
				if (fit != this->foodManager->end() && fit->data > 0) {
					auto ait = this->aiManager->find(col.first.entity);
					if (ait == this->aiManager->end()) {
						auto antAit = this->aiManager->iter_at(antFit->entity);
						if (antFit->data >= AntVals::Max) {
							if (antAit->data & AICodes::Seeking) antAit->data -= AICodes::Seeking;
						}
						else {
							fit->data -= 1;
							antFit->data += 1;
							antAit->data |= AICodes::Stationary;
							if (fit->data == 0) toDelete.push_back(fit->entity);
							break;
						}
					}
					else if (ait->data & AICodes::Home && antFit->data > 0 &&
							 antPit->data.at(0) == 0 && antPit->data.at(1) == 0) {
						fit->data += antFit->data;
						antFit->data = 0;
						this->aiManager->iter_at(antFit->entity)->data |= AICodes::Seeking;
					}
				}
			}
		}
	}
	for (auto e : toDelete) foodGenerator.destroy_food(e);
	if (frameNumber % 10 == 0) {
		auto it{ aiManager->begin() };
		while (!(it->data & AICodes::Home)) {
			it++;
		}
		auto fit = foodManager->find(it->entity);
		if (fit->data > AntVals::Thresh) {
			fit->data -= AntVals::Thresh;
			antGenerator->new_ant({ 0, 0, 0 });
		}
	}
}
