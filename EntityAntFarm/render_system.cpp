#include "render_system.h"

void render_system(const EntityManager entityManager, const std::vector<PositionComponent>& position, const std::vector<int32_t>& color, olc::PixelGameEngine* engine) {
	engine->Clear(olc::BLACK);
	auto col_it = color.cbegin();
	for (auto pos_it{ position.cbegin() }; pos_it != position.cend(); pos_it++) {
		if (entityManager.is_alive(pos_it->entity)) {
			if (*col_it < 0) {
				std::array<uint8_t, 3> col = convert_color(*col_it);
				engine->Draw(pos_it->data[0], pos_it->data[1], {col[0], col[1], col[2]});
			}
		}
	}
}

std::array<uint8_t, 3> convert_color(int32_t c)
{
	std::array<uint8_t, 3> out{};
	for (size_t i{}; i < 3; i++) {
		out[i] = (c >> (8 * i)) & CHAR_MASK;
	}
	return out;
}
