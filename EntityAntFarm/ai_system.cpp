#include "ai_system.h"
// 1.5708
// 0.785398
// 0
// - 0.785398
// - 1.5708
// - 2.35619
// 3.14159
// 2.35619

const double RANGE{ 0.78539816339 };
const double THRESH{ 0.146365203 };
void AISystem::step()
{
	for (auto ait{ aiManager->begin() }; ait != aiManager->end(); ait++) {
		if (entityManager->is_alive(ait->entity)) {
			if (ait->data & AICodes::Home) {
				
			}
			else {
				_ant_ai(ait);
			}
		}
	}
}

void AISystem::_ant_ai(std::vector<Trail>::iterator& ait)
{
	auto it = velocityManager->iter_at(ait->entity);
	if (ait->data & AICodes::Stationary) {
		_ant_stationary(ait, it);
	}
	else {
		auto pit = positionManager->citer_at(it->entity);
		std::vector<uint8_t> pool{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
		double theta = atan2(pit->data.at(1), pit->data.at(0));
		int dir = static_cast<int>(round(theta / RANGE));
		if (dir < 0) dir += 8;
		int rdir = (dir + 4) % 8;
		uint8_t choice;
		if (ait->data & AICodes::Seeking) {
			pool.at(rdir) = static_cast<uint8_t>(dir);
			choice = _ant_seeking(pool);
		}
		else {
			choice = rdir;
		}
		std::array<int, 2> deltav = _choice_to_velocity(choice);
		it->data.at(2) = deltav.at(0);
		it->data.at(3) = deltav.at(1);
	}
}

uint8_t AISystem::_ant_seeking(std::vector<uint8_t>& pool)
{
	for (size_t i{}; i < decisionVector.size(); i++) {
		decisionVector.at(i) = pool.at(i % 8);
	}
	return decisionVector.at(rand() % decisionVector.size());
}

void AISystem::_ant_stationary(std::vector<Trail>::iterator& ait, std::vector<Velocity>::iterator& it)
{
	ait->data ^= ait->data | AICodes::Stationary;
	it->data.at(2) = it->data.at(3) = 0;
}

std::array<int, 2> AISystem::_choice_to_velocity(const uint8_t& choice)
{
	std::array<int, 2> vel{};
	switch (choice) {
	case 0:
		vel.at(0) = 1;
		vel.at(1) = 0;
		break;
	case 1:
		vel.at(0) = 1;
		vel.at(1) = 1;
		break;
	case 2:
		vel.at(0) = 0;
		vel.at(1) = 1;
		break;
	case 3:
		vel.at(0) = -1;
		vel.at(1) = 1;
		break;
	case 4:
		vel.at(0) = -1;
		vel.at(1) = 0;
		break;
	case 5:
		vel.at(0) = -1;
		vel.at(1) = -1;
		break;
	case 6:
		vel.at(0) = 0;
		vel.at(1) = -1;
		break;
	case 7:
		vel.at(0) = 1;
		vel.at(1) = -1;
		break;
	default:
		vel.at(0) = 0;
		vel.at(1) = 0;
	}
	return vel;
}

bool AISystem::_choice_valid(const uint8_t& choice, std::vector<History>::iterator& it)
{
	
	return true;
}
