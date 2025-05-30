//
// Created by sputnik on 5/22/25.
//

#ifndef ENEMYSPAWNERSYSTEM_H
#define ENEMYSPAWNERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/MeshComponent.h"

class EnemySpawnerSystem: public System {
public:
    double timeSinceLastSpawn = 0;
    double spawnTime = 2.0;

    void update(const UniqueRef<EntityManager>& entityManager, const UniqueRef<AssetBank>& assetBank) {
        if (GetTime() - timeSinceLastSpawn > spawnTime) {
            constexpr float posArray[3] = {1.5f, 0.0f, -1.5f};
            const float xPos = posArray[GetRandomValue(0, 2)];
            for (int i=0; i<GetRandomValue(4,7); i++) {
                Entity zombie = entityManager->createEntity();
                zombie.group("enemy");
                zombie.addComponent<TransformComponent>(Vector3{ xPos, 0.0f, -30.0f - static_cast<float>(i) }, Vector3{ 0.35f, 0.35f, 0.35f });
                zombie.addComponent<MeshComponent>(assetBank->getModel("zombie_model"));
                zombie.addComponent<CollisionSphereComponent>(0.5f, 5, 5, RED);
                zombie.addComponent<RigidbodyComponent>(Vector3{ 0.0f, 0.0f, 1.0f }, 5.0f);
                zombie.addComponent<HealthComponent>();
                zombie.addComponent<AnimationComponent>(assetBank->getModelAnimation("zombie_animation").first,
                    assetBank->getModelAnimation("zombie_animation").second, 7);
            }
            timeSinceLastSpawn = GetTime();
        }
    }
};

#endif //ENEMYSPAWNERSYSTEM_H
