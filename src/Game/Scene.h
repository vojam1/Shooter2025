//
// Created by sputnik on 5/22/25.
//

#ifndef SCENE_H
#define SCENE_H

#include "../ECS/ECS.h"
#include "../Common.h"

class Scene {
public:
    explicit Scene(UniqueRef<EntityManager>& entityManager);

    void loadScene(int level);
    void update();
    void render();

private:
    UniqueRef<EntityManager> entityManager;
};



#endif //SCENE_H
