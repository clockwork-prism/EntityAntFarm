#include "physics_system.h"

void physics_system(const EntityManager entityManager, PhysicsManager& physics, float elapsedTime)
{
	for (size_t i{}; i < physics.transform.size(); i++) {
		if (entityManager.is_alive(physics.transform_at(i).entity)) {
			physics.transform_at(i).data.at(0) += physics.velocity_at(i).at(0);
			physics.transform_at(i).data.at(1) += physics.velocity_at(i).at(1);
		}
		else {
			physics.delete_component(i);
		}
	}
}
