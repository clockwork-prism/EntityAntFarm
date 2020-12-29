#include "render_system.h"

void RenderSystem::step(size_t nAnts)
{
	engine->Clear(olc::BLACK);
	std::fill(depthBuffer.begin(), depthBuffer.end(), -1);
	for (auto it{ positionManager->cbegin() }; it != positionManager->cend(); it++) {
		if (entityManager->is_alive(it->entity)) {
			try {
				_render_color(it);
			}
			catch (std::out_of_range& ex) {
			}
		}
	}

	std::stringstream ss{};
	ss << "Ants: " << nAnts << "\n";
	ss << "Entities: " << positionManager->size();
	engine->DrawString(5, 5, ss.str());
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
	int x = it->data[0] + offset->xOffset;
	int y = it->data[1] + offset->yOffset;
	int z = it->data[2];
	_draw_pixel(x, y, z, icolor);
}

void RenderSystem::_draw_pixel(int x, int y, int z, const int32_t& icolor)
{
	if (x >= 0 && x < engine->ScreenWidth() && y >= 0 && y < engine->ScreenHeight()) {
		size_t idx = static_cast<size_t>(y * engine->ScreenWidth() + x);
		if (depthBuffer.at(idx) <= z) {
			std::array<uint8_t, 4> col = int_to_color(icolor);
			engine->Draw(x, y, { col[0], col[1], col[2], col[3] });
			depthBuffer.at(idx) = z;
		}
	}
}

void RenderSystem::_render_pixel_array(std::vector<Position>::const_iterator& it)
{
	const Array2D<int32_t> colorArray = colorManager->car_at(it->entity);
	for (size_t r{}; r < colorArray.shape()[0]; r++) {
		for (size_t c{}; c < colorArray.shape()[1]; c++) {
			int x = it->data[0] + (int)r + offset->xOffset;
			int y = it->data[1] + (int)c + offset->yOffset;
			int z = it->data[2];
			_draw_pixel(x, y, z, colorArray.cat(r, c));
		}
	}
}

