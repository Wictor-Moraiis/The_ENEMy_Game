#include "game.h"
#include "scenario.h"
#include "character.h"
#include "raylib.h"
#include <stdio.h>

void IniciarTutorial() {
    Scenario tutorial = CreateScenario();
    
    // Usando IDs de personagens agora
    AddSpeak(&tutorial, CHAR_CONSCIENCIA, "O relogio marca 3:00 da manha.");
    AddSpeak(&tutorial, CHAR_CONSCIENCIA, "Voce passou os ultimos meses estudando sem parar.");
    AddSpeak(&tutorial, CHAR_CONSCIENCIA, "Sua mente esta exausta. A prova e amanha.");
    
    const char* opts1[] = {"Fechar os olhos", "Tomar cafe", "Estudar mais", "Desistir"};
    AddQuestion(&tutorial, "O que voce decide fazer agora?", opts1, 0, 1);
    
    AddSpeak(&tutorial, CHAR_VOZ_GRAVE, "BEM-VINDO, ESTUDANTE.");
    AddSpeak(&tutorial, CHAR_VOZ_GRAVE, "ESTE E O SEU SUBCONSCIENTE. O CAMPO DE BATALHA FINAL.");
    
    // Exemplo solicitado: Entidade das Artes
    AddSpeak(&tutorial, CHAR_MASCARA_ARTES, "Eu sou a Entidade das Artes. Para passar por mim, voce deve entender a estética.");
    const char* optsArtes[] = {"Modernismo", "Barroco", "Renascimento", "Surrealismo"};
    AddQuestion(&tutorial, "Qual movimento artístico brasileiro teve como marco a Semana de 22?", optsArtes, 0, 1);

    AddSpeak(&tutorial, CHAR_VOZ_GRAVE, "AQUI, A CANETA NAO E SUA ARMA. SEU CONHECIMENTO E.");

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
