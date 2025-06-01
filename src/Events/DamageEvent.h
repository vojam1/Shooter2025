//
// Created by sputnik on 5/26/25.
//

#ifndef DAMAGEEVENT_H
#define DAMAGEEVENT_H

#include "../Common.h"
#include "../EventBus/Event.h"

class DamageEvent: public Event {
public:
    int32_t damage;
    const Entity entity;

    explicit DamageEvent(const Entity& entity, const int32_t damage): damage(damage), entity(entity) {}
};

#endif //DAMAGEEVENT_H
