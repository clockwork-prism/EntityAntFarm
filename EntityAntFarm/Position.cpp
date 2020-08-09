#include "Position.h"

bool operator<(const PositionComponent& lhs, const PositionComponent& rhs) {
    if (lhs.data[0] < rhs.data[0]) return true;
    if (lhs.data[1] < rhs.data[1]) return true;
    return false;
}

bool operator==(const PositionComponent& lhs, const PositionComponent& rhs)
{
    if (lhs.data[0] == rhs.data[0] && lhs.data[1] == rhs.data[1]) return true;
    return false;
}

bool position_compare(const PositionComponent& lhs, const PositionComponent& rhs, unsigned blockSize)
{
    if (lhs.data[0] / blockSize < rhs.data[0] / blockSize) return true;
    if (lhs.data[1] / blockSize < rhs.data[1] / blockSize) return true;
    if (lhs.data[0] < rhs.data[0]) return true;
    if (lhs.data[1] < rhs.data[1]) return true;
    return false;
}
