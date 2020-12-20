#include "collision_system.h"

void CollisionSystem::step(unsigned collisionRange) 
{
    double collisionRange2 = std::pow(collisionRange, 2);
    for (auto cit1 = collisionManager->begin(); cit1 != collisionManager->end(); cit1++) {
        auto vit1 = velocityManager->citer_at(cit1->entity);
        auto pit1 = positionManager->citer_at(vit1->entity);
        cit1->data.clear();
        for (auto pit2 = positionManager->cbegin(); pit2 != positionManager->cend(); pit2++) {
            if (pit1->entity != pit2->entity) {
                double distance = std::pow(pit1->data[0] - pit2->data[0], 2) + 
                                  std::pow(pit1->data[1] - pit2->data[1], 2);
                if (distance <= collisionRange2) {
                    cit1->data.push_back({*pit2, std::sqrt(distance)});
                }
            }
        }
        //std::sort(collisionVector.begin(), collisionVector.end(),
          //  [](Collision& lhs, Collision& rhs) {
            //    return lhs.second < rhs.second;
            //});
    }
}
