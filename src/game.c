#include "game.h"
#include "scenario.h"
#include "character.h"
#include "questions.h"
#include "raylib.h"
#include <stdio.h>

bool IniciarTutorial() {
    Scenario tutorial = CreateScenario();

    AddBackground(&tutorial, ""); 
    AddSpeak(&tutorial, CHAR_CONSCIENCIA, "O relógio marca 3:00 da manhã.");
    AddSpeak(&tutorial, CHAR_CONSCIENCIA, "Você passou os últimos meses estudando sem parar.");
    AddSpeak(&tutorial, CHAR_CONSCIENCIA, "Sua mente está exausta. A prova é amanhã.");

    const char* opts1[] = {"Fechar os olhos", "Tomar café", "Estudar mais", "Desistir"};
    AddQuestion(&tutorial, "O que você decide fazer agora?", opts1, 0, 1);

    AddSpeak(&tutorial, CHAR_VOZ_GRAVE, "BEM-VINDA, ELLIE.");
    AddSpeak(&tutorial, CHAR_VOZ_GRAVE, "ESTE É O SEU SUBCONSCIENTE. O CAMPO DE BATALHA FINAL.");

    AddBackground(&tutorial, "assets/graphics/livro_background.png"); 
    
    AddSpeak(&tutorial, CHAR_MASCARA_ARTES, "Ellie, para passar por mim, você deve entender a estética.");
    AddSpeak(&tutorial, CHAR_MASCARA_ARTES, "Selecione a opção correta para avançar.");

    const char* optsArtes[] = {"Modernismo", "Barroco", "Renascimento", "Surrealismo"};
    AddQuestion(&tutorial, "Qual movimento artístico brasileiro teve como marco a Semana de 22?", optsArtes, 0, 1);

    AddBackground(&tutorial, ""); 
    AddSpeak(&tutorial, CHAR_VOZ_GRAVE, "AQUI, A CANETA NÃO É SUA ARMA. SEU CONHECIMENTO É, ELLIE.");

    while (!WindowShouldClose()) {
        if (IsScenarioFinished(&tutorial)) break;
        BeginDrawing();
            UpdateAndDrawScenario(&tutorial);
        EndDrawing();
    }

    UnloadScenarioResources(&tutorial);
    if (WindowShouldClose()) return false;

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

    if (WindowShouldClose()) return false;
    return StartBattle(CHAR_MASCARA_ARTES, DIFICULDADE_FACIL);
}

bool IniciarNivel1() {
    Scenario lvl1 = CreateScenario();
    AddBackground(&lvl1, "assets/graphics/livro_background.png");
    AddSpeak(&lvl1, CHAR_VOZ_GRAVE, "Nível 1: O Desafio dos Números.");
    AddSpeak(&lvl1, CHAR_CONSCIENCIA, "Ellie, prepare-se. A matemática aqui não perdoa erros.");

    while (!WindowShouldClose()) {
        if (IsScenarioFinished(&lvl1)) break;
        BeginDrawing();
            UpdateAndDrawScenario(&lvl1);
        EndDrawing();
    }
    UnloadScenarioResources(&lvl1);
    
    if (WindowShouldClose()) return false;
    return StartBattle(CHAR_MATH_ENEMY, DIFICULDADE_MEDIA);
}

bool IniciarNivel2() {
    Scenario lvl2 = CreateScenario();
    AddBackground(&lvl2, "assets/graphics/livro_background.png"); 
    AddSpeak(&lvl2, CHAR_VOZ_GRAVE, "Nível 2: O Despertar da Natureza.");
    AddSpeak(&lvl2, CHAR_NATUREZA_BOSS, "Você acha que seu conhecimento é suficiente para dominar a própria vida?");

    while (!WindowShouldClose()) {
        if (IsScenarioFinished(&lvl2)) break;
        BeginDrawing();
            UpdateAndDrawScenario(&lvl2);
        EndDrawing();
    }
    UnloadScenarioResources(&lvl2);

    if (WindowShouldClose()) return false;
    return StartBattle(CHAR_NATUREZA_BOSS, DIFICULDADE_DIFICIL);
}

void ExecutarJogo(PlayerStats* player, int slot) {
    bool quit = false;

    while (!quit && !WindowShouldClose()) {
        bool levelSuccess = false;

        if (player->level == 1) {
            levelSuccess = IniciarTutorial();
        } else if (player->level == 2) {
            levelSuccess = IniciarNivel1();
        } else if (player->level == 3) {
            levelSuccess = IniciarNivel2();
        } else if (player->level >= 4) {
            break; // Fim do jogo
        }

        if (levelSuccess) {
            player->level++;
            SavePlayer(player, slot);
        } else {
            // Se falhou (Game Over ou Window Close), limpamos as questões usadas para tentar de novo
            ResetUsedQuestions();
            if (WindowShouldClose()) quit = true;
        }
    }

    // Tela de Fim de Jogo / Créditos (apenas se completou ou se ainda está aberto)
    while (!WindowShouldClose() && player->level >= 4) {
        const char* t1 = "PARABÉNS, ELLIE!";
        const char* t2 = "Você completou todos os desafios disponíveis.";
        const char* t3 = "Aperte ESC para sair.";
        
        int s1 = MeasureText(t1, 30);
        int s2 = MeasureText(t2, 20);
        int s3 = MeasureText(t3, 15);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(t1, GetScreenWidth()/2 - s1/2, GetScreenHeight()/2 - 60, 30, GOLD);
            DrawText(t2, GetScreenWidth()/2 - s2/2, GetScreenHeight()/2, 20, WHITE);
            DrawText(t3, GetScreenWidth()/2 - s3/2, GetScreenHeight()/2 + 60, 15, GRAY);
        EndDrawing();
    }
}
