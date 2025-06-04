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

            if (enemyTransform.position.z >= 5 || enemyTransform.position.z <= -40) {
                eventBus->emitEvent<DamageEvent>(player, 10);
                eventBus->emitEvent<DamageEvent>(enemy, 100);
            }

            for (auto& bullet: bullets) {
                auto& bulletTransform = bullet.getComponent<TransformComponent>();
                auto& bulletCollision = bullet.getComponent<CollisionSphereComponent>();

                if (CheckCollisionSpheres(
                    enemyTransform.position,
                    enemyCollision.radius,
                    bulletTransform.position,
                    bulletCollision.radius
                )) {
                    eventBus->emitEvent<CollisionEvent>(enemy, bullet);
                }
            }
        }
    }
};

#endif //COLLISIONSYSTEM_H
