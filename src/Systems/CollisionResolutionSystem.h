//
// Created by sputnik on 6/2/25.
//

#ifndef COLLISIONRESOLUTIONSYSTEM_H
#define COLLISIONRESOLUTIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

#include "../Components/HealthComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/ScoreTrackerComponent.h"

class CollisionResolutionSystem : public System {
public:
    CollisionResolutionSystem() = default;

    void subscribeToEvents(UniqueRef<EventBus>& eventBus) {
        eventBus->subscribeToEvent<CollisionEvent>(this, &CollisionResolutionSystem::onCollision);
    }

    void onCollision(CollisionEvent& event) {
        const auto& entity = event.a;
        auto& entityHealth = entity.getComponent<HealthComponent>();
        const auto& projectile = event.b;
        auto& projectileHealth = projectile.getComponent<HealthComponent>();
        const std::string& tag = projectile.getComponent<ProjectileComponent>().tag;

        if (tag == "missile") {
            auto& projectileTransorm = projectile.getComponent<TransformComponent>();
            auto& projectileCollision = projectile.getComponent<CollisionSphereComponent>();

            projectileCollision.radius = 10.0f;
            for (auto& enemy: entity.entityManager->getEntitiesInGroup("enemy")) {
                auto& enemyTransform = enemy.getComponent<TransformComponent>();
                auto& enemyCollision = enemy.getComponent<CollisionSphereComponent>();
                if (CheckCollisionSpheres(
                enemyTransform.position,
                enemyCollision.radius,
                projectileTransorm.position,
                projectileCollision.radius)) {
                        enemy.getComponent<HealthComponent>().health -= projectile.getComponent<ProjectileComponent>().damage;
                        projectileHealth.health -= projectile.getComponent<ProjectileComponent>().selfDamage;
                    }
            }
        } else {
            entityHealth.health -= projectile.getComponent<ProjectileComponent>().damage;
            projectileHealth.health -= projectile.getComponent<ProjectileComponent>().selfDamage;
        }

        if (entityHealth.health <= 0) {
            entity.entityManager->getEntityFromTag("player").getComponent<ScoreTrackerComponent>().score += 100;
            entity.kill();
        }

        if (projectileHealth.health <= 0) {
            projectile.kill();
        }
    }
};

#endif //COLLISIONRESOLUTIONSYSTEM_H
