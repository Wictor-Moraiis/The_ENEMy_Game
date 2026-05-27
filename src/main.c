#include "raylib.h"
#include "game.h"

int main() {
    // Inicialização da Janela e Áudio
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "The ENEMy Game - O Despertar");
    InitAudioDevice(); // Inicializa o sistema de áudio

    // Carregamento de Assets
    Texture2D logo = LoadTexture("assets/graphics/logo.png");
    Music music = LoadMusicStream("assets/audio/main_song.mp3");
    
    music.looping = true;
    PlayMusicStream(music);

    SetTargetFPS(60);

    bool gameStarted = false;

    // Loop da Tela de Início (Splash Screen)
    while (!WindowShouldClose() && !gameStarted) {
        // Atualiza o stream da música
        UpdateMusicStream(music);

        // Verifica se qualquer tecla foi pressionada
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
                DrawText("LOGO NÃO ENCONTRADA", 250, 200, 20, RED);
                DrawText("Coloque logo.png em assets/graphics/", 210, 230, 20, GRAY);
            }

            DrawText("Pressione QUALQUER TECLA para iniciar o sonho...", 180, 380, 20, LIGHTGRAY);
        EndDrawing();
    }

    // Transição para o Jogo
    if (gameStarted) {
        StopMusicStream(music);
        UnloadMusicStream(music);
        UnloadTexture(logo);
        iniciar_tutorial();
    }

    CloseAudioDevice(); // Fecha o dispositivo de áudio
    CloseWindow();

    return 0;
}

void iniciar_tutorial() {
    const char *dialogos[] = {
        "O relogio marca 3:00 da manha.",
        "Voce passou os ultimos meses estudando sem parar.",
        "Sua mente esta exausta. A prova e amanha.",
        "Seus olhos pesam...",
        "De repente, o chao desaparece sob seus pes.",
        "Voce esta flutuando em um abismo de formulas e datas.",
        "Uma voz grave ecoa de lugar nenhum:",
        "BEM-VINDO, ESTUDANTE.",
        "ESTE E O SEU SUBCONSCIENTE. O CAMPO DE BATALHA FINAL.",
        "AQUI, A CANETA NAO E SUA ARMA. SEU CONHECIMENTO E."
    };
    int totalDialogos = 10;
    int dialogoAtual = 0;
    bool continua = false;

    while (!WindowShouldClose()) {
        // Lógica de entrada
        if (IsKeyPressed(KEY_S)) {
            continua = true;
        }

        if (!continua) {
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
                dialogoAtual++;
                if (dialogoAtual >= totalDialogos) {
                    continua = true;
                }
            }
        }

        BeginDrawing();
            ClearBackground(BLACK); // Fundo sempre preto agora
            
            if (!continua) {
                // Desenha o diálogo centralizado
                int textWidth = MeasureText(dialogos[dialogoAtual], 20);
                DrawText(dialogos[dialogoAtual], GetScreenWidth()/2 - textWidth/2, GetScreenHeight()/2, 20, WHITE);
                
                // Instruções
                DrawText("Pressione [ENTER] para continuar", 250, 400, 15, GRAY);
                DrawText("Pressione [S] para pular", 600, 20, 15, DARKGRAY);
            } else {
                DrawText("O SONHO SE TORNA REALIDADE...", 250, 180, 20, GOLD);
                DrawText("CONTINUA...", 340, 220, 30, RED);
                DrawText("Aperte ESC para fechar o jogo.", 280, 400, 15, GRAY);
            }
        EndDrawing();
    }
}
