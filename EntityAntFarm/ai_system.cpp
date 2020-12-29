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
const double TRAIL_WEIGHT_SEEKING{ 10 };
const double TRAIL_WEIGHT_RETURNING{ 20 };
const int TRAIL_THRESH{ 2 };
const std::array<int, 2> HOME_WEIGHT{ 20, 10 };

struct AIChoice {
	bool awayDirection;
	bool homeDirection;
	double trail;
	bool inHistory;
};

uint8_t theta_to_choice(double theta) {
	int choice = static_cast<int>(round(theta / RANGE));
	if (choice < 0) choice += 8;
	return static_cast<uint8_t>(choice);
}

void AISystem::step()
{
	for (auto ait{ aiManager->begin() }; ait != aiManager->end(); ait++) {
		if (entityManager->is_alive(ait->entity)) {
			if (ait->data & AICodes::Home) {
				
			}
			else {
				_set_ant_ai_state(ait);
				_ant_ai(ait);
			}
		}
	}
}

void AISystem::_set_ant_ai_state(std::vector<AI>::iterator& ait) {
	auto fit = foodManager->iter_at(ait->entity);
	if (fit->data >= AntVals::Max) {
		if (ait->data & AICodes::Seeking) {
			ait->data -= AICodes::Seeking;
			ait->data |= AICodes::Retracing;
		}
	}
	else
		ait->data |= AICodes::Seeking;
	bool foodAdjacent = false;
	auto collisionIt = collisionManager->iter_at(ait->entity);
	if (!collisionIt->foodCollisions.empty()) {
		for (auto& fcol : collisionIt->foodCollisions) {
			auto fit = foodManager->cfind(fcol.first);
			if (fit != foodManager->cend()){ 
				if (fit->data > 0 && fit->kind == GIVER) {
					ait->data |= AICodes::MoreFood;
					if (fcol.second.at(0) < 2) {
						foodAdjacent = true;
						break;
					}
				}
				else if (fit->kind == RECEIVER) {
					auto pit = positionManager->iter_at(ait->entity);
					if (pit->data.at(0) == 0 && pit->data.at(1) == 0 && ait->data & AICodes::MoreFood && ait->data & AICodes::Seeking) {
						ait->data |= AICodes::Retracing;
						break;
					}
				}
			}
		}
	}
	if (ait->data & AICodes::Seeking && foodAdjacent)
		ait->data |= AICodes::Stationary;
}

void AISystem::_ant_ai(std::vector<AI>::iterator& ait)
{
	auto it = velocityManager->iter_at(ait->entity);
	if (ait->data & AICodes::Stationary) {
		_ant_stationary(ait, it);
	}
	else if (ait->data & AICodes::Retracing) {
		_ant_retracing(ait, it);
	}
	else {
		auto collisionIt = collisionManager->iter_at(ait->entity);
		uint8_t choice{ 8 };
		auto pit = positionManager->citer_at(it->entity);
		auto hit = historyManager->iter_at(it->entity);

		for (auto& fcol : collisionIt->foodCollisions) {
			auto fit = foodManager->find(fcol.first);
			if (fit != foodManager->end()) {
				if (ait->data & AICodes::Seeking) {
					if (fit->data > 0 && fit->kind == GIVER) {
						choice = (theta_to_choice(fcol.second.at(1)) + 4) % 8;
						break;
					}
				}
				else if (fit->kind == RECEIVER) {
					choice = (theta_to_choice(fcol.second.at(1)) + 4) % 8;
					break;
				}
			}
		}

		if (choice == 8) {

			std::vector<AIChoice> pool{
				{false, false, 0, false},
				{false, false, 0, false},
				{false, false, 0, false},
				{false, false, 0, false},
				{false, false, 0, false},
				{false, false, 0, false},
				{false, false, 0, false},
				{false, false, 0, false}
			};

			double theta = atan2(pit->data.at(1), pit->data.at(0));
			int dir = static_cast<int>(round(theta / RANGE));
			if (dir < 0) dir += 8;
			int rdir = (dir + 4) % 8;

			pool.at(rdir).homeDirection = true;
			pool.at(dir).awayDirection = true;
			for (size_t i{ 0 }; i < hit->size()/2; i += 2) {
				int32_t targetx = hit->data_at(i);
				int32_t targety = hit->data_at(i + 1);
				uint8_t ichoice = _velocity_to_choice({ targetx - pit->data.at(0), targety - pit->data.at(1) });
				if (ichoice < 8) {
					pool.at(ichoice).inHistory = true;
					if (ichoice == 7) {
						pool.at(0).inHistory = true;
						pool.at(6).inHistory = true;
					}
					else if (ichoice == 0) {
						pool.at(7).inHistory = true;
						pool.at(1).inHistory = true;
					}
					else {
						pool.at(ichoice - 1).inHistory = pool.at(ichoice + 1).inHistory = true;
					}
				}
			}

			for (auto& tcol : collisionIt->trailCollisions) {
				auto tit = trailManager->find(tcol.first);
				if (tit != trailManager->end() && tcol.second.at(0) > 0) {
					int tdir = static_cast<int>(round(tcol.second.at(1) / RANGE));
					if (tdir < 0) tdir += 8;
					pool.at((tdir + 4) % 8).trail = tit->data / pow(tcol.second.at(0), 2);
				}
			}

			decisionVector.clear();
			for (uint8_t i{}; i < pool.size(); i++) {
				AIChoice ac = pool.at(i);
				if (ac.inHistory)
					continue;
				size_t n{1};
				size_t nl{};
				size_t nr{};
				int ir, il;
				ir = i + 1;
				il = i - 1;
				if (ir == 8)
					ir = 0;
				if (il == -1)
					il = 7;
				if (ait->data & AICodes::Seeking) {
					if (ac.homeDirection)
						continue;
					n += static_cast<size_t>(((double)ac.trail) / TrailIncr::Increase * TRAIL_WEIGHT_SEEKING);
					if (ac.awayDirection && pit->data.at(0) > 0 && pit->data.at(1) > 0) {
						n += HOME_WEIGHT.at(0);
						nr += HOME_WEIGHT.at(1);
						nl += HOME_WEIGHT.at(1);
					}
				}
				else {
					if (ac.awayDirection)
						continue;
					n += static_cast<size_t>(((double)ac.trail) / TrailIncr::Increase * TRAIL_WEIGHT_RETURNING);
					if (ac.homeDirection) {
						n += HOME_WEIGHT.at(0);
						nr += HOME_WEIGHT.at(1);
						nl += HOME_WEIGHT.at(1);
					}
				}
				for (int j{}; j < n; j++)
					decisionVector.push_back(i);
				for (int j{}; j < nr; j++)
					decisionVector.push_back(ir);
				for (int j{}; j < nl; j++)
					decisionVector.push_back(nl);
			}
			if (decisionVector.empty())
				choice = rand() % 8;
			else
				choice = decisionVector.at(rand() % decisionVector.size());
		}
		std::array<int, 2> deltav = _choice_to_velocity(choice);
		if (deltav.at(0) == 0 && deltav.at(1) == 0) {
			deltav.at(0) = it->data.at(0);
			deltav.at(1) = it->data.at(1);
		}
		it->data.at(0) = it->data.at(2);
		it->data.at(1) = it->data.at(3);
		it->data.at(2) = deltav.at(0);
		it->data.at(3) = deltav.at(1);
		hit->update_history(pit->data.at(0), pit->data.at(1));
	}
}

