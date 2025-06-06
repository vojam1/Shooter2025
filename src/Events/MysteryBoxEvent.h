//
// Created by sputnik on 6/6/25.
//

#ifndef MYSTERYBOXEVENT_H
#define MYSTERYBOXEVENT_H

#include "../EventBus/Event.h"

class MysteryBoxEvent : public Event {
public:
    Entity box;

    explicit MysteryBoxEvent(const Entity box) : box(box) {}
};

#endif //MYSTERYBOXEVENT_H
