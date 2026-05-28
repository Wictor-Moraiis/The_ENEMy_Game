#include "game.h"
#include "scenario.h"
#include "raylib.h"
#include <stdio.h>

void IniciarTutorial() {
    Scenario tutorial = CreateScenario();
    
    AddSpeak(&tutorial, "Consciencia", "O relogio marca 3:00 da manha.");
    AddSpeak(&tutorial, "Consciencia", "Voce passou os ultimos meses estudando sem parar.");
    AddSpeak(&tutorial, "Consciencia", "Sua mente esta exausta. A prova e amanha.");
    
    const char* opts1[] = {"Fechar os olhos", "Tomar cafe", "Estudar mais", "Desistir"};
    AddQuestion(&tutorial, "O que voce decide fazer agora?", opts1, 0, 1);
    
    AddSpeak(&tutorial, "Voz Grave", "BEM-VINDO, ESTUDANTE.");
    AddSpeak(&tutorial, "Voz Grave", "ESTE E O SEU SUBCONSCIENTE. O CAMPO DE BATALHA FINAL.");
    
    const char* opts2[] = {"Brasilia", "Sao Paulo", "Rio de Janeiro", "Salvador"};
    AddQuestion(&tutorial, "Para provar seu valor, qual a capital do Brasil?", opts2, 0, 1);

    AddSpeak(&tutorial, "Voz Grave", "AQUI, A CANETA NAO E SUA ARMA. SEU CONHECIMENTO E.");

    while (!WindowShouldClose()) {
        if (IsScenarioFinished(&tutorial)) break;

        BeginDrawing();
            ClearBackground(BLACK);
            UpdateAndDrawScenario(&tutorial);
        EndDrawing();
    }

    // Transição pós-tutorial
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("O SONHO SE TORNA REALIDADE...", 250, 180, 20, GOLD);
            DrawText("CONTINUA...", 340, 220, 30, RED);
            DrawText("Aperte ESC para fechar o jogo.", 280, 400, 15, GRAY);
        EndDrawing();
    }
}
