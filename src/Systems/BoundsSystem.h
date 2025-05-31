//
// Created by sputnik on 5/29/25.
//

#ifndef BOUNDSSYSTEM_H
#define BOUNDSSYSTEM_H

#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/DamageEvent.h"

class BoundsSystem : public System {
public:
    BoundsSystem() {
        requireComponent<TransformComponent>();
        requireComponent<RigidbodyComponent>();
    }

    void update(UniqueRef<EntityManager>& entityManager, UniqueRef<EventBus>& eventBus) {
        for (auto& entity : getSystemEntities()) {
            auto& entityTransform = entity.getComponent<TransformComponent>();

            if (entityTransform.position.z >= 10 || entityTransform.position.z <= -40) {
                if (entityManager->hasGroup(entity, "enemy")) {
                    auto& player = entityManager->getEntityFromTag("player");
                    eventBus->emitEvent<DamageEvent>(player, 10);
                }
                eventBus->emitEvent<DamageEvent>(entity, 100);
            }
        }
    }
};

#endif //BOUNDSSYSTEM_H
