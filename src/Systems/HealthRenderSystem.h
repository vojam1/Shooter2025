//
// Created by sputnik on 6/6/25.
//

#ifndef HEALTHRENDERSYSTEM_H
#define HEALTHRENDERSYSTEM_H

#include "../Components/HealthComponent.h"
#include "../Components/HealthRenderComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"

class HealthRenderSystem: public System {
public:
    HealthRenderSystem() {
        requireComponent<TransformComponent>();
        requireComponent<HealthComponent>();
        requireComponent<HealthRenderComponent>();
    }

    void update(Camera3D& camera) {
        for (auto& entity: getSystemEntities()) {
            auto& transform = entity.getComponent<TransformComponent>();
            auto& health = entity.getComponent<HealthComponent>().health;
            std::string renderString = std::to_string(health);
            Vector2 screenCoords = GetWorldToScreen(Vector3(transform.position.x - 0.5f, transform.position.y + 2.0f, transform.position.z), camera);
            DrawText(renderString.c_str(), screenCoords.x, screenCoords.y, 15, Color(255,0,0,200));
        }
    }
};

#endif //HEALTHRENDERSYSTEM_H
