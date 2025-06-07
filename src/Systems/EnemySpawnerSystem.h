//
// Created by sputnik on 5/22/25.
//

#ifndef ENEMYSPAWNERSYSTEM_H
#define ENEMYSPAWNERSYSTEM_H

#include "../Components/HealthRenderComponent.h"
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/MeshComponent.h"

class EnemySpawnerSystem: public System {
public:
    int8_t level = 1;
    double timeSinceLastSpawn = 0;
    double spawnTime = 0;

    std::vector<Entity> barriers {};

    void spawnBarrier(Entity& box) {
        barriers.push_back(box);
    }

    void update(const UniqueRef<EntityManager>& entityManager, const UniqueRef<AssetBank>& assetBank) {
        spawnTime = 2.5f - (static_cast<float>(level) * 0.5f);
        spawnTime = spawnTime <= 0.5f ? 0.5f : spawnTime;
        if (GetTime() - timeSinceLastSpawn > spawnTime) {
            constexpr float posArray[3] = {1.5f, 0.0f, -1.5f};
            const float xPos = posArray[GetRandomValue(0, 2)];
            for (int i=0; i<GetRandomValue(1,3); i++) {
                bool spawnBox = GetRandomValue(0,10) == 5;
                if (spawnBox) {
                    Entity box = entityManager->createEntity();
                    box.group("box");
                    box.addComponent<TransformComponent>(Vector3{xPos, 0.0, -30.f - i*2.f}, Vector3{0.5f, 0.5f, 0.5f});
                    box.addComponent<MeshComponent>(assetBank->getModel("box_model"));
                    box.addComponent<RigidbodyComponent>(Vector3{0,0, 1.f,}, 5.f);
                    box.addComponent<CollisionSphereComponent>(0.5f, 5, 5, YELLOW);
                    box.addComponent<HealthComponent>();
                    continue;
                }
                Entity zombie = entityManager->createEntity();
                zombie.group("enemy");
                zombie.addComponent<TransformComponent>(Vector3{ xPos, 0.2f, -30.0f - i*2.f}, Vector3{ 0.35f, 0.35f, 0.35f });
                zombie.addComponent<MeshComponent>(assetBank->getModel("zombie_model"));
                zombie.addComponent<CollisionSphereComponent>(0.5f, 5, 5, RED);
                zombie.addComponent<RigidbodyComponent>(Vector3{ 0.0f, 0.0f, 1.0f }, 5.0f);
                zombie.addComponent<HealthComponent>();
                zombie.addComponent<HealthRenderComponent>();
                zombie.addComponent<AnimationComponent>(assetBank->getModelAnimation("zombie_animation").first,
                    assetBank->getModelAnimation("zombie_animation").second, 7);
                timeSinceLastSpawn = GetTime();
            }
        }
        for (int i=0; i<barriers.size(); i++) {
            Entity barrier = entityManager->createEntity();
            barrier.group("barrier");
            barrier.addComponent<TransformComponent>(barriers[i].getComponent<TransformComponent>().position,
                Vector3(0.5f, 0.5f, 0.5f));
            barrier.addComponent<MeshComponent>(assetBank->getModel("barrier_model"));
            barrier.addComponent<CollisionSphereComponent>(0.5f, 5, 5, PURPLE);
            barrier.addComponent<HealthComponent>();
            barrier.addComponent<HealthRenderComponent>();
        }
        barriers.clear();
    }
};

#endif //ENEMYSPAWNERSYSTEM_H
