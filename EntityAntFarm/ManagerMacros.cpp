#include "ManagerMacros.h"

Entity new_trail(NewTrail& newTrail, EntityManager& entityManager, TRAIL_MANAGER& trails, ColorManager& colors, POSITION_MANAGER& positions)
{
    Entity newEntity = entityManager.create_entity();
	trails.add_entity_component({ newEntity, newTrail.trail });
	positions.add_entity_component({ newEntity, newTrail.position });
	colors.add_entity_component({ newEntity, newTrail.color });
    return newEntity;
}

Entity new_ant(NewAnt& newAnt, EntityManager& entityManager, POSITION_MANAGER& positions, ColorManager& colors, VELOCITY_MANAGER& velocities)
{
	Entity newEntity = entityManager.create_entity();
	positions.add_entity_component({ newEntity, newAnt.position });
	colors.add_entity_component({ newEntity, newAnt.color });
	velocities.add_entity_component({ newEntity, newAnt.velocity });
	return newEntity;
}
