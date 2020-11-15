#include "input_system.h"

void InputSystem::step(const float fElapsedTime) {
	if (engine->GetKey(olc::Key::W).bHeld) {
		offset->yOffset += static_cast<int>(100*fElapsedTime);
	}
	if (engine->GetKey(olc::Key::S).bHeld) {
		offset->yOffset -= static_cast<int>(100 * fElapsedTime);
	}
	if (engine->GetKey(olc::Key::A).bHeld) {
		offset->xOffset += static_cast<int>(100 * fElapsedTime);
	}
	if (engine->GetKey(olc::Key::D).bHeld) {
		offset->xOffset -= static_cast<int>(100 * fElapsedTime);
	}
}