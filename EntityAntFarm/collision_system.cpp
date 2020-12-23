#include "collision_system.h"

void CollisionSystem::step(unsigned collisionRange) 
{
    double collisionRange2 = std::pow(collisionRange, 2);
    for (auto cit1 = collisionManager->begin(); cit1 != collisionManager->end(); cit1++) {
        auto vit1 = velocityManager->citer_at(cit1->entity);
        auto pit1 = positionManager->citer_at(vit1->entity);
        cit1->foodCollisions.clear();
        cit1->trailCollisions.clear();
        for (auto pit2 = positionManager->cbegin(); pit2 != positionManager->cend(); pit2++) {
            if (pit1->entity != pit2->entity) {
                double distance = std::pow(pit1->data[0] - pit2->data[0], 2) + 
                                  std::pow(pit1->data[1] - pit2->data[1], 2);
                if (distance <= collisionRange2) {
                    auto tit = trailManager->cfind(pit2->entity);
                    if (tit != trailManager->cend()) cit1->trailCollisions.push_back(
                        {
                            tit->entity,
                            {
                                sqrt(distance),
                                atan2(pit1->data[0] - pit2->data[0], pit1->data[1] - pit2->data[1])
                            }
                        }
                    );
                    else {
                        auto fit = foodManager->cfind(pit2->entity);
                        if (fit != foodManager->cend()) cit1->foodCollisions.push_back(
                            {
                                fit->entity,
                                {
                                    sqrt(distance),
                                    atan2(pit1->data[0] - pit2->data[0], pit1->data[1] - pit2->data[1])
                                }
                            }
                        );
                    }
                }
            }
        }
        //std::sort(collisionVector.begin(), collisionVector.end(),
          //  [](Collision& lhs, Collision& rhs) {
            //    return lhs.second < rhs.second;
            //});
    }
}
