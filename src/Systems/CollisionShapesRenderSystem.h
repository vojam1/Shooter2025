//
// Created by sputnik on 5/26/25.
//

#ifndef COLLISIONSHAPESRENDERSYSTEM_H
#define COLLISIONSHAPESRENDERSYSTEM_H

#include "../Components/CollisionSphereComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"

class CollisionShapesRenderSystem: public System {
public:
    CollisionShapesRenderSystem() {
        requireComponent<TransformComponent>();
        requireComponent<CollisionSphereComponent>();
    }

    void update() {
        for (auto& entity: getSystemEntities()) {
            const auto& transform = entity.getComponent<TransformComponent>();
            const auto& sphere = entity.getComponent<CollisionSphereComponent>();

            DrawSphereWires(transform.position, sphere.radius, sphere.rings, sphere.slices, sphere.color);
        }
    }
};

#endif //COLLISIONSHAPESRENDERSYSTEM_H
