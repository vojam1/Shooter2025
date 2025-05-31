//
// Created by sputnik on 5/26/25.
//

#ifndef PROJECTILESYSTEM_H
#define PROJECTILESYSTEM_H

#include <raylib.h>

#include "../Components/MeshComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../ECS/ECS.h"

class ProjectileSystem : public System {
public:
    ProjectileSystem() {
        requireComponent<ProjectileComponent>();
    }

    void fireProjectile(const UniqueRef<EntityManager>& entityManager, const UniqueRef<AssetBank>& assetBank) {
        for (auto& entity: getSystemEntities()) {
            Entity bullet = entityManager->createEntity();
            bullet.group("bullet");

            auto& playerTransform = entity.getComponent<TransformComponent>();
            auto& projectileComp = entity.getComponent<ProjectileComponent>();

            bullet.addComponent<TransformComponent>(Vector3(playerTransform.position.x, 0, playerTransform.position.z ),
                projectileComp.scale,
                projectileComp.rotation,
                projectileComp.angle);
            bullet.addComponent<RigidbodyComponent>(projectileComp.velocity);
            bullet.addComponent<MeshComponent>(assetBank->getModel(projectileComp.model));
            bullet.addComponent<CollisionSphereComponent>(projectileComp.radius, 5, 5);
        }
    }
};

#endif //PROJECTILESYSTEM_H
