//
// Created by sputnik on 6/6/25.
//

#ifndef MYSTERYBOXSYSTEM_H
#define MYSTERYBOXSYSTEM_H

#include "ProjectileSystem.h"
#include "UIRenderSystem.h"
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
        if (box.hasGroup("present")) {
            int32_t randomNum = GetRandomValue(1,3);
            switch (randomNum) {
                case 1:
                    box.entityManager->getEntityFromTag("player").getComponent<HealthComponent>().health += 10;
                    box.entityManager->getSystem<UIRenderSystem>().render("+10 HP", box.getComponent<TransformComponent>().position);
                    break;
                case 2:
                    box.entityManager->getSystem<CollisionResolutionSystem>().activateDoubleScore();
                    box.entityManager->getSystem<UIRenderSystem>().render("DOUBLE SCORE", box.getComponent<TransformComponent>().position);
                    break;
                case 3:
                    box.entityManager->getSystem<ProjectileSystem>().activateInstaKill();
                    box.entityManager->getSystem<UIRenderSystem>().isInstaKill = true;
                    box.entityManager->getSystem<UIRenderSystem>().instaKillTimer = GetTime();
                    box.entityManager->getSystem<UIRenderSystem>().render("INSTA KILL", box.getComponent<TransformComponent>().position);
                    break;
                default:
                    break;
            }
        } else {
            auto& projectileSystem = box.entityManager->getSystem<ProjectileSystem>();
            int32_t randomNum = GetRandomValue(1,5);
            switch (randomNum) {
                case 1:
                    projectileSystem.addCharge("missile", 1);
                    box.entityManager->getSystem<UIRenderSystem>().render("+1 MISSILE", box.getComponent<TransformComponent>().position);
                    break;
                case 2:
                    projectileSystem.addCharge("arrow", GetRandomValue(1,3));
                    box.entityManager->getSystem<UIRenderSystem>().render("+1 ARROW", box.getComponent<TransformComponent>().position);

                    break;
                case 3:
                    projectileSystem.arrowSelfDamage -= 5;
                    if (projectileSystem.arrowSelfDamage <= 10) {
                        projectileSystem.arrowSelfDamage = 10;
                        box.entityManager->getSystem<UIRenderSystem>().render("MAX PEN", box.getComponent<TransformComponent>().position);
                    } else {
                        box.entityManager->getSystem<UIRenderSystem>().render("+5 ARROW PEN", box.getComponent<TransformComponent>().position);
                    }
                    break;
                case 4:
                    projectileSystem.bulletDamage += 10;
                    if (projectileSystem.bulletDamage >= 100) {
                        projectileSystem.bulletDamage = 100;
                        box.entityManager->getSystem<UIRenderSystem>().render("MAX DAMAGE", box.getComponent<TransformComponent>().position);
                    } else {
                        box.entityManager->getSystem<UIRenderSystem>().render("+10 DAMAGE", box.getComponent<TransformComponent>().position);
                    }
                    break;
                case 5:
                    box.entityManager->getSystem<EnemySpawnerSystem>().spawnBarrier(box);
                    break;
                default:
                    break;
            }
        }
        PlaySound(box.getComponent<SfxComponent>().dyingSound);
        box.kill();
    }
};

#endif //MYSTERYBOXSYSTEM_H
