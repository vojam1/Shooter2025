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
    double lastSpawnTime = 0.0;

    ProjectileSystem() {
        requireComponent<ProjectileShooterComponent>();
    }

    void fireProjectile(const UniqueRef<EntityManager>& entityManager, const UniqueRef<AssetBank>& assetBank) {
        for (auto& entity: getSystemEntities()) {
            auto& projectileComp = entity.getComponent<ProjectileShooterComponent>();

            if (GetTime() - lastSpawnTime <= projectileComp.fireRate) { continue; }

            Entity bullet = entityManager->createEntity();
            bullet.group("bullet");

            auto& playerTransform = entity.getComponent<TransformComponent>();
            bullet.addComponent<TransformComponent>(Vector3(playerTransform.position.x, 0, playerTransform.position.z ),
                projectileComp.scale,
                projectileComp.rotation,
                projectileComp.angle);
            bullet.addComponent<RigidbodyComponent>(projectileComp.velocity);
            bullet.addComponent<MeshComponent>(assetBank->getModel(projectileComp.modelId));
            bullet.addComponent<CollisionSphereComponent>(projectileComp.radius, 5, 5);
            bullet.addComponent<ProjectileComponent>(projectileComp.tag, projectileComp.damage, projectileComp.selfDamage);
            bullet.addComponent<HealthComponent>();
            lastSpawnTime = GetTime();
        }
    }
};

#endif //PROJECTILESYSTEM_H
