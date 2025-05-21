//
// Created by sputnik on 5/19/25.
//

#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../Components/RigidbodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"

class MovementSystem : public System {
public:
    MovementSystem() {
        requireComponent<TransformComponent>();
        requireComponent<RigidbodyComponent>();
    }

    void update(const float deltaTime) const {
        for (auto& entity: getSystemEntities()) {
            auto& transform = entity.getComponent<TransformComponent>();
            const auto& rigidbody = entity.getComponent<RigidbodyComponent>();

            transform.position += rigidbody.velocity * rigidbody.speedMultiplier * deltaTime;
            if (transform.position.x > 1.75f) transform.position.x = 1.75f;
            if (transform.position.x < -1.75f) transform.position.x = -1.75f;
        }
    }
};

#endif //MOVEMENTSYSTEM_H
