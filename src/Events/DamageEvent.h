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
    Entity entity;

    explicit DamageEvent(Entity& entity, int32_t damage): entity(entity), damage(damage) {}
};

#endif //DAMAGEEVENT_H
