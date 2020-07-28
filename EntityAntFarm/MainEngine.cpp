#include "MainEngine.h"

MainEngine::MainEngine() {
	// Name you application
	sAppName = "Example";
}

bool MainEngine::OnUserCreate() {
	// Called once at the start, so create things here
	entityManager = EntityManager();
	_position = PositionManager();
	for (int i{}; i < 20; i++) {
		int x = rand() % ScreenWidth();
		int y = rand() % ScreenHeight();
		Entity e = entityManager.create_entity();
		_position.add_entity_component(e, Position{ e, {x, y} });
	}
	return true;
}

bool MainEngine::OnUserUpdate(float fElapsedTime) {
	// called once per frame, draws random coloured pixels
	_EAF_RenderSystem(_position);
	return true;
}

void MainEngine::_EAF_RenderSystem(const PositionManager& position)
{
	Clear(olc::BLACK);
	for (auto it{ position.cbegin() }; it != position.cend(); it++) {
		if (entityManager.is_alive(it->entity))
			Draw(it->data[0], it->data[1]);
	}
}
