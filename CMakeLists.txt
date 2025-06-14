cmake_minimum_required(VERSION 3.31)
project(Shooter2025)

set(CMAKE_CXX_STANDARD 20)
add_executable(Shooter2025 src/main.cpp
        src/ECS/ECS.cpp
        src/ECS/ECS.h
        src/Common.h
        src/Game/Game.cpp
        src/Game/Game.h
        src/Components/MeshComponent.h
        src/Components/TransformComponent.h
        src/Components/RigidbodyComponent.h
        src/Systems/RenderSystem.h
        src/Systems/MovementSystem.h
        src/Components/KeyboardControllerComponent.h
        src/EventBus/Event.h
        src/EventBus/EventBus.h
        src/Systems/KeyboardControllerSystem.h
        src/Events/KeyPressEvent.h
        src/Components/CameraComponent.h
        src/Util/Debug.h
        src/Systems/DebugRenderSystem.h
        src/Components/AnimationComponent.h
        src/Systems/AnimationSystem.h
        src/Systems/EnemySpawnerSystem.h
        src/AssetBank/AssetBank.cpp
        src/AssetBank/AssetBank.h
        src/Components/HealthComponent.h
        src/Systems/ProjectileSystem.h
        src/Systems/DamageSystem.h
        src/Events/DamageEvent.h
        src/Components/CollisionSphereComponent.h
        src/Systems/CollisionShapesRenderSystem.h
        src/Systems/CollisionSystem.h
        src/Components/ProjectileComponent.h
        src/Events/CollisionEvent.h
        src/Components/ProjectileComponent.h
        src/Systems/UIRenderSystem.h
        src/Systems/CollisionResolutionSystem.h
        src/Components/ScoreTrackerComponent.h
        src/Events/MysteryBoxEvent.h
        src/Systems/MysteryBoxSystem.h
        src/Components/HealthRenderComponent.h
        src/Systems/HealthRenderSystem.h
        src/Components/SfxComponent.h
)

include_directories("/usr/local/include")
target_link_libraries(Shooter2025 "/usr/local/lib/libraylib.a")