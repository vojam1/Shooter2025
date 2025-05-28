//
// Created by sputnik on 5/26/25.
//

#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../Components/CollisionSphereComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/DamageEvent.h"
#include "../Util/Debug.h"

class CollisionSystem : public System {
public:
    CollisionSystem() {
        requireComponent<CollisionSphereComponent>();
        requireComponent<TransformComponent>();
    }

    void update(UniqueRef<EntityManager>& entityManager, UniqueRef<EventBus>& eventBus) {
        auto& entities = getSystemEntities();

        auto& player = entityManager->getEntityFromTag("player");
        const auto& playerTransform = player.getComponent<TransformComponent>();
        const auto& playerCollisionSphere = player.getComponent<CollisionSphereComponent>();

        auto& enemies = entityManager->getEntitiesInGroup("enemy");
        auto& bullets = entityManager->getEntitiesInGroup("bullet");

        for (auto& entity : enemies) {
            const auto& entityTransform = entity.getComponent<TransformComponent>();
            auto& entityCollisionSphere = entity.getComponent<CollisionSphereComponent>();

            for (auto& bullet: bullets) {
                const auto& bulletTransform = bullet.getComponent<TransformComponent>();
                auto& bulletCollisionSphere = bullet.getComponent<CollisionSphereComponent>();


                if (CheckCollisionSpheres(bulletTransform.position, bulletCollisionSphere.radius,
                    entityTransform.position, entityCollisionSphere.radius)) {
                    //eventBus->emitEvent<DamageEvent>(entity, 20);
                }
            }
        }
    }
};

#endif //COLLISIONSYSTEM_H
