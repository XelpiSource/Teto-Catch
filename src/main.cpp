#include <iostream>
#include <raylib.h>

int main() {
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Teto Catch");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLUE);

        EndDrawing();
    }

    return 0;
}