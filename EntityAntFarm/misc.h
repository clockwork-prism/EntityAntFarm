#pragma once
#include <cstdint>

struct ScreenOffset {
	int xOffset, yOffset;
};

struct AICodes {
	static const uint32_t Stationary{ 1 };
	static const uint32_t Home{ 2 };
	static const uint32_t Seeking{ 4 };
	static const uint32_t Retracing{ 8 };
	static const uint32_t MoreFood{ 16 };
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