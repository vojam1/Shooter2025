//
// Created by sputnik on 5/19/25.
//

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include <raylib.h>

struct CameraComponent {
    Camera3D camera{};

    explicit CameraComponent(Vector3 position = Vector3{10.0f,10.0f,10.0f}, Vector3 target = Vector3{0,0,0},
        Vector3 up = Vector3{0,1.0f,0}, float fov = 45.0f, int projection = CAMERA_PERSPECTIVE) {
        camera.position = position;
        camera.target = target;
        camera.up = up;
        camera.fovy = fov;
        camera.projection = projection;
    }

};

#endif //CAMERACOMPONENT_H
