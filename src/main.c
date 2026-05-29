#include "raylib.h"
#include "game.h"
#include "character.h"
#include "player.h"
#include <string.h>
#include <stdio.h>

typedef enum { SCREEN_SPLASH, SCREEN_SAVE_SELECT, SCREEN_NEW_GAME, SCREEN_GAME } GameScreen;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "The ENEMy Game - O Despertar");
    InitAudioDevice();
    InitCharacters();

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

    while (!WindowShouldClose()) {
        UpdateMusicStream(music);

        switch (currentScreen) {
            case SCREEN_SPLASH:
                if (GetKeyPressed() != 0) {
                    LoadAllSaves(saves);
                    currentScreen = SCREEN_SAVE_SELECT;
                }
                break;
            
            case SCREEN_SAVE_SELECT:
                for (int i = 0; i < MAX_SAVES; i++) {
                    Rectangle rect = { 200, (float)(100 + i * 60), 400, 50 };
                    if (CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
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
                IniciarTutorial();
                // Após o tutorial, voltamos ou fechamos (por enquanto fecha para simplificar)
                goto cleanup;
                break;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            
            if (currentScreen == SCREEN_SPLASH) {
                if (logo.id > 0) DrawTextureEx(logo, (Vector2){250, 100}, 0, 2.0f, WHITE);
                else DrawText("THE ENEMy GAME", 280, 200, 30, GOLD);
                DrawText("Pressione QUALQUER TECLA", 260, 380, 20, LIGHTGRAY);
            } 
            else if (currentScreen == SCREEN_SAVE_SELECT) {
                DrawText("SELECIONE SEU PERFIL", 250, 40, 25, GOLD);
                for (int i = 0; i < MAX_SAVES; i++) {
                    Rectangle rect = { 200, (float)(100 + i * 60), 400, 50 };
                    bool hover = CheckCollisionPointRec(GetMousePosition(), rect);
                    DrawRectangleRec(rect, hover ? DARKGRAY : BLACK);
                    DrawRectangleLinesEx(rect, 2, hover ? GOLD : GRAY);
                    
                    char label[64];
                    if (saves[i].active) sprintf(label, "SLOT %d: %s (Nivel %d)", i + 1, saves[i].name, saves[i].level);
                    else sprintf(label, "SLOT %d: [ NOVO JOGO ]", i + 1);
                    
                    DrawText(label, (int)rect.x + 20, (int)rect.y + 15, 20, WHITE);
                }
            }
            else if (currentScreen == SCREEN_NEW_GAME) {
                DrawText("COMO SE CHAMA, ESTUDANTE?", 200, 150, 25, GOLD);
                DrawRectangle(200, 200, 400, 50, DARKGRAY);
                DrawRectangleLines(200, 200, 400, 50, WHITE);
                DrawText(inputName, 220, 215, 20, RAYWHITE);
                DrawText("Pressione ENTER para despertar", 250, 300, 15, GRAY);
            }

        EndDrawing();
    }

cleanup:
    UnloadCharacters();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
