#include "ManagerMacros.h"

const int32_t CHAR_MASK = (1 << 8) - 1;

std::array<uint8_t, 4> int_to_color(int32_t iColor) {
	std::array<uint8_t, 4> aColor{};
	for (size_t i{}; i < 3; i++) {
		aColor.at(i) = iColor >> i * 8 & CHAR_MASK;
	}

	uint8_t a = iColor >> 24 & (CHAR_MASK / 2);
	aColor.at(3) = (uint8_t)(255 * (double)a / 127);
	return aColor;
}

int32_t color_to_int(std::array<uint8_t, 4> aColor)
{
	int32_t iColor{ 1 << 31 };
	for (size_t i{}; i < 3; i++) {
		int32_t temp = aColor.at(i);
		iColor += temp << 8 * i;
	}
	int32_t a = (int32_t)(127 * (double)(aColor.at(3)) / 255);
	iColor += a << 24;

	return iColor;
}

Entity new_trail(NewTrail& newTrail, EntityManager& entityManager, TRAIL_MANAGER& trails, COLOR_MANAGER& colors, POSITION_MANAGER& positions)
{
    Entity newEntity = entityManager.create_entity();
	trails.add_entity_component({ newEntity, newTrail.trail });
	positions.add_entity_component({ newEntity, newTrail.position });
	colors.add_entity_component({ newEntity, newTrail.color });
    return newEntity;
}

Entity new_ant(NewAnt& newAnt, EntityManager& entityManager, POSITION_MANAGER& positions, COLOR_MANAGER& colors, VELOCITY_MANAGER& velocities)
{
	Entity newEntity = entityManager.create_entity();
	positions.add_entity_component({ newEntity, newAnt.position });
	colors.add_entity_component({ newEntity, newAnt.color });
	velocities.add_entity_component({ newEntity, newAnt.velocity });
	return newEntity;
}
