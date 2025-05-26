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
#include "../ECS/ECS.h"

class ProjectileSystem : public System {
public:
    ProjectileSystem() = default;

    void update(const UniqueRef<EntityManager>& entityManager, UniqueRef<AssetBank>& assetBank) {
        Entity bullet = entityManager->createEntity();
        bullet.addComponent<TransformComponent>();
        bullet.addComponent<RigidbodyComponent>(Vector3{0,0,-2.0f});
        bullet.addComponent<MeshComponent>(assetBank->getModel("bullet_model"));
    }
};

#endif //PROJECTILESYSTEM_H
