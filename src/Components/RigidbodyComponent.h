//
// Created by sputnik on 5/19/25.
//

#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <raymath.h>

struct RigidbodyComponent {
    Vector3 velocity{};
    float speedMultiplier{};

    explicit RigidbodyComponent(const Vector3 velocity = {0, 0, 0}, float speedMultiplier = 1.f) {
        this->velocity = velocity;
        this->speedMultiplier = speedMultiplier;
    }

};

#endif //RIGIDBODYCOMPONENT_H
