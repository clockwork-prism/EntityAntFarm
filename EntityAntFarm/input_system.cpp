#include "input_system.h"

void input_system(olc::PixelGameEngine* engine, ScreenOffset& offset, const float fElapsedTime) {
	if (engine->GetKey(olc::Key::W).bHeld) {
		offset.yOffset += 100*fElapsedTime;
	}
	if (engine->GetKey(olc::Key::S).bHeld) {
		offset.yOffset -= 100 * fElapsedTime;
	}
	if (engine->GetKey(olc::Key::A).bHeld) {
		offset.xOffset += 100 * fElapsedTime;
	}
	if (engine->GetKey(olc::Key::D).bHeld) {
		offset.xOffset -= 100 * fElapsedTime;
	}
}