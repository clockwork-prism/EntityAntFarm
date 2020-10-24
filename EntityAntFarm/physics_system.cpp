#include "physics_system.h"

void physics_system(const EntityManager& entityManager, PositionManager& position, VelocityManager& velocity, std::vector<std::vector<Collision>>& collisionMap)
{
	_update_positions(velocity, entityManager, position);
}

void _update_positions(VelocityManager& velocity, const EntityManager& entityManager, PositionManager& position)
{
	for (auto vit{ velocity.begin() }; vit != velocity.end(); vit++) {
		if (entityManager.is_alive(vit->entity)) {
			try {
				auto pit{ position.iter_at(vit->entity) };
				pit->data[0] += vit->data[2];
				pit->data[1] += vit->data[3];
			}
			catch (std::out_of_range& ex) {
				std::cerr << ex.what();
			}
		}
	}
}
