#pragma once
#include <cstdint>

struct ScreenOffset {
	int xOffset, yOffset;
};

struct AICodes {
	static const uint32_t Stationary{ 0b00000001 };
	static const uint32_t Home{ 0b00000010 };
	static const uint32_t Seeking{ 0b00000100 };
};

struct TrailIncr {
	static const uint32_t Max = 10000;
	static const uint32_t Increase = 2000;
	static const uint32_t Decay = 50;
};

struct AntVals {
	static const uint32_t Max = 5;
	static const uint32_t Thresh = 10;
};