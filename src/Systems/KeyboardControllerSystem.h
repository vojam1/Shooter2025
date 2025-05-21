//
// Created by sputnik on 5/19/25.
//

#ifndef KEYBOARDCONTROLLERSYSTEM_H
#define KEYBOARDCONTROLLERSYSTEM_H

#include "../Components/KeyboardControllerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Events/KeyPressEvent.h"
#include "../ECS/ECS.h"

class KeyboardControllerSystem : public System {
public:
    KeyboardControllerSystem() {
        requireComponent<RigidbodyComponent>();
        requireComponent<KeyboardControllerComponent>();
    }

    void update() {
        for (auto& entity: getSystemEntities()) {
            auto& rigidbody = entity.getComponent<RigidbodyComponent>();

            auto inputVector = Vector2(0,0);

            if (IsKeyDown(KEY_D)) {
                inputVector.x = 1.0f;
            }
            if(IsKeyDown(KEY_A)) {
                inputVector.y = 1.0f;
            }
            rigidbody.velocity.x = (inputVector.x - inputVector.y);
        }
    }

};

#endif //KEYBOARDCONTROLLERSYSTEM_H
