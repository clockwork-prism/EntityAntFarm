#include "Managers.h"

Entity new_trail(NewTrail& newTrail, EntityManager& entityManager, TrailManager& trails, ColorManager& colors, PositionManager& positions)
{
    Entity newEntity = entityManager.create_entity();
	trails.add_entity_component({ newEntity, newTrail.trail });
	positions.add_entity_component({ newEntity, newTrail.position });
	colors.add_entity_component({ newEntity, newTrail.color });
    return newEntity;
}

Entity new_ant(NewAnt& newAnt, EntityManager& entityManager, PositionManager& positions, ColorManager& colors, VelocityManager& velocities)
{
	Entity newEntity = entityManager.create_entity();
	positions.add_entity_component({ newEntity, newAnt.position });
	colors.add_entity_component({ newEntity, newAnt.color });
	velocities.add_entity_component({ newEntity, newAnt.velocity });
	return newEntity;
}
