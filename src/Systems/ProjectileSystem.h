//
// Created by sputnik on 5/26/25.
//

#ifndef PROJECTILESYSTEM_H
#define PROJECTILESYSTEM_H

#include <raylib.h>

#include "../Components/MeshComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"

class ProjectileSystem : public System {
public:
    ProjectileSystem() = default;

    static void fireProjectile(Entity& player, const UniqueRef<EntityManager>& entityManager, const UniqueRef<AssetBank>& assetBank) {
        Entity bullet = entityManager->createEntity();
        bullet.group("bullet");

        auto& playerTransform = player.getComponent<TransformComponent>();
        bullet.addComponent<TransformComponent>(Vector3(playerTransform.position.x, 0, playerTransform.position.z ),
            Vector3(0.05f, 0.05f, 0.05f),
            Vector3(0.0f, 1.0f, 0.0f),
            180.f);
        bullet.addComponent<RigidbodyComponent>(Vector3{0,0,-5.0f});
        bullet.addComponent<MeshComponent>(assetBank->getModel("bullet_model"));
        bullet.addComponent<CollisionSphereComponent>(0.5f, 5, 5);
    }
};

#endif //PROJECTILESYSTEM_H
