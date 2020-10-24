#include "collision_system.h"

std::vector<std::vector<Collision>> collision_system(
    const EntityManager& entityManager, const PositionManager& position, 
    const VelocityManager & velocity, unsigned collisionRange
) 
{
    std::vector<std::vector<std::pair<Position, double>>> collisionMap(
        velocity.size(), std::vector<Collision>(100, { {{0}, {0,0,0}}, 0. })
    );

    double collisionRange2 = std::pow(collisionRange, 2);
    size_t i{};
    for (auto vit1 = velocity.cbegin(); vit1 != velocity.cend(); vit1++) {
        auto pit1 = position.citer_at(vit1->entity);
        std::vector<Collision> collisionVector{ {*pit1, 0} };
        collisionVector.reserve(100);
        for (auto pit2 = position.cbegin(); pit2 != position.cend(); pit2++) {
            if (pit1->entity != pit2->entity) {
                double distance = std::pow(pit1->data[0] - pit2->data[0], 2) + 
                                  std::pow(pit1->data[1] - pit2->data[1], 2);
                if (distance <= collisionRange2) {
                    collisionVector.push_back({*pit2, std::sqrt(distance)});
                }
            }
        }
        //std::sort(collisionVector.begin(), collisionVector.end(),
          //  [](Collision& lhs, Collision& rhs) {
            //    return lhs.second < rhs.second;
            //});
        collisionMap.at(i) = (collisionVector);
        i++;
    }

    return collisionMap;
}
