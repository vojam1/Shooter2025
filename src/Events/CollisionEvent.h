//
// Created by sputnik on 5/31/25.
//

#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "../EventBus/Event.h"
#include "../ECS/ECS.h"

class CollisionEvent : public Event {
public:
    Entity a;
    Entity b;

    CollisionEvent(Entity a, Entity b) : a(a), b(b) {}
};

#endif //COLLISIONEVENT_H
