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

    static void drawWeaponUI(const Entity& player) {
        constexpr auto weaponDstRect = Rectangle(50.0f, SCREEN_HEIGHT - 200.f, 150.0f, 150.0f);

        DrawRectangleRec(weaponDstRect, Color(0, 0, 0, 100));

        const std::string& tag = player.getComponent<ProjectileShooterComponent>().tag;

        const std::string texPath = "../res/Textures/" + tag + ".png";
        const Texture texture = LoadTexture(texPath.c_str());

        DrawTexturePro(texture, Rectangle(0,0,150,150),
            weaponDstRect, Vector2(0,0), 0, WHITE);

    }

    static void drawPlayerUI(const Entity& player) {
        const auto& playerHealth = player.getComponent<HealthComponent>().health;
        const auto& playerScore = player.getComponent<ScoreTrackerComponent>().score;

        const Texture heart = LoadTexture("../res/Textures/heart.png");

        DrawText(std::to_string(playerHealth).c_str(), 10.f, 10.f, 50, RED);
        DrawTextureEx(heart, Vector2(80.f, 10.f), 0, 0.35f, RED);
        const std::string scoreText = "SCORE: " + std::to_string(playerScore);
        DrawText(scoreText.c_str(), 10.f, 70.f, 30, BLACK);

    }

    void update(const Entity& player) {
        drawPlayerUI(player);
        drawWeaponUI(player);
    }
};

#endif //UIRENDERSYSTEM_H
