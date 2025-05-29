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
        auto& enemies = entityManager->getEntitiesInGroup("enemy");
        auto& bullets = entityManager->getEntitiesInGroup("bullet");
        auto& player = entityManager->getEntityFromTag("player");

        for (auto& enemy: enemies) {
            auto& enemyTransform = enemy.getComponent<TransformComponent>();
            auto& enemyCollision = enemy.getComponent<CollisionSphereComponent>();

            for (auto& bullet: bullets) {
                auto& bulletTransform = bullet.getComponent<TransformComponent>();
                auto& bulletCollision = bullet.getComponent<CollisionSphereComponent>();

                if (CheckCollisionSpheres(
                    enemyTransform.position,
                    enemyCollision.radius,
                    bulletTransform.position,
                    bulletCollision.radius
                )) {
                    eventBus->emitEvent<DamageEvent>(enemy, 30);
                    eventBus->emitEvent<DamageEvent>(bullet, 100);
                }
            }
        }
        // auto& player = entityManager->getEntityFromTag("player");
        // const auto& playerTransform = player.getComponent<TransformComponent>();
        // const auto& playerCollisionSphere = player.getComponent<CollisionSphereComponent>();
        //
        // for (auto& entity : getSystemEntities()) {
        //     if (entity == player) { continue; }
        //     const auto& entityTransform = entity.getComponent<TransformComponent>();
        //     auto& entityCollisionSphere = entity.getComponent<CollisionSphereComponent>();
        //
        //     if (CheckCollisionSpheres(playerTransform.position, playerCollisionSphere.radius,
        //        entityTransform.position, entityCollisionSphere.radius)) {
        //        eventBus->emitEvent<DamageEvent>(player, 10);
        //     }
        //     if (entityTransform.position.z >= 8) {
        //         entity.kill();
        //     }
        // }
    }
};

#endif //COLLISIONSYSTEM_H
