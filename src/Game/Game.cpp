//
// Created by sputnik on 5/19/25.
//

#include "Game.h"
#include "../Util/Debug.h"

#include "../Components/KeyboardControllerComponent.h"
#include "../Components/MeshComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/DeathSystem.h"
#include "../Systems/DebugRenderSystem.h"
#include "../Systems/EnemySpawnerSystem.h"

#include "../Systems/RenderSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/KeyboardControllerSystem.h"

Camera3D Game::camera = { 0 };

Game::Game() {
    entityManager = std::make_unique<EntityManager>();
    eventBus = std::make_unique<EventBus>();
    assetBank = std::make_unique<AssetBank>();

    isDebug = false;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Soulslike2025");
    SetTargetFPS(1000);
    ToggleFullscreen();

    skyTexture = LoadTexture("../res/Textures/sky.png");
}

void Game::setup() {
    DisableCursor();

    entityManager->addSystem<RenderSystem>();
    entityManager->addSystem<MovementSystem>();
    entityManager->addSystem<KeyboardControllerSystem>();
    entityManager->addSystem<DebugRenderSystem>();
    entityManager->addSystem<AnimationSystem>();
    entityManager->addSystem<EnemySpawnerSystem>();
    entityManager->addSystem<DeathSystem>();

    assetBank->addModel("player_model", "../res/Models/Player/Soldier.glb");
    assetBank->addModel("zombie_model", "../res/Models/Zombie/Zombie2.glb");

    camera.position = (Vector3){ 0.0f, 6.f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Entity player = entityManager->createEntity();
    player.tag("player");
    player.addComponent<TransformComponent>(Vector3{ 0.0f, 1.0f, 5.0f }, Vector3{ 0.25f, 0.25f, 0.25f });
    player.addComponent<RigidbodyComponent>(Vector3{ 0.0f, 0.0f, 0.0f }, 5.0f);
    player.addComponent<MeshComponent>(assetBank->getModel("player_model"));
    player.addComponent<KeyboardControllerComponent>();

    Entity ground = entityManager->createEntity();
    ground.addComponent<TransformComponent>(Vector3{ 0.0f, -1.0f, -30.0f }, Vector3{ 4.f, 0.1f, 45.f });
    ground.addComponent<MeshComponent>(GenMeshCube(1.75f, 1.f, 10.f));

}


void Game::run(){
    setup();
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        Logger::log("FPS= " + std::to_string(GetFPS()));
        processInput();
        update();
        render();
    }
    unload();
}

void Game::update() {
    const float deltaTime = GetFrameTime();
    UpdateCamera(&camera, CAMERA_PERSPECTIVE);

    eventBus.reset();
    //entityManager->getSystem<DeathSystem>().subscribeToEvents(eventBus);

    entityManager->update();
    entityManager->getSystem<EnemySpawnerSystem>().update(entityManager, assetBank);
    entityManager->getSystem<MovementSystem>().update(deltaTime);
    entityManager->getSystem<KeyboardControllerSystem>().update();
    entityManager->getSystem<AnimationSystem>().update(deltaTime);
}


void Game::render(){
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawTexture(skyTexture, 0, 0, WHITE);

    BeginMode3D(camera);

        entityManager->getSystem<RenderSystem>().update(camera);

    EndMode3D();

    if (isDebug) {
        entityManager->getSystem<DebugRenderSystem>().update();
    }

    EndDrawing();
}

void Game::processInput() {
    if (IsKeyPressed(KEY_COMMA)) {
        isDebug = !isDebug;
    }
}


void Game::unload() {
    UnloadTexture(skyTexture);
}