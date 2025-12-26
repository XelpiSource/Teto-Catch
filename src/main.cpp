#include <iostream>
#include <raylib.h>
#include <random>
#include <string>

int main() {
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Teto Catch");

    SetTargetFPS(60);


    // player data
    int playerX = 800;
    int playerY = 800;
    int velocityX = 0;

    // random X coord for baguette
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(100, screenWidth - 100);

    // baguette data
    int baguetteX = distrib(gen);
    int baguetteY = 0;
    int baguetteCount = 0;
    int baguetteSpeed = 1;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLUE);

        DrawText(("Score: " + std::to_string(baguetteCount)).c_str(), 10, 10, 60,WHITE);

        #pragma region player

        DrawRectangle(playerX, playerY, 100, 100, RED);

        if (IsKeyDown(KEY_A) && velocityX > -20) {
            velocityX -= 5;
        } else if (IsKeyDown(KEY_D) && velocityX < 20) {
            velocityX += 5;
        }

        playerX += velocityX;

        if (velocityX > 0) {
            velocityX -= 1;
        } else if (velocityX < 0) {
            velocityX += 1;
        }

        #pragma endregion

        #pragma region baguette

        DrawRectangle(baguetteX, baguetteY, 100, 100, ORANGE);
        baguetteY += 2 + baguetteCount;

        if (baguetteY >= playerY - 100 && baguetteX >= playerX && baguetteX <= playerX + 130) {
            baguetteCount++;

            if (baguetteSpeed < 5) {
                baguetteSpeed++;
            }

            baguetteX = distrib(gen);
            baguetteY = 0;
        } else if (baguetteY > screenHeight - 100) {
            baguetteCount = 0;
            baguetteSpeed = 1;
            baguetteX = distrib(gen);
            baguetteY = 0;
        }

        #pragma endregion

        EndDrawing();
    }

    return 0;
}
