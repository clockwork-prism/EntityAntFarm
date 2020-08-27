#include "collision_system.h"

std::vector<std::vector<COLLISION>> collision_system(const EntityManager& entityManager, const POSITION_MANAGER& position, const VELOCITY_MANAGER & velocity, unsigned collisionRange)
{
    std::vector<std::vector<std::pair<POSITION, double>>> collisionMap{};

    double collisionRange2 = std::pow(collisionRange, 2);

    for (auto vit1 = velocity.cbegin(); vit1 != velocity.cend(); vit1++) {
        auto pit1 = position.citer_at(vit1->entity);
        std::vector<COLLISION> collisionVector{ {*pit1, 0} };
        for (auto pit2 = position.cbegin(); pit2 != position.cend(); pit2++) {
            if (pit1->entity != pit2->entity) {
                double distance = std::pow(pit1->data[0] - pit2->data[0], 2) + std::pow(pit1->data[1] - pit2->data[1], 2);
                if (distance <= collisionRange2) collisionVector.push_back({ *pit2, std::sqrt(distance) });
            }
        }
        std::sort(collisionVector.begin(), collisionVector.end(),
            [](COLLISION& lhs, COLLISION& rhs) {
                return lhs.second < rhs.second;
            });
        collisionMap.push_back(collisionVector);
    }

    return collisionMap;
}
