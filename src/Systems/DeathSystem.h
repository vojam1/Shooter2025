//
// Created by sputnik on 5/23/25.
//

#ifndef DEATHSYSTEM_H
#define DEATHSYSTEM_H

#include "../Components/HealthComponent.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/DeathEvent.h"

class DeathSystem: public System {
public:
    DeathSystem() {
        requireComponent<HealthComponent>();
    }

    void subscribeToEvents(UniqueRef<EventBus>& eventBus) {
        eventBus->subscribeToEvent<DeathEvent>(this, &DeathSystem::killEntity);
    }

    void killEntity(DeathEvent& event) {
        event.entityToKill.kill();
    }
};

#endif //DEATHSYSTEM_H
