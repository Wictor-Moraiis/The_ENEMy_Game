#include "game.h"
#include "scenario.h"
#include "character.h"
#include "raylib.h"
#include <stdio.h>

void IniciarTutorial() {
    Scenario tutorial = CreateScenario();

    // Inicia com tela preta explícita
    AddBackground(&tutorial, ""); 

    AddSpeak(&tutorial, CHAR_CONSCIENCIA, "O relógio marca 3:00 da manhã.");
    AddSpeak(&tutorial, CHAR_CONSCIENCIA, "Você passou os últimos meses estudando sem parar.");
    AddSpeak(&tutorial, CHAR_CONSCIENCIA, "Sua mente está exausta. A prova é amanhã.");

    const char* opts1[] = {"Fechar os olhos", "Tomar café", "Estudar mais", "Desistir"};
    AddQuestion(&tutorial, "O que você decide fazer agora? (Utilize números ou clique para selecionar)", opts1, 0, 1);

    AddSpeak(&tutorial, CHAR_VOZ_GRAVE, "BEM-VINDA, ELLIE.");
    AddSpeak(&tutorial, CHAR_VOZ_GRAVE, "ESTE É O SEU SUBCONSCIENTE. O CAMPO DE BATALHA FINAL.");

    AddBackground(&tutorial, "assets/graphics/livro_background.png"); 
    
    AddSpeak(&tutorial, CHAR_MASCARA_ARTES, "Ellie, para passar por mim, você deve entender a estética.");
    AddSpeak(&tutorial, CHAR_MASCARA_ARTES, "Selecione a opção correta para avançar.");

    AddBackground(&tutorial, ""); // Volta para tela preta
    AddSpeak(&tutorial, CHAR_VOZ_GRAVE, "AQUI, A CANETA NÃO É SUA ARMA. SEU CONHECIMENTO É, ELLIE.");

    while (!WindowShouldClose()) {
        if (IsScenarioFinished(&tutorial)) break;

        BeginDrawing();
            UpdateAndDrawScenario(&tutorial);
        EndDrawing();
    }

    UnloadScenarioResources(&tutorial);

    // Transição para a primeira batalha
    while (!WindowShouldClose()) {
        const char* t1 = "O PRIMEIRO DESAFIO APARECE...";
        const char* t2 = "Aperte ENTER para lutar!";
        int s1 = MeasureText(t1, 20);
        int s2 = MeasureText(t2, 15);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(t1, GetScreenWidth()/2 - s1/2, GetScreenHeight()/2 - 40, 20, GOLD);
            DrawText(t2, GetScreenWidth()/2 - s2/2, GetScreenHeight()/2 + 10, 15, WHITE);
        EndDrawing();
        if (IsKeyPressed(KEY_ENTER)) break;
    }
}

void IniciarNivel1() {
    Scenario lvl1 = CreateScenario();
    AddBackground(&lvl1, "assets/graphics/livro_background.png");
    AddSpeak(&lvl1, CHAR_VOZ_GRAVE, "Nível 1: Linguagens e Ciências Humanas.");
    AddSpeak(&lvl1, CHAR_MASCARA_ARTES, "Vamos ver se você realmente aprendeu sobre o Modernismo, Ellie.");

    StartBattle(CHAR_MASCARA_ARTES, DIFICULDADE_FACIL);
    while (!WindowShouldClose()) {
        if (IsScenarioFinished(&lvl1)) break;
        BeginDrawing();
            UpdateAndDrawScenario(&lvl1);
        EndDrawing();
    }
    UnloadScenarioResources(&lvl1);
}

void IniciarNivel2() {
    Scenario lvl2 = CreateScenario();
    AddBackground(&lvl2, "");
    AddSpeak(&lvl2, CHAR_VOZ_GRAVE, "Nível 2: Parabéns, você conseguir avançar");
    AddSpeak(&lvl2, CHAR_VOZ_GRAVE, "Sinto uma presença forte vindo da floresta...");

    while (!WindowShouldClose()) {
        if (IsScenarioFinished(&lvl2)) break;
        BeginDrawing();
            UpdateAndDrawScenario(&lvl2);
        EndDrawing();
    }
    UnloadScenarioResources(&lvl2);
    StartBattle(CHAR_NATUREZA_BOSS, DIFICULDADE_MEDIA);
}

void ExecutarJogo(PlayerStats* player, int slot) {
    if (player->level == 1) {
        IniciarTutorial();
        player->level = 2;
        SavePlayer(player, slot);
    }
    
    if (player->level == 2) {
        IniciarNivel1();
        player->level = 3;
        SavePlayer(player, slot);
    }

    if (player->level == 3) {
        IniciarNivel2();
        player->level = 4; // Fim da demo
        SavePlayer(player, slot);
    }

    // Tela de Fim de Jogo / Créditos
    while (!WindowShouldClose()) {
        const char* t1 = "PARABÉNS, ELLIE!";
        const char* t2 = "Você completou todos os desafios disponíveis.";
        const char* t3 = "Aperte ESC para sair.";
        
        int s1 = MeasureText(t1, 30);
        int s2 = MeasureText(t2, 20);
        int s3 = MeasureText(t3, 15);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(t1, GetScreenWidth()/2 - s1/2, GetScreenHeight()/2 - 60, 30, GOLD);
            if (player->level >= 4) {
                DrawText(t2, GetScreenWidth()/2 - s2/2, GetScreenHeight()/2, 20, WHITE);
            }
            DrawText(t3, GetScreenWidth()/2 - s3/2, GetScreenHeight()/2 + 60, 15, GRAY);
        EndDrawing();
    }
}
