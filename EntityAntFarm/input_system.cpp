#include "input_system.h"

void InputSystem::step(const float fElapsedTime) {
	int step = static_cast<int>(100 * fElapsedTime) + 1;
	if (engine->GetKey(olc::Key::W).bHeld) {
		offset->yOffset += step;
	}
	if (engine->GetKey(olc::Key::S).bHeld) {
		offset->yOffset -= step;
	}
	if (engine->GetKey(olc::Key::A).bHeld) {
		offset->xOffset += step;
	}
	if (engine->GetKey(olc::Key::D).bHeld) {
		offset->xOffset -= step;
	}
}