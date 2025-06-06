//
// Created by sputnik on 6/6/25.
//

#ifndef MYSTERYBOXSYSTEM_H
#define MYSTERYBOXSYSTEM_H

#include "ProjectileSystem.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/MysteryBoxEvent.h"

class MysteryBoxSystem : public System {
public:
    MysteryBoxSystem() = default;

    void subscribeToEvents(UniqueRef<EventBus>& eventBus) {
        eventBus->subscribeToEvent<MysteryBoxEvent>(this, &MysteryBoxSystem::onDestroy);
    }

    void onDestroy(MysteryBoxEvent& e) {
        Entity& box = e.box;
        box.entityManager->getSystem<ProjectileSystem>().addCharge("missile", 3);
        box.entityManager->getSystem<ProjectileSystem>().arrowSelfDamage -= 5;
        box.kill();
    }
};

#endif //MYSTERYBOXSYSTEM_H
