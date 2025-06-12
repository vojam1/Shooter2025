//
// Created by sputnik on 5/26/25.
//

#ifndef PROJECTILESYSTEM_H
#define PROJECTILESYSTEM_H

#include <raylib.h>

#include "../Components/MeshComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/ProjectileShooterComponent.h"
#include "../ECS/ECS.h"

class ProjectileSystem : public System {
public:
    bool instaKill = false;
    double instaKillTime = 0.0;
    int32_t previousDamage = 0;

    double lastSpawnTime = 0.0;

    int32_t bulletCharges = 2000000000;
    int32_t bulletDamage = 25;

    int32_t arrowCharges = 3;
    int32_t arrowDamage = 999;
    int32_t arrowSelfDamage = 25;

    int32_t missileCharges = 1;
    int32_t missileDamage = 999;

    ProjectileSystem() {
        requireComponent<ProjectileShooterComponent>();
    }

    void activateInstaKill() {
        instaKill = true;
        previousDamage = bulletDamage;
        bulletDamage = 999;
        instaKillTime = GetTime();
    }

    void addCharge(const std::string& tag, int32_t charge) {
        if (tag == "bullet") {
            bulletCharges += charge;
        }
        else if (tag == "arrow") {
            arrowCharges += charge;
        }
        else if (tag == "missile") {
            missileCharges += charge;
        }
    }

    int32_t getDamage(const std::string& tag) {
        if (tag == "bullet") {
            return bulletDamage;
        }
        if (tag == "arrow") {
            return arrowDamage;
        }
        if (tag == "missile") {
            return missileDamage;
        }
        return 0;
    }
    void fireProjectile(const UniqueRef<EntityManager>& entityManager, const UniqueRef<AssetBank>& assetBank) {
        for (auto& entity: getSystemEntities()) {
            auto& projectileComp = entity.getComponent<ProjectileShooterComponent>();

            if (GetTime() - lastSpawnTime <= projectileComp.fireRate) { continue; }

            if (instaKill && GetTime() - instaKillTime >= 5.0) {
                bulletDamage = previousDamage;
                instaKill = false;
            }

            if (projectileComp.tag == "bullet") {
                if (bulletCharges <= 0)
                    continue;
                bulletCharges--;
            }
            if (projectileComp.tag == "arrow") {
                if (arrowCharges <= 0)
                    continue;
                arrowCharges--;
            }
            if (projectileComp.tag == "missile") {
                if (missileCharges <= 0)
                    continue;
                missileCharges--;
            }

            Entity bullet = entityManager->createEntity();
            bullet.group("bullet");

            auto& playerTransform = entity.getComponent<TransformComponent>();
            bullet.addComponent<TransformComponent>(Vector3(playerTransform.position.x, 0, playerTransform.position.z - 1.f ),
                projectileComp.scale,
                projectileComp.rotation,
                projectileComp.angle);
            bullet.addComponent<RigidbodyComponent>(projectileComp.velocity);
            bullet.addComponent<MeshComponent>(assetBank->getModel(projectileComp.modelId));
            bullet.addComponent<CollisionSphereComponent>(projectileComp.radius, 5, 5);
            bullet.addComponent<ProjectileComponent>(projectileComp.tag, getDamage(projectileComp.tag), projectileComp.tag == "arrow" ? arrowSelfDamage : projectileComp.selfDamage);
            bullet.addComponent<HealthComponent>();
            lastSpawnTime = GetTime();
        }
    }
};

#endif //PROJECTILESYSTEM_H
