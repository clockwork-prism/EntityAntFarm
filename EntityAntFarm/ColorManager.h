#pragma once

#include "ComponentManager.h"
#include "ArrayComponentManager.h"
#include "Array2D.h"
#include <cstdint>

typedef Component<int32_t> Color;

typedef ArrayComponentManager<Color, int32_t, std::vector> ColorManager;

std::array<uint8_t, 4> int_to_color(int32_t iColor);

int32_t color_to_int(std::array<uint8_t, 4> aColor);