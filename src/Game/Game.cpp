//
// Created by sputnik on 5/19/25.
//

#include "Game.h"

#include "../Components/KeyboardControllerComponent.h"
#include "../Components/MeshComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"

#include "../Systems/RenderSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/KeyboardControllerSystem.h"

Camera3D Game::camera = { 0 };

Game::Game() {
    entityManager = std::make_unique<EntityManager>();
    eventBus = std::make_unique<EventBus>();

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Soulslike2025");
    SetTargetFPS(60);
    ToggleFullscreen();
}

void Game::setup() {
    DisableCursor();

    entityManager->addSystem<RenderSystem>();
    entityManager->addSystem<MovementSystem>();
    entityManager->addSystem<KeyboardControllerSystem>();

    camera.position = (Vector3){ 0.0f, 10.0f, -10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Entity player = entityManager->createEntity();
    player.addComponent<TransformComponent>(Vector3{ 0.0f, 0.0f, 0.0f });
    player.addComponent<RigidbodyComponent>(Vector3{ 0.0f, 0.0f, 0.0f }, 5.0f);
    player.addComponent<MeshComponent>("../res/Models/Cube/Cube.gltf");
    player.addComponent<KeyboardControllerComponent>();

}


void Game::run(){
    setup();
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        update();
        render();
    }

    CloseWindow();
}

void Game::update() {
    const float deltaTime = GetFrameTime();

    UpdateCamera(&camera, CAMERA_PERSPECTIVE);

    entityManager->update();

    entityManager->getSystem<MovementSystem>().update(deltaTime);
    entityManager->getSystem<KeyboardControllerSystem>().update();
}

void Game::render(){
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(camera);

        entityManager->getSystem<RenderSystem>().update(camera);

        DrawGrid(10, 1.0f);

    EndMode3D();

    EndDrawing();
}
