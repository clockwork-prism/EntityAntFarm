#include "resource_system.h"


void ResourceSystem::step(uint32_t frameNumber)
{
	_update_trails();
	_transfer_food(frameNumber);
}


void ResourceSystem::_update_trails()
{
	for (auto cit = collisionManager->begin(); cit != collisionManager->end(); cit++) {
		auto pit = positionManager->iter_at(cit->entity);
		std::pair<bool, std::array<int32_t, 3>> newTrailPosition = { true, pit->data };
		newTrailPosition.second.at(2) = 0;
		auto tcol = cit->trailCollisions;
		for (size_t i{ 0 }; i < tcol.size(); i++) {
			auto it = this->trailManager->iter_at(tcol.at(i).first);
			if (tcol.at(i).second.at(0) == 0) {
				_incremenet_trail(it, newTrailPosition);
				newTrailPosition.first = false;
			}
		}
		if (newTrailPosition.first) {
			trailGenerator->new_trail(TrailIncr::Increase, newTrailPosition.second);
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
		trailGenerator->destroy_trail(e);
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
	cit->data = color_to_int({ 0, 0, 255, (uint8_t)(255 * (double)it->data / TrailIncr::Max) });
}

void ResourceSystem::_transfer_food(uint32_t frameNumber) {
	std::vector<Entity> toDelete{};
	for (auto cit = collisionManager->begin(); cit != collisionManager->end(); cit++) {
		if (!(cit->foodCollisions.empty())) {
			auto antPit = this->positionManager->iter_at(cit->entity);
			auto antFit = this->foodManager->iter_at(cit->entity);
			auto antAit = this->aiManager->iter_at(antFit->entity);
			auto fit = this->foodManager->end();

			for (auto& fcol : cit->foodCollisions) {
				if (fcol.second.at(0) < 2 && fcol.second.at(2) != TRANSPORTER) {
					fit = foodManager->iter_at(fcol.first);
					break;
				}
			}

			if (fit != foodManager->end()) {
				if (fit->kind == GIVER && fit->data > 0 && (antAit->data & AICodes::Seeking)) {
					fit->data -= 1;
					antFit->data += 1;
					if (fit->data == 0)
						toDelete.push_back(fit->entity);
				}
				else if (fit->kind == RECEIVER && antFit->data > 0 &&
					antPit->data.at(0) == 0 && antPit->data.at(1) == 0) {
					fit->data += antFit->data;
					antFit->data = 0;
				}

			}
		}
	}
	for (auto e : toDelete) foodGenerator->destroy_food(e);
	if (frameNumber % 10 == 0) {
		auto it{ foodManager->begin() };
		while (it->kind != RECEIVER) {
			it++;
		}
		if (it->data > AntVals::Thresh) {
			it->data -= AntVals::Thresh;
			antGenerator->new_ant({ 0, 0, 2 });
		}
	}
}
