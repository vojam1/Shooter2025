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

    void update() {
        for (auto& entity: getSystemEntities()) {
            auto& animation = entity.getComponent<AnimationComponent>();
            const auto& mesh = entity.getComponent<MeshComponent>();
            const ModelAnimation anim = animation.modelAnimations[animation.animIndex];

            animation.animCurrentFrame += 1;
            if (animation.animCurrentFrame > anim.frameCount) {
                animation.animCurrentFrame = 0;
            }
            UpdateModelAnimation(mesh.model, anim, animation.animCurrentFrame);
        }
    }
};

#endif //ANIMATIONSYSTEM_H
