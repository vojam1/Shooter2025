//
// Created by sputnik on 5/26/25.
//

#ifndef COLLISIONSPHERECOMPONENT_H
#define COLLISIONSPHERECOMPONENT_H

#include <raylib.h>
#include "../Common.h"

struct CollisionSphereComponent {
    Mesh sphereMesh;
    float radius;
    int16_t rings;
    int16_t slices;
    Color color;

    CollisionSphereComponent(float radius = 30.f, int16_t rings = 1, int16_t slices = 1, Color color = WHITE) {
        this->sphereMesh = GenMeshSphere(radius, rings, slices);
        this->radius = radius;
        this->rings = rings;
        this->slices = slices;
        this->color = color;
    }
};

#endif //COLLISIONSPHERECOMPONENT_H
