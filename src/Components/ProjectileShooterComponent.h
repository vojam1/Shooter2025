//
// Created by sputnik on 5/31/25.
//

#ifndef PROJECTILESHOOTERCOMPONENT_H
#define PROJECTILESHOOTERCOMPONENT_H

struct ProjectileShooterComponent {
    std::string tag;
    std::string modelId;
    Vector3 scale{};
    Vector3 velocity{};
    Vector3 rotation{};
    float angle;
    float radius;
    int16_t damage;
    int16_t selfDamage;
    float fireRate;

    explicit ProjectileShooterComponent(const std::string& tag = "missile",
        const std::string& modelId = "missile_model",
        const Vector3& scale = Vector3(1.0f, 1.0f, 1.0f),
        const Vector3& velocity = Vector3(0.0f, 0.0f, -5.0f),
        const Vector3& rotation = Vector3(0.0f, 0.0f, 0.0f),
        float angle = 0.0f,
        float radius = 0.5f,
        int16_t damage = 0,
        int16_t selfDamage = 0,
        float fireRate = 1.0f)
    {
        this->tag = tag;
        std::map<std::string, int> lookUpMap{
            {"bullet", 1},
            {"arrow", 2},
            {"missile", 3}
        };
        switch (lookUpMap[tag]) {
            case 1:
                this->modelId = "bullet_model";
                this->scale = Vector3(0.05f, 0.05f, 0.05f);
                this->velocity = Vector3(0.0f, 0.0f, -5.0f);
                this->rotation = Vector3(0.0f, 1.0f, 0.0f);
                this->angle = 180.f;
                this->radius = 0.5f;
                this->damage = 25;
                this->selfDamage = 100;
                this->fireRate = 0.25f;
                break;

            case 2:
                this->modelId = "arrow_model";
                this->scale = scale;
                this->velocity = Vector3(0.0f, 0.0f, -7.5f);
                this->rotation = Vector3(0.0f, 1.0f, 0.0f);
                this->angle = 90.f;
                this->radius = radius;
                this->damage = 100;
                this->selfDamage = 25;
                this->fireRate = 1.0f;
                break;

            case 3:
                this->modelId = "missile_model";
                this->scale = Vector3(0.1f, 0.1f, 0.1f);
                this->velocity = Vector3(0.0f, 0.0f, -4.f);
                this->rotation = Vector3(0.0f, 1.0f, 0.0f);
                this->angle = 90.f;
                this->radius = radius;
                this->damage = 100;
                this->selfDamage = 100;
                this->fireRate = 2.0f;
                break;

            default:
                this->modelId = modelId;
                this->scale = scale;
                this->velocity = velocity;
                this->rotation = rotation;
                this->angle = angle;
                this->radius = radius;
                this->damage = damage;
                this->selfDamage = selfDamage;
                this->fireRate = fireRate;
                break;
        }
    }
};

#endif //PROJECTILESHOOTERCOMPONENT_H
