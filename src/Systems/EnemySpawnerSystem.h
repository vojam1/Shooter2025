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
    double timeSinceLastSpawn = 0;
    double spawnTime = 0;
    int32_t maxEnemies = 0;

    int32_t enemyHealth = 100;

    int32_t boxSpawnChance = 0;

    std::vector<Entity> barriers {};

    void spawnBarrier(Entity& box) {
        barriers.push_back(box);
    }

    void update(const UniqueRef<EntityManager>& entityManager, const UniqueRef<AssetBank>& assetBank, int32_t level) {
        switch (level) {
            case 1:
                spawnTime = 2.0f;
                maxEnemies = 5;
                enemyHealth = 100;
                boxSpawnChance = 20;
                break;
            case 2:
                spawnTime = 1.5f;
                maxEnemies = 7;
                enemyHealth = 100;
                boxSpawnChance = 15;
                break;
            case 3:
                spawnTime = 1.5f;
                maxEnemies = 10;
                enemyHealth = 150;
                boxSpawnChance = 10;
                break;
            case 4:
                spawnTime = 1.0f;
                maxEnemies = 10;
                enemyHealth = 200;
                boxSpawnChance = 10;
                break;
        }
        if (GetTime() - timeSinceLastSpawn > spawnTime) {
            constexpr float posArray[3] = {1.5f, 0.0f, -1.5f};
            const float xPos = posArray[GetRandomValue(0, 2)];
            for (int i=0; i<GetRandomValue(1,maxEnemies); i++) {
                bool spawnBox = GetRandomValue(0,boxSpawnChance) == 10;
                bool spawnPresent = GetRandomValue(0,20) == 15;
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
                if (spawnPresent) {
                    Entity present = entityManager->createEntity();
                    present.group("box");
                    present.group("present");
                    present.addComponent<TransformComponent>(Vector3{xPos, 0.0, -30.f - i*2.f});
                    present.addComponent<MeshComponent>(assetBank->getModel("present_model"));
                    present.addComponent<RigidbodyComponent>(Vector3{0,0, 1.f,}, 5.f);
                    present.addComponent<CollisionSphereComponent>(0.5f, 5, 5, YELLOW);
                    present.addComponent<HealthComponent>();
                    continue;
                }
                Entity zombie = entityManager->createEntity();
                zombie.group("enemy");
                zombie.addComponent<TransformComponent>(Vector3{ xPos, 0.2f, -30.0f - i*2.f}, Vector3{ 0.35f, 0.35f, 0.35f });
                zombie.addComponent<MeshComponent>(assetBank->getModel("zombie_model"));
                zombie.addComponent<CollisionSphereComponent>(0.5f, 5, 5, RED);
                zombie.addComponent<RigidbodyComponent>(Vector3{ 0.0f, 0.0f, 1.0f }, 5.0f);
                zombie.addComponent<HealthComponent>(enemyHealth);
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
