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
void AISystem::step(std::vector<std::vector<Collision>>& collisionMap)
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
		ait->data -= AICodes::Stationary;
		it->data.at(2) = it->data.at(3) = 0;
	}
	else {
		auto pit = positionManager->citer_at(it->entity);
		std::vector<uint8_t> pool{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
		double theta = atan2(pit->data.at(1), pit->data.at(0));
		int dir = static_cast<int>(round(theta / RANGE));
		if (dir < 0) dir += 8;
		int rdir = (dir + 4) % 8;
		pool.at(rdir) = static_cast<uint8_t>(dir);
		for (size_t i{}; i < decisionVector.size(); i++) {
			decisionVector.at(i) = pool.at(i % 8);
		}
		uint8_t choice = decisionVector.at(rand() % decisionVector.size());
		_choice_to_velocity(choice, it);
	}
}

void AISystem::_choice_to_velocity(const uint8_t& choice, std::vector<Velocity>::iterator& it)
{
	switch (choice) {
	case 0:
		it->data.at(2) = 1;
		it->data.at(3) = 0;
		break;
	case 1:
		it->data.at(2) = 1;
		it->data.at(3) = 1;
		break;
	case 2:
		it->data.at(2) = 0;
		it->data.at(3) = 1;
		break;
	case 3:
		it->data.at(2) = -1;
		it->data.at(3) = 1;
		break;
	case 4:
		it->data.at(2) = -1;
		it->data.at(3) = 0;
		break;
	case 5:
		it->data.at(2) = -1;
		it->data.at(3) = -1;
		break;
	case 6:
		it->data.at(2) = 0;
		it->data.at(3) = -1;
		break;
	case 7:
		it->data.at(2) = 1;
		it->data.at(3) = -1;
		break;
	default:
		it->data.at(2) = 0;
		it->data.at(3) = 0;
	}
}
