#include <iostream>
#include <raylib.h>
#include <random>

int main() {
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Teto Catch");

    SetTargetFPS(60);

    int playerX = 800;
    int playerY = 800;
    int velocityX = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(100, screenWidth - 100);

    int baguetteX = distrib(gen);
    int baguetteY = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLUE);

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

        DrawRectangle(baguetteX, baguetteY, 100, 100, ORANGE);
        baguetteY += 2;

        EndDrawing();
    }

    return 0;
}