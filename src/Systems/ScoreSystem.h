//
// Created by sputnik on 6/2/25.
//

#ifndef SCORESYSTEM_H
#define SCORESYSTEM_H

#include "../Components/HealthComponent.h"
#include "../Components/ScoreTrackerComponent.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

class ScoreSystem : public System {
public:
    ScoreSystem() {
        requireComponent<ScoreTrackerComponent>();
    }

    void subscribeToEvents(UniqueRef<EventBus>& eventBus) {
        eventBus->subscribeToEvent<CollisionEvent>(this, &ScoreSystem::onCollision);
    }

    void onCollision(CollisionEvent& event) {
        for (auto& entity: getSystemEntities()) {
            if (event.a.getComponent<HealthComponent>().health <= 0) {
                //entity.getComponent<ScoreTrackerComponent>().score += 100;
            }
        }
    }
};

#endif //SCORESYSTEM_H
