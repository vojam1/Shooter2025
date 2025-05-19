//
// Created by sputnik on 5/19/25.
//

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <raymath.h>

struct TransformComponent {
    Vector3 position{};
    Vector3 scale{};
    double rotation;

    explicit TransformComponent(const Vector3 position = {0, 0, 0} , const Vector3 scale = {1.0f, 1.0f, 1.0f }, const double rotation = 0.0) {
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }
};

#endif //TRANSFORMCOMPONENT_H