void AISystem::_ant_retracing(std::vector<AI>::iterator& ait, std::vector<Velocity>::iterator& it)
{
	auto pit = positionManager->citer_at(ait->entity);
	auto hit = historyManager->iter_at(ait->entity);
	size_t place{ static_cast<size_t>(hit->back()) };
	int32_t targetx = hit->data_at(place);
	int32_t targety = hit->data_at(place + 1);
	std::array<int32_t, 2> deltav{ targetx - pit->data.at(0), targety - pit->data.at(1) };
	hit->set_back(hit->back() + 2);
	if (hit->back() > (hit->size() - 3)) {
		ait->data -= AICodes::Retracing;
		hit->set_back(0);
		hit->reverse();
		if (ait->data & AICodes::Seeking && ait->data & AICodes::MoreFood)
			ait->data -= AICodes::MoreFood;
	}
	if (deltav.at(0) > 5 || deltav.at(1) > 5)
		deltav.at(0) = 0;
	it->data.at(0) = it->data.at(2);
	it->data.at(1) = it->data.at(3);
	it->data.at(2) = deltav.at(0);
	it->data.at(3) = deltav.at(1);
}

uint8_t AISystem::_ant_seeking(std::vector<uint8_t>& pool)
{
	for (size_t i{}; i < decisionVector.size(); i++) {
		decisionVector.at(i) = pool.at(i % pool.size());
	}
	return decisionVector.at(rand() % decisionVector.size());
}

void AISystem::_ant_stationary(std::vector<AI>::iterator& ait, std::vector<Velocity>::iterator& it)
{
	ait->data -= AICodes::Stationary;
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

uint8_t AISystem::_velocity_to_choice(const std::array<int, 2> vel)
{	
	uint8_t choice{};
	if (vel.at(0) == 1 && vel.at(1) == 0)
		choice = 0;
	else if (vel.at(0) == 1 && vel.at(1) == 1)
		choice = 1;
	else if (vel.at(0) == 0 && vel.at(1) == 1)
		choice = 2;
	else if (vel.at(0) == -1 && vel.at(1) == 1)
		choice = 3;
	else if (vel.at(0) == -1 && vel.at(1) == 0)
		choice = 4;
	else if (vel.at(0) == -1 && vel.at(1) == -1)
		choice = 5;
	else if (vel.at(0) == 0 && vel.at(1) == -1)
		choice = 6;
	else if (vel.at(0) == 1 && vel.at(1) == -1)
		choice = 7;
	else choice = 8;
	return choice;
}

bool AISystem::_choice_valid(const uint8_t& choice, std::vector<History>::iterator& it)
{
	
	return true;
}
