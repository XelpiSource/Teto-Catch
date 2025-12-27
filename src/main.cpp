#include <iostream>
#include <raylib.h>
#include <random>
#include <string>

int main() {
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Teto Catch");

    SetTargetFPS(60);

    // random X coord for baguette
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(100, screenWidth - 300);

    // player data
    int playerX = 800;
    int playerY = 800;
    int velocityX = 0;

    // baguette data
    int baguetteX = distrib(gen);
    int baguetteY = 0;
    int baguetteCount = 0;
    int baguetteSpeed = 1;

    // Sprites

    // Background
    const Texture2D backgroundTx = LoadTexture(RESOURCES_PATH "background.png");
    Rectangle sourceRecBackground = { 0.0f, 0.0f, static_cast<float>(backgroundTx.width), static_cast<float>(backgroundTx.height) };
    Rectangle destRecBackground = { 0.0f, 0.0f, screenWidth, screenHeight };
    Vector2 origin = { 0.0f, 0.0f };

    // Player Texture
    const Texture2D playerTx = LoadTexture(RESOURCES_PATH "miniTeto.png");
    Rectangle sourceRecPlayer = { 0.0f, 0.0f, static_cast<float>(playerTx.width), static_cast<float>(playerTx.height) };
    Rectangle destRecPlayer = { static_cast<float>(playerX), static_cast<float>(playerY), 300, 300 };

    // Baguette Texture
    const Texture2D baguetteTx = LoadTexture(RESOURCES_PATH "baguette.png");
    Rectangle sourceRecBaguette = { 0.0f, 0.0f, static_cast<float>(baguetteTx.width), static_cast<float>(baguetteTx.height) };
    Rectangle destRecBaguette = { static_cast<float>(baguetteX), static_cast<float>(baguetteY), 200, 200 };

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLUE);

        DrawTexturePro(backgroundTx, sourceRecBackground, destRecBackground, origin, 0.0f, WHITE);

        DrawText(("Score: " + std::to_string(baguetteCount)).c_str(), 10, 10, 60,WHITE);

        #pragma region player

        DrawTexturePro(playerTx, sourceRecPlayer, destRecPlayer, origin, 0.0f, WHITE);

        // to not run offscreen
        if (playerX > screenWidth - 280) {
            velocityX -= 5;
        } else if (playerX < -30) {
            velocityX += 5;
        }

        if (IsKeyDown(KEY_A) && velocityX > -20) {
            velocityX -= 4;
        } else if (IsKeyDown(KEY_D) && velocityX < 20) {
            velocityX += 4;
        }

        playerX += velocityX;
        destRecPlayer.x = static_cast<float>(playerX);

        if (velocityX > 0) {
            velocityX -= 1;
        } else if (velocityX < 0) {
            velocityX += 1;
        }

        #pragma endregion

        #pragma region baguette

        DrawTexturePro(baguetteTx, sourceRecBaguette, destRecBaguette, origin, 0.0f, WHITE);
        baguetteY += 2 + baguetteCount;
        destRecBaguette.y = static_cast<float>(baguetteY);

        if (baguetteY >= playerY - 50 && baguetteX >= playerX && baguetteX <= playerX + 200) {
            baguetteCount++;

            if (baguetteSpeed < 5) {
                baguetteSpeed++;
            }

            baguetteX = distrib(gen);
            baguetteY = 0;
            destRecBaguette.x = static_cast<float>(baguetteX);
            destRecBaguette.y = static_cast<float>(baguetteY);

        } else if (baguetteY > screenHeight - 100) {
            baguetteCount = 0;
            baguetteSpeed = 1;
            baguetteX = distrib(gen);
            baguetteY = 0;
            destRecBaguette.x = static_cast<float>(baguetteX);
            destRecBaguette.y = static_cast<float>(baguetteY);
        }

        #pragma endregion

        EndDrawing();
    }

    return 0;
}
