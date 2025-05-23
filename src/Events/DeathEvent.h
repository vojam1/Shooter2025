//
// Created by sputnik on 5/23/25.
//

#ifndef DEATHEVENT_H
#define DEATHEVENT_H

#include "../EventBus/Event.h"
#include "../ECS/ECS.h"

class DeathEvent : public Event {
public:
    Entity entityToKill;
};

#endif //DEATHEVENT_H
