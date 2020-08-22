#pragma once
#include "ComponentManager.h"
#include <vector>
#include <array>

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
