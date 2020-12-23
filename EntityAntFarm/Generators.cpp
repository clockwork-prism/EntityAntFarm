#include "Generators.h"

Entity TrailGenerator::new_trail(int32_t trail, std::array<int32_t, 3> position)
{
    Entity newEntity = this->entityManager->create_entity();
	this->trailManager->add_entity_component({ newEntity, trail });
	this->positionManager->add_entity_component({ newEntity, position });
	this->colorManager->add_entity_component({ newEntity, color_to_int({ 0, 0, 0, 0 }) });
    return newEntity;
}

void TrailGenerator::destroy_trail(Entity e) {
	this->trailManager->remove_entity_component(e);
	this->positionManager->remove_entity_component(e);
	this->colorManager->remove_entity_component(e);
	this->entityManager->destroy_entity(e);
}

Entity AntGenerator::new_ant(std::array<int32_t, 3> position)
{
	Entity newEntity = this->entityManager->create_entity();
	this->positionManager->add_entity_component({ newEntity, position });
	this->colorManager->add_entity_component({ newEntity, color_to_int({ 255, 255, 255, 255 }) });
	this->velocityManager->add_entity_component({ newEntity, {0, 0, 0, 0} });
	this->foodManager->add_entity_component({ newEntity, 0 });
	this->aiManager->add_entity_component({ newEntity, AICodes::Seeking });
	this->historyManager->add_entity_component({ newEntity, 0 });
	this->collisionManager->add_entity_component({ newEntity, {}, {} });
	return newEntity;
}

Entity FoodGenerator::new_food(int32_t food, std::array<int32_t, 3> position)
{
	Entity newEntity = this->entityManager->create_entity();
	
	this->foodManager->add_entity_component({ newEntity, food });
	this->colorManager->add_entity_component({ newEntity, color_to_int({255, 150, 0, 255}) });
	this->positionManager->add_entity_component({ newEntity, position });

	return newEntity;
}

void FoodGenerator::new_food_cluster(int32_t n, uint32_t food, std::array<int32_t, 3> position) {
	int32_t x{ position.at(0) };
	int32_t y{ position.at(1) };
	int32_t m{ position.at(2) };

	for (int32_t i{}; i < n; i++) {
		for (int32_t j{}; j < n; j++) {
			this->new_food(food, { x + i, y + j, m });
		}
	}
}

void FoodGenerator::destroy_food(Entity e)
{
	this->entityManager->destroy_entity(e);
	this->positionManager->remove_entity_component(e);
	this->colorManager->remove_entity_component(e);
	this->foodManager->remove_entity_component(e);
}
