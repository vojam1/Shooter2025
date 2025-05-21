//
// Created by sputnik on 5/19/25.
//

#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include <raylib.h>

struct MeshComponent {
    Model model {};

    explicit MeshComponent(const Mesh &mesh) {
        this->model = LoadModelFromMesh(mesh);
    }

    explicit MeshComponent(const char* filePath = ""){
        this->model = LoadModel(filePath);
    }
};

#endif //MESHCOMPONENT_H
