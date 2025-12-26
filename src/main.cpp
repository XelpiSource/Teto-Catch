#include <iostream>
#include <raylib.h>

int main() {
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Teto Catch");

    SetTargetFPS(60);

    int playerX = 800;
    int playerY = 800;
    int velocityX = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLUE);

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

        EndDrawing();
    }

    return 0;
}