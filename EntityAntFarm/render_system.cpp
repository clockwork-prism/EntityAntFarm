#include "render_system.h"

void render_system(const EntityManager& entityManager, const POSITION_MANAGER& position, const ColorManager& color, olc::PixelGameEngine* engine)
{
	engine->Clear(olc::BLACK);
	for (auto it{ position.cbegin() }; it != position.cend(); it++) {
		if (entityManager.is_alive(it->entity)) {
			try {
				_render_color(color, it, engine);
			}
			catch (std::out_of_range& ex) {
			}
		}
	}
}

void _render_color(
	const ColorManager& color, 
	std::vector<Component<std::array<int32_t, 3Ui64>>>::const_iterator& it, 
	olc::PixelGameEngine* engine
)
{
	auto cit = color.citer_at(it->entity);
	if (cit->data < 0) {
		_render_pixel(cit->data, engine, it);
	}
	else {
		_render_pixel_array(color, engine, it);
	}
}

void _render_pixel(
	const int32_t& icolor, olc::PixelGameEngine* engine,
	std::vector<Component<std::array<int32_t, 3Ui64>>>::const_iterator& it
)
{
	std::array<uint8_t, 4> col = int_to_color(icolor);
	engine->Draw(it->data[0], it->data[1], { col[0], col[1], col[2], col[3] });
}

void _render_pixel_array(
	const ColorManager& color, olc::PixelGameEngine* engine, 
	std::vector<Component<std::array<int32_t, 3Ui64>>>::const_iterator& it
)
{
	const Array2D<int32_t> colorArray = color.car_at(it->entity);
	for (size_t r{}; r < colorArray.shape()[0]; r++) {
		for (size_t c{}; c < colorArray.shape()[1]; c++) {
			std::array<uint8_t, 4> col = int_to_color(colorArray.cat(r, c));
			engine->Draw(it->data[0] + (int)r, it->data[1] + (int)c, { col[0], col[1], col[2], col[3] });
		}
	}
}

