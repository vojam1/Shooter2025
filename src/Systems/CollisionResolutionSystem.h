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

        entityHealth.health -= projectile.getComponent<ProjectileComponent>().damage;
        projectileHealth.health -= projectile.getComponent<ProjectileComponent>().selfDamage;


        if (entityHealth.health <= 0) {
            entity.kill();
        }

        if (projectileHealth.health <= 0) {
            projectile.kill();
        }
    }
};

#endif //COLLISIONRESOLUTIONSYSTEM_H
