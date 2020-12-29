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
				if (vit->data[2] != 0 || vit->data[3] != 0) {
					positionManager->update_bucket(
						{pit->entity,
						{pit->data[0] + vit->data[2], pit->data[1] + vit->data[3], pit->data[2]}
						}
					);
				}
			}
			catch (std::out_of_range& ex) {
				std::cerr << ex.what();
			}
		}
	}
}
