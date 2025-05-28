//
// Created by sputnik on 5/26/25.
//

#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "../Components/HealthComponent.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/DamageEvent.h"

class DamageSystem : public System {
public:
    DamageSystem() {
        requireComponent<HealthComponent>();
    }

    void subscribeToEvents(UniqueRef<EventBus>& eventBus) {
        eventBus->subscribeToEvent<DamageEvent>(this, &DamageSystem::onDamage);
    }

    void onDamage(DamageEvent& event) {
        const auto& entity = event.entity;
        auto& healthComp = entity.getComponent<HealthComponent>();
        healthComp.health -= event.damage;
        if (healthComp.health <= 0) {
            entity.kill();
        }
    }
};

#endif //DAMAGESYSTEM_H
