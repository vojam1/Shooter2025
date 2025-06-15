//
// Created by sputnik on 5/19/25.
//

#include "Game.h"

#include <iostream>

#include "../Util/Debug.h"

#include "../Components/KeyboardControllerComponent.h"
#include "../Components/MeshComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/CollisionSphereComponent.h"
#include "../Components/ProjectileShooterComponent.h"

#include "../Systems/AnimationSystem.h"
#include "../Systems/CollisionResolutionSystem.h"
#include "../Systems/CollisionShapesRenderSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/DebugRenderSystem.h"
#include "../Systems/EnemySpawnerSystem.h"
#include "../Systems/HealthRenderSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/KeyboardControllerSystem.h"
#include "../Systems/MysteryBoxSystem.h"
#include "../Systems/ProjectileSystem.h"
#include "../Systems/UIRenderSystem.h"

Camera3D Game::camera = { 0 };

Game::Game() {
    entityManager = std::make_unique<EntityManager>();
    assetBank = std::make_unique<AssetBank>();
    eventBus = std::make_unique<EventBus>();
    isDebug = false;
    isInit = false;
    maxLevel = false;
    level = 1;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shoot'Em Up!");
    SetTargetFPS(60);
    ToggleFullscreen();
    DisableCursor();
    InitAudioDevice();

    skyTexture = LoadTexture("../res/Textures/sky.png");
    music = LoadMusicStream("../res/Sounds/game-music-loop.mp3");
}

