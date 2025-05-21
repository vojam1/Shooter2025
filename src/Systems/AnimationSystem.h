//
// Created by sputnik on 5/21/25.
//

#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "../Components/AnimationComponent.h"
#include "../Components/MeshComponent.h"
#include "../ECS/ECS.h"

class AnimationSystem : public System {
public:
    double timeSinceLastFrame {0};

    AnimationSystem() {
        requireComponent<TransformComponent>();
        requireComponent<AnimationComponent>();
        requireComponent<MeshComponent>();
    }

    void update(float deltaTime) {
        for (auto& entity: getSystemEntities()) {
            auto& animation = entity.getComponent<AnimationComponent>();
            const auto& mesh = entity.getComponent<MeshComponent>();

            animation.timeSinceLastFrame += deltaTime;

            if (animation.timeSinceLastFrame > 0.025) {
                const ModelAnimation anim = animation.modelAnimations[animation.animIndex];
                animation.animCurrentFrame = (animation.animCurrentFrame + 1)%anim.frameCount;
                UpdateModelAnimation(mesh.model, anim, animation.animCurrentFrame);
                animation.timeSinceLastFrame = 0.0;
            }
        }
    }
};

#endif //ANIMATIONSYSTEM_H
