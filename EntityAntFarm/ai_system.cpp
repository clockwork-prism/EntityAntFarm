#include "ai_system.h"

void ai_system(const EntityManager& entityManager, VELOCITY_MANAGER& velocity)
{
	for (auto it{ velocity.begin() }; it != velocity.end(); it++) {
		if (entityManager.is_alive(it->entity)) {
			int x_v = rand() % 3 - 1;
			int y_v = rand() % 3 - 1;
			it->data[2] = x_v;
			it->data[3] = y_v;
		}
	}
}
