#pragma once
#include "ComponentManager.h"
#include <vector>
#include <array>

struct Position :
    public Component < std::array<int, 2> > 
{
};

bool operator<(const Position& lhs, const Position& rhs);

class PositionManager :
    public ComponentManager <Position, std::vector>
{
};