void Game::setup() {
    entityManager->addSystem<RenderSystem>();
    entityManager->addSystem<MovementSystem>();
    entityManager->addSystem<KeyboardControllerSystem>();
    entityManager->addSystem<DebugRenderSystem>();
    entityManager->addSystem<AnimationSystem>();
    entityManager->addSystem<EnemySpawnerSystem>();
    entityManager->addSystem<DamageSystem>();
    entityManager->addSystem<CollisionShapesRenderSystem>();
    entityManager->addSystem<CollisionSystem>();
    entityManager->addSystem<ProjectileSystem>();
    entityManager->addSystem<UIRenderSystem>();
    entityManager->addSystem<CollisionResolutionSystem>();
    entityManager->addSystem<MysteryBoxSystem>();
    entityManager->addSystem<HealthRenderSystem>();

    assetBank->addModel("player_model", "../res/Models/Player/Tank.glb");

    assetBank->addModel("zombie_model", "../res/Models/Enemy/Zombie.glb");
    assetBank->addModelAnimation("zombie_animation", "../res/Models/Enemy/Zombie.glb");

    assetBank->addModel("bullet_model", "../res/Models/Projectile/Bullet.glb");
    assetBank->addModel("missile_model", "../res/Models/Projectile/Missile.glb");
    assetBank->addModel("arrow_model", "../res/Models/Projectile/Arrow.glb");
    assetBank->addModel("box_model", "../res/Models/Objects/Box.glb");
    assetBank->addModel("barrier_model", "../res/Models/Objects/Barrier.glb");
    assetBank->addModel("present_model", "../res/Models/Objects/Present.glb");

    assetBank->addSound("gun_shot", "../res/Sounds/gun-shot.mp3", 1.0f);
    assetBank->addSound("arrow", "../res/Sounds/arrow.mp3", 0.4f);
    assetBank->addSound("missile", "../res/Sounds/missile.mp3", 1.0f);
    assetBank->addSound("zombie-dying", "../res/Sounds/zombie-dying.mp3", 0.1f);
    assetBank->addSound("explosion", "../res/Sounds/explosion.mp3", 0.1f);
    assetBank->addSound("box-destroy", "../res/Sounds/box-destroy.mp3", 0.1f);
    assetBank->addSound("game_start", "../res/Sounds/game-start.mp3", 1.0f);
    assetBank->addSound("game_over", "../res/Sounds/game-over.mp3", 1.0f);
    assetBank->addSound("insta-kill", "../res/Sounds/insta-kill.mp3", 1.0f);

    camera.position = (Vector3){ 0.0f, 6.f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Entity player = entityManager->createEntity();
    player.tag("player");
    player.addComponent<TransformComponent>(Vector3{ 0.0f, 1.0f, 5.0f },
                                            Vector3{ 0.15f, 0.15f, 0.15f },
                                            Vector3{ 0.0f, 1.0f, 0.0f },
                                            -90.f);
    player.addComponent<RigidbodyComponent>(Vector3{ 0.0f, 0.0f, 0.0f }, 5.0f);
    player.addComponent<MeshComponent>(assetBank->getModel("player_model"));
    player.addComponent<KeyboardControllerComponent>();
    player.addComponent<HealthComponent>();
    player.addComponent<CollisionSphereComponent>(0.75f, 5, 5, GREEN);
    player.addComponent<ProjectileShooterComponent>("bullet");
    player.addComponent<ScoreTrackerComponent>();

    Entity ground = entityManager->createEntity();
    ground.addComponent<TransformComponent>(Vector3{ 0.0f, -1.0f, -30.0f }, Vector3{ 4.f, 0.1f, 45.f });
    ground.addComponent<MeshComponent>(GenMeshCube(1.75f, 1.f, 10.f));

    maxLevel = false;
    level = 1;
    PlayMusicStream(music);
}

bool Game::showMenu() const {
    if (IsKeyPressed(KEY_ENTER)) {
        PlaySound(assetBank->getSound("game_start"));
        return false;
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Zombie Shoot'Em Up!", SCREEN_WIDTH/10, SCREEN_HEIGHT/3, 150, GREEN);
    DrawText("To start press ENTER...", SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 50, GRAY);
    EndDrawing();
    return true;
}

bool Game::showGameOver(bool highScore) const {
    PlaySound(assetBank->getSound("game_over"));
    while (true) {
        if (IsKeyPressed(KEY_ENTER)) return true;
        if (IsKeyPressed(KEY_ESCAPE)) return false;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Game Over!", 400, 400, 200, RED);
        const int32_t score = entityManager->getEntityFromTag("player").getComponent<ScoreTrackerComponent>().score;
        if (highScore) {
            const std::string scoreStr = "NEW HIGH SCORE: " + std::to_string(score);
            DrawText(scoreStr.c_str(), 550, 650, 75, GOLD);
        } else {
            const std::string scoreStr = "SCORE: " + std::to_string(score);
            DrawText(scoreStr.c_str(), 750, 650, 75, BLACK);
            std::string highScoreStr = "HIGH SCORE: " + std::to_string(HIGH_SCORE);
            DrawText(highScoreStr.c_str(), 30, 990, 45, Color(171, 171, 61, 255));
        }
        DrawText("Press ENTER to play again or ESCAPE to exit...", 1000, 1000, 35, GRAY);
        EndDrawing();
    }
}

void Game::run(){
    setup();
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        if (!isInit && showMenu()) {
            continue;
        }
        isInit = true;
        processInput();
        update();
        if (entityManager->getEntityFromTag("player").getComponent<HealthComponent>().health <= 0) {
            bool highScore = false;
            auto& score = entityManager->getEntityFromTag("player").getComponent<ScoreTrackerComponent>().score;
            if (score != 0 && score > HIGH_SCORE) {
                highScore = true;
                HIGH_SCORE = score;
            }
            if (showGameOver(highScore)) {
                entityManager = std::make_unique<EntityManager>();
                setup();
            } else {
                break;
            }
            continue;
        }
        render();
    }
    unload();
}

void Game::update() {
    UpdateMusicStream(music);
    const float deltaTime = GetFrameTime();
    UpdateCamera(&camera, CAMERA_PERSPECTIVE);

    eventBus->Reset();
    entityManager->getSystem<DamageSystem>().subscribeToEvents(eventBus);
    entityManager->getSystem<CollisionResolutionSystem>().subscribeToEvents(eventBus);
    entityManager->getSystem<MysteryBoxSystem>().subscribeToEvents(eventBus);

    entityManager->update();
    entityManager->getSystem<EnemySpawnerSystem>().update(entityManager, assetBank, level);
    entityManager->getSystem<MovementSystem>().update(deltaTime);
    entityManager->getSystem<KeyboardControllerSystem>().update();
    entityManager->getSystem<AnimationSystem>().update();
    entityManager->getSystem<CollisionSystem>().update(entityManager, eventBus);

    int32_t score = entityManager->getEntityFromTag("player").getComponent<ScoreTrackerComponent>().score;
    if (!maxLevel) {
        if (score > 2000 && score < 5000) {
            level = 2;
        } else if (score > 5000 && score < 10000) {
            level = 3;
        } else if (score > 10000 && score < 20000) {
            level = 4;
            maxLevel = true;
        }
    }
}


void Game::render(){
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawTexture(skyTexture, 0, 0, WHITE);

    BeginMode3D(camera);

        entityManager->getSystem<RenderSystem>().update(camera);

        if (isDebug) {
            entityManager->getSystem<CollisionShapesRenderSystem>().update();
        }

    EndMode3D();

    entityManager->getSystem<UIRenderSystem>().update(entityManager->getEntityFromTag("player"), camera);
    entityManager->getSystem<HealthRenderSystem>().update(camera);


    if (isDebug) {
        entityManager->getSystem<DebugRenderSystem>().update();
    }

    EndDrawing();
}

void Game::processInput() const {
    if (IsKeyPressed(KEY_ENTER)) {
        entityManager->getSystem<ProjectileSystem>().fireProjectile(entityManager, assetBank);
        const std::string& tag = entityManager->getEntityFromTag("player").getComponent<ProjectileShooterComponent>().tag;
        if (tag == "bullet")
            PlaySound(assetBank->getSound("gun_shot"));
        else if (tag == "arrow")
            PlaySound(assetBank->getSound("arrow"));
        else if (tag == "missile")
            PlaySound(assetBank->getSound("missile"));
    }
    if (IsKeyPressed(KEY_ONE)) {
        entityManager->getEntityFromTag("player").addComponent<ProjectileShooterComponent>("bullet");
    }
    if (IsKeyPressed(KEY_TWO)) {
        entityManager->getEntityFromTag("player").addComponent<ProjectileShooterComponent>("arrow");
    }
    if (IsKeyPressed(KEY_THREE)) {
        entityManager->getEntityFromTag("player").addComponent<ProjectileShooterComponent>("missile");
    }
}

void Game::unload() {
    UnloadTexture(skyTexture);
}