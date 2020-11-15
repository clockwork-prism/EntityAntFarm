#include "ai_system.h"

void AISystem::step()
{
	for (auto it{ velocityManager->begin() }; it != velocityManager->end(); it++) {
		if (entityManager->is_alive(it->entity)) {
			int x_v = rand() % 3 - 1;
			int y_v = rand() % 3 - 1;
			it->data[2] = x_v;
			it->data[3] = y_v;
		}
	}
}
