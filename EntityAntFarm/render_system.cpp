#include "render_system.h"

void render_system(const EntityManager& entityManager, const POSITION_MANAGER& position, olc::PixelGameEngine* engine)
{
	engine->Clear(olc::BLACK);
	for (auto it{ position.cbegin() }; it != position.cend(); it++) {
		if (entityManager.is_alive(it->entity))
			engine->Draw(it->data[0], it->data[1]);
	}
}
