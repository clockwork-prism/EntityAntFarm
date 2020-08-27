#include "physics_system.h"

void physics_system(const EntityManager& entityManager, POSITION_MANAGER& position, VELOCITY_MANAGER& velocity, std::vector<std::vector<COLLISION>>& collisionMap)
{
	_update_positions(velocity, entityManager, position);
}

void _update_positions(VELOCITY_MANAGER& velocity, const EntityManager& entityManager, POSITION_MANAGER& position)
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
