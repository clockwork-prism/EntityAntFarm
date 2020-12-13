#pragma once
#include <cstdint>

struct ScreenOffset {
	int xOffset, yOffset;
};

struct AICodes {
	static const uint32_t Stationary{ 1 };
	static const uint32_t Home{ 2 };
};