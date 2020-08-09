#pragma once
#include "ComponentManager.h"
#include <vector>
#include <array>

struct PositionComponent :
    public Component < std::array<int, 2> > 
{
};

bool operator<(const PositionComponent& lhs, const PositionComponent& rhs);
bool operator==(const PositionComponent& lhs, const PositionComponent& rhs);

bool position_compare(const PositionComponent& lhs, const PositionComponent& rhs, unsigned blockSize);

class PositionManager :
    public ComponentManager <PositionComponent, std::vector>
{
};

