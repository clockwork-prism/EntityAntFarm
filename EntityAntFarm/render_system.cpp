#include "render_system.h"

void render_system(const EntityManager& entityManager, const POSITION_MANAGER& position, const COLOR_MANAGER& color, olc::PixelGameEngine* engine)
{
	engine->Clear(olc::BLACK);
	for (auto it{ position.cbegin() }; it != position.cend(); it++) {
		if (entityManager.is_alive(it->entity)) {
			std::array<uint8_t, 4> col{};
			try {
				auto cit = color.citer_at(it->entity);
				col = int_to_color(cit->data);
			}
			catch (std::out_of_range& ex) {
				col = { 255, 255, 255, 255 };
			}
			engine->Draw(it->data[0], it->data[1], { col[0], col[1], col[2], col[3] });
		}
	}
}


