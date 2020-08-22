#pragma once
#include "ComponentManager.h"
#include <vector>
#include <array>
#include <cstdint>

#ifndef POSITION
#define POSITION Component<std::array<int, 2>>
#endif // !POSITION


#ifndef POSITION_MANAGER
#define POSITION_MANAGER ComponentManager<Component<std::array<int, 2>>, std::vector>
#endif // !POSITION_MANAGER

#ifndef VELOCITY
#define VELOCITY Component<std::array<int, 4>>
#endif // !VELOCITY

#ifndef VELOCITY_MANAGER
#define VELOCITY_MANAGER ComponentManager<Component<std::array<int, 4>>, std::vector>
#endif // !VELOCITY_MANAGER

#ifndef COLOR
#define COLOR Component<int32_t>
#endif // !COLOR

#ifndef COLOR_MANAGER
#define COLOR_MANAGER ComponentManager<COLOR, std::vector>
#endif // !COLOR_MANAGER


