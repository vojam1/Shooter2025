//
// Created by sputnik on 5/23/25.
//

#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

struct HealthComponent {
    int16_t health;

    explicit HealthComponent(const int16_t health = 100) : health(health) {}
};

#endif //HEALTHCOMPONENT_H
