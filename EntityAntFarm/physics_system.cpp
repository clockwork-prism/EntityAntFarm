#include "physics_system.h"

void PhysicsSystem::step()
{
	_update_positions();
}

void PhysicsSystem::_update_positions()
{
	for (auto vit{ velocityManager->begin() }; vit != velocityManager->end(); vit++) {
		if (entityManager->is_alive(vit->entity)) {
			try {
				auto pit{ positionManager->iter_at(vit->entity) };
				auto hit{ historyManager->iter_at(vit->entity) };
				for (size_t i{ 15 }; i > 1; i--) {
					hit->data.at(i) = hit->data.at(i - 2);
				}
				for (size_t i{}; i < 2; i++)
					hit->data.at(i) = pit->data.at(i);
				pit->data[0] += vit->data[2];
				pit->data[1] += vit->data[3];
			}
			catch (std::out_of_range& ex) {
				std::cerr << ex.what();
			}
		}
	}
}
