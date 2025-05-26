//
// Created by sputnik on 5/19/25.
//

#ifndef GAME_H
#define GAME_H
#include <raylib.h>

#include "../Common.h"
#include "../AssetBank/AssetBank.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"

class Game {
public:
    Game();

    void run();

private:
    const uint16_t SCREEN_WIDTH = 1920;
    const uint16_t SCREEN_HEIGHT = 1080;
    bool isDebug;

    Texture2D skyTexture{};

    void update();
    void render();
    void processInput();

    void setup();
    void unload();

    double timeSinceLastSpawn = 0.0;
    double enemySpawnTime = 2.0;

    static Camera3D camera;
    UniqueRef<EntityManager> entityManager;
    UniqueRef<AssetBank> assetBank;
    UniqueRef<EventBus> eventBus;
};



#endif //GAME_H
