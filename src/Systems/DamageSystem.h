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
        //eventBus->subscribeToEvent<CollisionEvent>(this, &DamageSystem::onCollision);
        eventBus->subscribeToEvent<DamageEvent>(this, &DamageSystem::onDamage);
    }

    void onDamage(DamageEvent& event) {
        const auto& entity = event.entity;
        auto& entityHealth = entity.getComponent<HealthComponent>();

        entityHealth.health -= event.damage;

        if (entityHealth.health <= 0) {
            if (entity.hasGroup("enemy")) {
                entity.entityManager->getEntityFromTag("player").getComponent<ScoreTrackerComponent>().score += 100;
            }
            entity.kill();
        }
    }
};

#endif //DAMAGESYSTEM_H
