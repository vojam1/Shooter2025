//
// Created by sputnik on 5/21/25.
//

#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <raylib.h>

#include "../Common.h"

struct AnimationComponent {
    int32_t animCount {};
    int32_t animIndex {};
    int32_t animCurrentFrame {0};
    ModelAnimation* modelAnimations {};
    double timeSinceLastFrame {0};

    explicit AnimationComponent(ModelAnimation* modelAnimations = nullptr, const int32_t animCount = 0, const int32_t animIndex = 0){
        this->modelAnimations = modelAnimations;
        this->animCount = animCount;
        this->animIndex = animIndex;
    }
};

#endif //ANIMATIONCOMPONENT_H
