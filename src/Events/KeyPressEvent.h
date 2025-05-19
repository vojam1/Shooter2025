//
// Created by sputnik on 5/19/25.
//

#ifndef KEYPRESSEVENT_H
#define KEYPRESSEVENT_H

#include <raylib.h>

#include "../EventBus/Event.h"

class KeyPressEvent : public Event {
public:
    KeyboardKey key;
    explicit KeyPressEvent(const KeyboardKey key) : key(key) {}
};

#endif //KEYPRESSEVENT_H
