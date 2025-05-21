//
// Created by sputnik on 5/19/25.
//

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <raylib.h>

struct TransformComponent {
    Vector3 position{};
    Vector3 scale{};
    Vector3 rotation{};
    float angle{};

    explicit TransformComponent(const Vector3 position = {0, 0, 0},
            const Vector3 scale = {1.0f, 1.0f, 1.0f },
            const Vector3 rotation = {1.0f, 1.0f, 1.0f },
            const float angle = 0.0f)
    {
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
        this->angle = angle;
    }
};

#endif //TRANSFORMCOMPONENT_H
