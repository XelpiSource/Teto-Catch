#include <iostream>
#include <raylib.h>
#include <random>
#include <string>

int main() {
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;
    constexpr int logWidth = 1920;
    constexpr int logHeight = 1080;

    bool isFullscreen = false;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Teto Catch");

    RenderTexture2D target = LoadRenderTexture(logWidth, logHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    SetTargetFPS(60);

    // Audio
    InitAudioDevice();
    Sound tetoSfx = LoadSound(RESOURCES_PATH "tetoo.mp3");
    Sound tetoOhNoSfx = LoadSound(RESOURCES_PATH "teto-oh-no.mp3");
    Music bgm = LoadMusicStream(RESOURCES_PATH "background-music.mp3");
    PlayMusicStream(bgm);

    // random X coord for baguette
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(100, logWidth - 300);

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
    Rectangle destRecBackground = { 0.0f, 0.0f, logWidth, logHeight };
    Vector2 origin = { 0.0f, 0.0f };

    // Player Texture
    const Texture2D playerTx = LoadTexture(RESOURCES_PATH "miniTeto.png");
    Rectangle sourceRecPlayer = { 0.0f, 0.0f, static_cast<float>(playerTx.width), static_cast<float>(playerTx.height) };
    Rectangle destRecPlayer = { static_cast<float>(playerX), static_cast<float>(playerY), 300, 300 };

    // Baguette Texture
    const Texture2D baguetteTx = LoadTexture(RESOURCES_PATH "baguette.png");
    Rectangle sourceRecBaguette = { 0.0f, 0.0f, static_cast<float>(baguetteTx.width), static_cast<float>(baguetteTx.height) };
    Rectangle destRecBaguette = { static_cast<float>(baguetteX), static_cast<float>(baguetteY), 200, 200 };

    ToggleBorderlessWindowed();

    while (!WindowShouldClose()) {

        UpdateMusicStream(bgm);

        BeginTextureMode(target);

        if (IsKeyPressed(KEY_F11)) {
            ToggleBorderlessWindowed();
            isFullscreen = !isFullscreen;
        }

        ClearBackground(BLUE);

        DrawTexturePro(backgroundTx, sourceRecBackground, destRecBackground, origin, 0.0f, WHITE);

        DrawText(("Baguettes: " + std::to_string(baguetteCount)).c_str(), 10, 10, 60,WHITE);

        #pragma region player

        DrawTexturePro(playerTx, sourceRecPlayer, destRecPlayer, origin, 0.0f, WHITE);

        // to not run offscreen
        if (playerX > logWidth - 280) {
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
            PlaySound(tetoSfx);

            if (baguetteSpeed < 5) {
                baguetteSpeed++;
            }

            baguetteX = distrib(gen);
            baguetteY = 0;
            destRecBaguette.x = static_cast<float>(baguetteX);
            destRecBaguette.y = static_cast<float>(baguetteY);

        } else if (baguetteY > logHeight - 100) {
            PlaySound(tetoOhNoSfx);
            baguetteCount = 0;
            baguetteSpeed = 1;
            baguetteX = distrib(gen);
            baguetteY = 0;
            destRecBaguette.x = static_cast<float>(baguetteX);
            destRecBaguette.y = static_cast<float>(baguetteY);
        }

        #pragma endregion

        EndTextureMode();

    #pragma region letterbox

        BeginDrawing();

        ClearBackground(BLACK);

        float scale = std::min(
            static_cast<float>(GetScreenWidth())  / logWidth,
            static_cast<float>(GetScreenHeight()) / logHeight
        );

        float scaledWidth  = logWidth  * scale;
        float scaledHeight = logHeight * scale;

        float offsetX = (static_cast<float>(GetScreenWidth())  - scaledWidth)  / 2;
        float offsetY = (static_cast<float>(GetScreenHeight()) - scaledHeight) / 2;

        Rectangle src = {
            0, 0,
            static_cast<float>(target.texture.width),
            -static_cast<float>(target.texture.height)
        };

        Rectangle dst = {
            offsetX,
            offsetY,
            scaledWidth,
            scaledHeight
        };

        DrawTexturePro(target.texture, src, dst, {0, 0}, 0, WHITE);

        EndDrawing();

    #pragma endregion
    }

    UnloadSound(tetoSfx);
    CloseAudioDevice();

    return 0;
}