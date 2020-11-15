#include "render_system.h"

void RenderSystem::step()
{
	engine->Clear(olc::BLACK);
	for (auto it{ positionManager->cbegin() }; it != positionManager->cend(); it++) {
		if (entityManager->is_alive(it->entity)) {
			try {
				_render_color(it);
			}
			catch (std::out_of_range& ex) {
			}
		}
	}
}

void RenderSystem::_render_color(std::vector<Position>::const_iterator& it)
{
	auto cit = colorManager->citer_at(it->entity);
	if (cit->data < 0) {
		_render_pixel(cit->data, it);
	}
	else {
		_render_pixel_array(it);
	}
}

void RenderSystem::_render_pixel(const int32_t& icolor, std::vector<Position>::const_iterator& it)
{
	std::array<uint8_t, 4> col = int_to_color(icolor);
	engine->Draw(it->data[0] + offset->xOffset, it->data[1] + offset->yOffset, { col[0], col[1], col[2], col[3] });
}

void RenderSystem::_render_pixel_array(std::vector<Position>::const_iterator& it)
{
	const Array2D<int32_t> colorArray = colorManager->car_at(it->entity);
	for (size_t r{}; r < colorArray.shape()[0]; r++) {
		for (size_t c{}; c < colorArray.shape()[1]; c++) {
			std::array<uint8_t, 4> col = int_to_color(colorArray.cat(r, c));
			engine->Draw(it->data[0] + (int)r + offset->xOffset, it->data[1] + (int)c + offset->yOffset, { col[0], col[1], col[2], col[3] });
		}
	}
}

