//
// Created by sputnik on 5/26/25.
//

#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "../Components/HealthComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

class DamageSystem : public System {
public:
    DamageSystem() {
        requireComponent<HealthComponent>();
    }

    void subscribeToEvents(UniqueRef<EventBus>& eventBus) {
        eventBus->subscribeToEvent<CollisionEvent>(this, &DamageSystem::onCollision);
        eventBus->subscribeToEvent<DamageEvent>(this, &DamageSystem::onDamage);
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

    void onDamage(DamageEvent& event) {
        const auto& entity = event.entity;
        auto& entityHealth = entity.getComponent<HealthComponent>();

        entityHealth.health -= event.damage;

        if (entityHealth.health <= 0) {
            entity.kill();
        }
    }
};

#endif //DAMAGESYSTEM_H
