//
// Created by sputnik on 5/19/25.
//

#ifndef GAME_H
#define GAME_H
#include <raylib.h>

#include "../Common.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"

class Game {
public:
    Game();

    void run();

private:
    const uint16_t SCREEN_WIDTH = 1920;
    const uint16_t SCREEN_HEIGHT = 1080;

    void update();
    void render();
    void setup();

    static Camera3D camera;
    UniqueRef<EntityManager> entityManager;
    UniqueRef<EventBus> eventBus;
};



#endif //GAME_H
