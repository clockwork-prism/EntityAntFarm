#include "PositionManager.h"

bool operator<(const Position& lhs, const Position& rhs) {
    return lhs.entity < rhs.entity;
}
