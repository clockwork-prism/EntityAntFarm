#include "Generators.h"

Entity new_trail(uint32_t trail, std::array<int32_t, 3> position, NewTrailManagers& managers)
{
    Entity newEntity = managers.entityManager->create_entity();
	managers.trailManager->add_entity_component({ newEntity, trail });
	managers.positionManager->add_entity_component({ newEntity, position });
	managers.colorManager->add_entity_component({ newEntity, color_to_int({ 0, 0, 0, 0 }) });
    return newEntity;
}

Entity new_ant(std::array<int32_t, 3> position, NewAntManagers& managers)
{
	Entity newEntity = managers.entityManager->create_entity();
	managers.positionManager->add_entity_component({ newEntity, position });
	managers.colorManager->add_entity_component({ newEntity, color_to_int({ 255, 255, 255, 255 }) });
	managers.velocityManager->add_entity_component({ newEntity, {0, 0, 0, 0} });
	return newEntity;
}
