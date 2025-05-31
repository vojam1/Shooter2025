//
// Created by sputnik on 5/31/25.
//

#ifndef PROJECTILECOMPONENT_H
#define PROJECTILECOMPONENT_H

#include "../Common.h"

struct ProjectileComponent {
    std::string tag;
    int16_t damage;
    int16_t selfDamage;

    explicit ProjectileComponent(const std::string& tag = "", const int16_t damage = 100, int16_t selfDamage = 100) {
        this->tag = tag;
        this->damage = damage;
        this->selfDamage = selfDamage;
    }
};

#endif //PROJECTILECOMPONENT_H
