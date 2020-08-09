#include "ai_system.h"

void ai_system(const EntityManager& entityManager, PhysicsManager& physics)
{
	for (size_t i{}; i < physics.velocity.size(); i++) {
		physics.velocity_at(i).at(0) = rand() % 3 - 1;
		physics.velocity_at(i).at(1) = rand() % 3 - 1;
	}
}
