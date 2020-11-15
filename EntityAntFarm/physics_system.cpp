#include "physics_system.h"

void PhysicsSystem::step(std::vector<std::vector<Collision>>& collisionMap)
{
	_update_positions();
}

void PhysicsSystem::_update_positions()
{
	for (auto vit{ velocityManager->begin() }; vit != velocityManager->end(); vit++) {
		if (entityManager->is_alive(vit->entity)) {
			try {
				auto pit{ positionManager->iter_at(vit->entity) };
				pit->data[0] += vit->data[2];
				pit->data[1] += vit->data[3];
			}
			catch (std::out_of_range& ex) {
				std::cerr << ex.what();
			}
		}
	}
}
