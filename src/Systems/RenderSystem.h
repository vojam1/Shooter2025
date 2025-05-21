//
// Created by sputnik on 5/19/25.
//

#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <raylib.h>

#include "../Components/TransformComponent.h"
#include "../Components/MeshComponent.h"
#include "../ECS/ECS.h"

class RenderSystem: public System {
public:
    RenderSystem() {
        requireComponent<TransformComponent>();
        requireComponent<MeshComponent>();
    }

    void update(const Camera3D& camera) const {
        for (const Entity& entity: getSystemEntities()) {
            const auto& transform = entity.getComponent<TransformComponent>();
            const auto& mesh = entity.getComponent<MeshComponent>();

            DrawModelEx(mesh.model, transform.position, transform.rotation, transform.angle, transform.scale, WHITE);

        }
    }
};

#endif //RENDERSYSTEM_H