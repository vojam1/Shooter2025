//
// Created by sputnik on 6/1/25.
//

#ifndef UIRENDERSYSTEM_H
#define UIRENDERSYSTEM_H

#include <charconv>

#include "../ECS/ECS.h"
#include <raylib.h>

class UIRenderSystem: public System {
public:
    Texture bulletTexture {};
    Texture arrowTexture {};
    Texture missileTexture {};

    UIRenderSystem() {
        bulletTexture = LoadTexture("../res/Textures/bullet.png");
        arrowTexture = LoadTexture("../res/Textures/arrow.png");
        missileTexture = LoadTexture("../res/Textures/missile.png");
    };

    void drawWeaponUI(const Entity& player) const {
        std::string tag = player.getComponent<ProjectileShooterComponent>().tag;

        int32_t bulletCharges = player.entityManager->getSystem<ProjectileSystem>().bulletCharges;
        int32_t arrowCharges = player.entityManager->getSystem<ProjectileSystem>().arrowCharges;
        int32_t missileCharges = player.entityManager->getSystem<ProjectileSystem>().missileCharges;

        Color bulletColor = Color(0,0,0,50);
        Color arrowColor = Color(0,0,0,50);
        Color missileColor = Color(0,0,0,50);

        if (tag == "bullet") {
            bulletColor = Color(0,255,0, 150);
        } else if (tag == "arrow") {
            arrowColor = Color(0,0,255, 150);
        } else if (tag == "missile") {
            missileColor = Color(255,0,0, 150);
        }

        DrawRectangle(30.f, SCREEN_HEIGHT- 200.f, 150.f, 150.f, bulletColor);
        DrawRectangle(190.f, SCREEN_HEIGHT- 200.f, 150.f, 150.f, arrowColor);
        DrawRectangle(350.f, SCREEN_HEIGHT- 200.f, 150.f, 150.f, missileColor);

        DrawTexturePro(bulletTexture, Rectangle(0,0,150,150),
        Rectangle(30.f, SCREEN_HEIGHT-200.f, 150.f, 150.f), Vector2(0,0), 0, WHITE);

        DrawTexturePro(arrowTexture, Rectangle(0,0,150,150),
    Rectangle(190.f, SCREEN_HEIGHT-200.f, 150.f, 150.f), Vector2(0,0), 0, WHITE);

        DrawTexturePro(missileTexture, Rectangle(0,0,150,150),
    Rectangle(350.f, SCREEN_HEIGHT-200.f, 150.f, 150.f), Vector2(0,0), 0, WHITE);

        //DrawText(std::to_string(bulletCharges).c_str(), 35.f, SCREEN_HEIGHT-200.f, 40, WHITE);
        DrawText(std::to_string(arrowCharges).c_str(), 195.f, SCREEN_HEIGHT-200.f,  40, WHITE);
        DrawText(std::to_string(missileCharges).c_str(), 355, SCREEN_HEIGHT - 200.f, 40, WHITE);
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
