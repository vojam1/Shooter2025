//
// Created by sputnik on 5/26/25.
//

#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../Components/CollisionSphereComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"
#include "../Events/DamageEvent.h"
#include "../Events/MysteryBoxEvent.h"

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
        auto& boxes = entityManager->getEntitiesInGroup("box");
        auto& barriers = entityManager->getEntitiesInGroup("barrier");

        for (auto& bullet: bullets) {
            auto& bulletTransform = bullet.getComponent<TransformComponent>();
            auto& bulletCollision = bullet.getComponent<CollisionSphereComponent>();

            for (auto& enemy: enemies) {
                auto& enemyTransform = enemy.getComponent<TransformComponent>();
                auto& enemyCollision = enemy.getComponent<CollisionSphereComponent>();

                if (CheckCollisionSpheres(
                        enemyTransform.position,
                        enemyCollision.radius,
                        bulletTransform.position,
                        bulletCollision.radius
                )) {
                    eventBus->emitEvent<CollisionEvent>(enemy, bullet);
                }
            }

            for (auto& box: boxes) {
                auto& boxTransform = box.getComponent<TransformComponent>();
                auto& boxCollision = box.getComponent<CollisionSphereComponent>();

                if (CheckCollisionSpheres(
                    boxTransform.position,
                    boxCollision.radius,
                    bulletTransform.position,
                    bulletCollision.radius)) {
                    eventBus->emitEvent<MysteryBoxEvent>(box);
                }
            }
        }
        for (auto& enemy: enemies) {
            const auto& enemyTransform = enemy.getComponent<TransformComponent>();
            auto& enemyCollision = enemy.getComponent<CollisionSphereComponent>();

            if (enemyTransform.position.z >= 5) {
                eventBus->emitEvent<DamageEvent>(player, 10);
                eventBus->emitEvent<DamageEvent>(enemy, 100);
            }
            if (enemyTransform.position.z <= -40) {
                eventBus->emitEvent<DamageEvent>(enemy, 100);
            }
            for (auto& barrier: barriers) {
                auto& barrierTransform = barrier.getComponent<TransformComponent>();
                auto& barrierCollision = barrier.getComponent<CollisionSphereComponent>();

                if (CheckCollisionSpheres(
                    barrierTransform.position,
                    barrierCollision.radius,
                    enemyTransform.position,
                    barrierCollision.radius)) {
                    eventBus->emitEvent<DamageEvent>(enemy, 100);
                    eventBus->emitEvent<DamageEvent>(barrier, 20);
                }
            }
        }
    }
};

#endif //COLLISIONSYSTEM_H
