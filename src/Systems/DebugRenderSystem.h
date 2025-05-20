//
// Created by sputnik on 5/20/25.
//

#ifndef DEBUGRENDERSYSTEM_H
#define DEBUGRENDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Util/Debug.h"

class DebugRenderSystem: public System {
public:
    DebugRenderSystem() = default;

    void update() {
        auto debugRect = Rectangle(10.0f, 10.f, 300.0f, 100.0f);
        constexpr int fontSize = 24;
        const std::string message = Logger::getString();

        DrawRectangleRec(debugRect, Color(0, 0, 0, 100));
        DrawText(Logger::getString().c_str(),
            static_cast<int>(debugRect.x) + fontSize,
            static_cast<int>(debugRect.x) + fontSize,
            fontSize,
            WHITE);
        Logger::reset();
    }
};

#endif //DEBUGRENDERSYSTEM_H
