#include "raylib.h"
#include "game.h"
#include "character.h"
#include "player.h"
#include "questions.h"
#include <string.h>
#include <stdio.h>

typedef enum { SCREEN_SPLASH, SCREEN_SAVE_SELECT, SCREEN_NEW_GAME, SCREEN_GAME } GameScreen;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "The ENEMy Game - O Despertar");
    InitAudioDevice();
    InitCharacters();
    InitQuestionDatabase();

    Texture2D logo = LoadTexture("assets/graphics/logo.png");
    Music music = LoadMusicStream("assets/audio/main_song.mp3");
    music.looping = true;
    PlayMusicStream(music);

    SetTargetFPS(60);

    GameScreen currentScreen = SCREEN_SPLASH;
    PlayerStats saves[MAX_SAVES];
    PlayerStats currentPlayer = {0};
    int selectedSlot = -1;
    char inputName[MAX_NAME_LENGTH] = "\0";
    int letterCount = 0;
    int key = 0;
    int keySlot = -1;

    while (!WindowShouldClose()) {
        UpdateMusicStream(music);
        if (IsKeyPressed(KEY_F11)) ToggleFullscreen();

        switch (currentScreen) {
            case SCREEN_SPLASH:
                if (GetKeyPressed() != 0) {
                    LoadAllSaves(saves);
                    currentScreen = SCREEN_SAVE_SELECT;
                }
                break;
            
            case SCREEN_SAVE_SELECT:
                // Suporte ao Teclado (1-5)
                keySlot = -1;
                if (IsKeyPressed(KEY_ONE)) keySlot = 0;
                else if (IsKeyPressed(KEY_TWO)) keySlot = 1;
                else if (IsKeyPressed(KEY_THREE)) keySlot = 2;
                else if (IsKeyPressed(KEY_FOUR)) keySlot = 3;
                else if (IsKeyPressed(KEY_FIVE)) keySlot = 4;

                for (int i = 0; i < MAX_SAVES; i++) {
                    Rectangle rect = { 200, (float)(100 + i * 60), 400, 50 };
                    bool mouseClick = (CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
                    
                    if (mouseClick || keySlot == i) {
                        selectedSlot = i;
                        if (saves[i].active) {
                            currentPlayer = saves[i];
                            currentScreen = SCREEN_GAME;
                        } else {
                            currentScreen = SCREEN_NEW_GAME;
                        }
                    }
                }
                break;

            case SCREEN_NEW_GAME:
                key = GetCharPressed();
                while (key > 0) {
                    if ((key >= 32) && (key <= 125) && (letterCount < MAX_NAME_LENGTH - 1)) {
                        inputName[letterCount] = (char)key;
                        inputName[letterCount+1] = '\0';
                        letterCount++;
                    }
                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    letterCount--;
                    if (letterCount < 0) letterCount = 0;
                    inputName[letterCount] = '\0';
                }
                if (IsKeyPressed(KEY_ENTER) && letterCount > 0) {
                    CreateNewPlayer(&currentPlayer, inputName);
                    SavePlayer(&currentPlayer, selectedSlot);
                    currentScreen = SCREEN_GAME;
                }
                break;

            case SCREEN_GAME:
                StopMusicStream(music);
                UnloadMusicStream(music);
                UnloadTexture(logo);
                ExecutarJogo(&currentPlayer, selectedSlot);
                // Após o jogo, voltamos ou fechamos
                goto cleanup;
                break;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            
            int sw = GetScreenWidth();
            int sh = GetScreenHeight();

            if (currentScreen == SCREEN_SPLASH) {
                if (logo.id > 0) {
                    float scale = 2.0f;
                    DrawTextureEx(logo, (Vector2){(float)sw/2 - (logo.width * scale)/2, (float)sh/2 - 100}, 0, scale, WHITE);
                } else {
                    const char* title = "THE ENEMy GAME";
                    DrawText(title, sw/2 - MeasureText(title, 30)/2, sh/2 - 20, 30, GOLD);
                }
                const char* msg = "Pressione QUALQUER TECLA";
                DrawText(msg, sw/2 - MeasureText(msg, 20)/2, sh - 70, 20, LIGHTGRAY);
            } 
            else if (currentScreen == SCREEN_SAVE_SELECT) {
                const char* title = "SELECIONE SEU PERFIL";
                DrawText(title, sw/2 - MeasureText(title, 25)/2, 40, 25, GOLD);
                for (int i = 0; i < MAX_SAVES; i++) {
                    Rectangle rect = { (float)sw/2 - 200, (float)(100 + i * 60), 400, 50 };
                    bool hover = CheckCollisionPointRec(GetMousePosition(), rect);
                    DrawRectangleRec(rect, hover ? DARKGRAY : BLACK);
                    DrawRectangleLinesEx(rect, 2, hover ? GOLD : GRAY);
                    
                    char label[64];
                    if (saves[i].active) sprintf(label, "SLOT %d: %s (Nível %d)", i + 1, saves[i].name, saves[i].level);
                    else sprintf(label, "SLOT %d: [ NOVO JOGO ]", i + 1);
                    
                    DrawText(label, (int)rect.x + 20, (int)rect.y + 15, 20, WHITE);
                }
            }
            else if (currentScreen == SCREEN_NEW_GAME) {
                const char* title = "COMO SE CHAMA, ELLIE?";
                DrawText(title, sw/2 - MeasureText(title, 25)/2, sh/2 - 70, 25, GOLD);
                DrawRectangle(sw/2 - 200, sh/2 - 20, 400, 50, DARKGRAY);
                DrawRectangleLines(sw/2 - 200, sh/2 - 20, 400, 50, WHITE);
                DrawText(inputName, sw/2 - 180, sh/2 - 5, 20, RAYWHITE);
                const char* msg = "Pressione ENTER para despertar";
                DrawText(msg, sw/2 - MeasureText(msg, 15)/2, sh/2 + 80, 15, GRAY);
            }

        EndDrawing();
    }

cleanup:
    UnloadCharacters();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
