#include "collision_system.h"

void CollisionSystem::step(unsigned collisionRange) 
{
    double collisionRange2 = std::pow(collisionRange, 2);
    for (auto cit1 = collisionManager->begin(); cit1 != collisionManager->end(); cit1++) {
        auto vit1 = velocityManager->citer_at(cit1->entity);
        auto pit1 = positionManager->citer_at(vit1->entity);
        cit1->foodCollisions.clear();
        cit1->trailCollisions.clear();
        for (int bx{ -1 }; bx < 2; bx++) for (int by{ -1 }; by < 2; by++) {
            int32_t x = pit1->data.at(0) + (positionManager->bucketWidth * bx);
            int32_t y = pit1->data.at(1) + (positionManager->bucketWidth * by);
            if (!positionManager->has_bucket(x, y))
                continue;
            auto bucket = positionManager->clist_at(x, y);
            for (auto e : bucket) {
                auto pit2 = positionManager->citer_at(e);
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
                                    atan2(pit1->data[1] - pit2->data[1], pit1->data[0] - pit2->data[0])
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
                                        atan2(pit1->data[1] - pit2->data[1], pit1->data[0] - pit2->data[0]),
                                        static_cast<double>(fit->kind)
                                    }
                                }
                            );
                        }
                    }
                }
            }
        }
    }
}
