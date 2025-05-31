//
// Created by sputnik on 5/31/25.
//

#ifndef PROJECTILECOMPONENT_H
#define PROJECTILECOMPONENT_H

struct ProjectileComponent {
    std::string model;
    Vector3 scale{};
    Vector3 velocity{};
    Vector3 rotation{};
    float angle;
    float radius;

    explicit ProjectileComponent(const std::string& modelId = "missile_model",
        const Vector3& scale = Vector3(1.0f, 1.0f, 1.0f),
        const Vector3& velocity = Vector3(0.0f, 0.0f, -5.0f),
        const Vector3& rotation = Vector3(0.0f, 0.0f, 0.0f),
        const float angle = 0.0f,
        const float radius = 0.5f)
    {
        this->model = modelId;
        std::map<std::string, int> lookUpMap{
            {"bullet_model", 1},
            {"arrow_model", 2},
            {"missile_model", 3}
        };
        switch (lookUpMap[modelId]) {
            case 1:
                this->scale = Vector3(0.05f, 0.05f, 0.05f);
                this->velocity = Vector3(0.0f, 0.0f, -5.0f);
                this->rotation = Vector3(0.0f, 1.0f, 0.0f);
                this->angle = 180.f;
                this->radius = 0.5f;
                break;

            case 2:
                this->scale = scale;
                this->velocity = Vector3(0.0f, 0.0f, -7.5f);
                this->rotation = Vector3(0.0f, 1.0f, 0.0f);
                this->angle = 90.f;
                this->radius = radius;
                break;

            case 3:
                this->scale = Vector3(0.1f, 0.1f, 0.1f);
                this->velocity = Vector3(0.0f, 0.0f, -4.f);
                this->rotation = Vector3(0.0f, 1.0f, 0.0f);
                this->angle = 90.f;
                this->radius = radius;
                break;

            default:
                this->scale = scale;
                this->velocity = velocity;
                this->rotation = rotation;
                this->angle = angle;
                this->radius = radius;
                break;
        }
    }
};

#endif //PROJECTILECOMPONENT_H
