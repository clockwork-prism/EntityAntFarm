#include "PhysicsManager.h"

void PhysicsManager::sort_components(unsigned left, unsigned right)
{
    if (right == 0) right = this->transform.size();
    auto beg = this->transform.begin();
    auto end = this->transform.end();
    std::advance(beg, left);
    std::advance(end, right);
    std::sort(beg, end,
        [this](PositionComponent lhs, PositionComponent rhs) {
            if (lhs.data[0] / this->blockSize < rhs.data[0] / this->blockSize) return true;
            if (lhs.data[1] / this->blockSize < rhs.data[1] / this->blockSize) return true;
            if (lhs.data[0] < rhs.data[0]) return true;
            if (lhs.data[1] < rhs.data[1]) return true;
            return false;
        }
    );
    for (unsigned i{ left }; i < right; i++) {
        auto mit = this->_map.find(this->transform.at(i).entity);
        unsigned j = mit->second;
        if (j != i) {
            std::swap(this->velocity.at(i), this->velocity.at(j));
            mit->second = i;
        }
    }
}

unsigned PhysicsManager::add_transform(PositionComponent newPosition)
{
    if (this->transform.size() == 0) {
        this->transform.push_back(newPosition);
        this->velocity.push_back({ 0, 0, 0, 0 });
        this->color.push_back(0);
        this->_map[newPosition.entity] = 0;
        return 0;
    }
    auto mit = this->_map.find(newPosition.entity);
    if (mit != this->_map.end()) {
        this->transform.at(mit->second) = newPosition;
        return mit->second;
    }
    auto it = std::lower_bound(this->transform.begin(), this->transform.end(), newPosition);
    unsigned newIdx = it - this->transform.begin();
    this->transform.insert(it, newPosition);

    this->velocity.insert(this->velocity.begin() + newIdx, { 0,0,0,0 });
    this->color.insert(this->color.begin() + newIdx, 0);

    for (auto& m: this->_map) {
        if (m.second >= newIdx) m.second++;
    }

    this->_map[newPosition.entity] = newIdx;
    return newIdx;
}


void PhysicsManager::garbage_collect()
{
    while (true) {
        auto it = this->transform.end();
        it--;
        if (it->data[0] == INT_MAX) {
            this->transform.pop_back();
            this->velocity.pop_back();
        }
        else {
            break;
        }
    }
}

PositionComponent &PhysicsManager::transform_at(Entity e)
{
    unsigned idx = this->_map.at(e);
    return this->transform.at(idx);
}

PositionComponent &PhysicsManager::transform_at(unsigned idx)
{
    return this->transform.at(idx);
}

std::array<unsigned, 4> &PhysicsManager::velocity_at(Entity e)
{
    unsigned idx = this->_map.at(e);
    return this->velocity.at(idx);
}

std::array<unsigned, 4> &PhysicsManager::velocity_at(unsigned idx)
{
    return this->velocity.at(idx);
}

int32_t& PhysicsManager::color_at(Entity e)
{
    unsigned idx = this->_map.at(e);
    return this->color_at(idx);
}

int32_t& PhysicsManager::color_at(unsigned idx)
{
    return this->color.at(idx);
}
