//
// Created by sputnik on 6/1/25.
//

#ifndef UIRENDERSYSTEM_H
#define UIRENDERSYSTEM_H

#include "../ECS/ECS.h"
#include <raylib.h>

class UIRenderSystem: public System {
public:
    UIRenderSystem() = default;

    void drawWeaponUI(const Entity& player) {
        constexpr auto weaponDstRect = Rectangle(50.0f, SCREEN_HEIGHT - 200.f, 150.0f, 150.0f);

        DrawRectangleRec(weaponDstRect, Color(0, 0, 0, 100));

        const std::string& tag = player.getComponent<ProjectileShooterComponent>().tag;

        std::string texPath = "../res/Textures/" + tag + ".png";
        Texture texture = LoadTexture(texPath.c_str());

        DrawTexturePro(texture, Rectangle(0,0,150,150),
            weaponDstRect, Vector2(0,0), 0, WHITE);

    }

    void drawPlayerUI(const Entity& player) {
        auto& playerHealth = player.getComponent<HealthComponent>().health;

        DrawText(std::to_string(playerHealth).c_str(), 10.f, 10.f, 50, RED);       // Draw text (using default font)
    }

    void update(const Entity& player) {
        drawPlayerUI(player);
        drawWeaponUI(player);
    }
};

#endif //UIRENDERSYSTEM_H
