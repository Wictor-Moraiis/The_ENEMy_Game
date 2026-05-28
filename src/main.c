#include "raylib.h"
#include "game.h"

int main() {
    // Inicialização da Janela e Áudio
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "The ENEMy Game - O Despertar");
    InitAudioDevice();

    // Carregamento de Assets Iniciais
    Texture2D logo = LoadTexture("assets/graphics/logo.png");
    Music music = LoadMusicStream("assets/audio/main_song.mp3");
    
    music.looping = true;
    PlayMusicStream(music);

    SetTargetFPS(60);

    bool gameStarted = false;

    // Splash Screen
    while (!WindowShouldClose() && !gameStarted) {
        UpdateMusicStream(music);

        if (GetKeyPressed() != 0) {
            gameStarted = true;
        }

        BeginDrawing();
            ClearBackground(BLACK);

            if (logo.id > 0) {
                float logoScale = 2.0f;
                Vector2 position = { 
                    (float)screenWidth/2 - (logo.width * logoScale)/2, 
                    (float)screenHeight/2 - (logo.height * logoScale)/2 
                };
                DrawTextureEx(logo, position, 0.0f, logoScale, WHITE);
            } else {
                DrawText("THE ENEMy GAME", 280, 200, 30, GOLD);
            }

            DrawText("Pressione QUALQUER TECLA para iniciar o sonho...", 180, 380, 20, LIGHTGRAY);
        EndDrawing();
    }

    if (gameStarted) {
        StopMusicStream(music);
        UnloadMusicStream(music);
        UnloadTexture(logo);
        
        // Inicia o fluxo principal do jogo
        IniciarTutorial();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
