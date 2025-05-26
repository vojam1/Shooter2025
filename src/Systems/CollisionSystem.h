//
// Created by sputnik on 5/26/25.
//

#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../Components/CollisionSphereComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"

class CollisionSystem : public System {
public:
    CollisionSystem() {
        requireComponent<CollisionSphereComponent>();
        requireComponent<TransformComponent>();
    }

    void update() {
        for (auto& entity: getSystemEntities()) {
        }
    }
};

#endif //COLLISIONSYSTEM_H
