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

    AddBackground(&tutorial, "assets/graphics/linguagens_background.png"); 
    
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
    AddBackground(&lvl1, "assets/graphics/numeros_background.png");
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
    AddBackground(&lvl2, "assets/graphics/jungle_background.png"); 
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

bool IniciarNivel3() {
    Scenario lvl3 = CreateScenario();
    AddBackground(&lvl3, "assets/graphics/humanidades_background.png"); 
    AddSpeak(&lvl3, CHAR_VOZ_GRAVE, "Nível 3: O Desafio das Humanidades.");
    AddSpeak(&lvl3, CHAR_ENEMY_HUMANITIES, "Você está pronto para enfrentar os desafios do conhecimento humano?");

    while (!WindowShouldClose()) {
        if (IsScenarioFinished(&lvl3)) break;
        BeginDrawing();
            UpdateAndDrawScenario(&lvl3);
        EndDrawing();
    }

    UnloadScenarioResources(&lvl3);

    if (WindowShouldClose()) return false;
    return StartBattle(CHAR_ENEMY_HUMANITIES, DIFICULDADE_MEDIA);
}

void MostrarCutsceneFinal() {
    Scenario finalScene = CreateScenario();

    AddBackground(&finalScene, "");
    AddSpeak(&finalScene, CHAR_CONSCIENCIA, "O silêncio toma conta.");
    AddSpeak(&finalScene, CHAR_CONSCIENCIA, "Depois de tantos desafios, tudo parece mais leve.");
    AddSpeak(&finalScene, CHAR_ELLIE, "Será que... acabou mesmo?");

    AddBackground(&finalScene, "assets/graphics/aprovacao_background.png");
    AddSpeak(&finalScene, CHAR_VOZ_GRAVE, "Ellie...");
    AddSpeak(&finalScene, CHAR_VOZ_GRAVE, "Você enfrentou seus medos.");
    AddSpeak(&finalScene, CHAR_VOZ_GRAVE, "Você superou cada desafio.");
    AddSpeak(&finalScene, CHAR_VOZ_GRAVE, "E agora... chegou a hora de ver o resultado.");

    AddSpeak(&finalScene, CHAR_ELLIE, "Eu... consegui?");
    AddSpeak(&finalScene, CHAR_CONSCIENCIA, "Sim, Ellie.");
    AddSpeak(&finalScene, CHAR_CONSCIENCIA, "Você passou no vestibular.");
    AddBackground(&finalScene, "assets/graphics/ellieAcorda_background.png");
    AddSpeak(&finalScene, CHAR_VOZ_GRAVE, "Ellie acorda em sua cama.");
    AddSpeak(&finalScene, CHAR_VOZ_GRAVE, "Confiante mais do que nunca para encarar o seu maior desafio.");

    while (!WindowShouldClose()) {
        if (IsScenarioFinished(&finalScene)) break;
        BeginDrawing();
            UpdateAndDrawScenario(&finalScene);
        EndDrawing();
    }

    UnloadScenarioResources(&finalScene);

    if (WindowShouldClose()) return;

    while (!WindowShouldClose()) {
        const char* t1 = "APROVADA!";
        const char* t2 = "Ellie venceu o vestibular!";
        const char* t3 = "Todo esforço valeu a pena.";
        const char* t4 = "Pressione ENTER para continuar.";

        int s1 = MeasureText(t1, 50);
        int s2 = MeasureText(t2, 25);
        int s3 = MeasureText(t3, 20);
        int s4 = MeasureText(t4, 15);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(t1, GetScreenWidth()/2 - s1/2, GetScreenHeight()/2 - 80, 50, GOLD);
            DrawText(t2, GetScreenWidth()/2 - s2/2, GetScreenHeight()/2 - 20, 25, WHITE);
            DrawText(t3, GetScreenWidth()/2 - s3/2, GetScreenHeight()/2 + 20, 20, LIGHTGRAY);
            DrawText(t4, GetScreenWidth()/2 - s4/2, GetScreenHeight()/2 + 80, 15, GRAY);
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }
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
        } else if (player->level == 4) {
            levelSuccess = IniciarNivel3();
        } else if (player->level >= 5) {
            break;
        }

        if (levelSuccess) {
            player->level++;
            SavePlayer(player, slot);
        } else {
            ResetUsedQuestions();
            if (WindowShouldClose()) quit = true;
        }
    }

    if (!WindowShouldClose() && player->level >= 5) {
        MostrarCutsceneFinal();

        while (!WindowShouldClose()) {
            const char* t1 = "PARABÉNS, ELLIE!";
            const char* t2 = "Você completou todos os desafios disponíveis.";
            const char* t3 = "Obrigada por jogar.";
            const char* t4 = "Aperte ESC para sair.";

            int s1 = MeasureText(t1, 30);
            int s2 = MeasureText(t2, 20);
            int s3 = MeasureText(t3, 20);
            int s4 = MeasureText(t4, 15);

            BeginDrawing();
                ClearBackground(BLACK);
                DrawText(t1, GetScreenWidth()/2 - s1/2, GetScreenHeight()/2 - 80, 30, GOLD);
                DrawText(t2, GetScreenWidth()/2 - s2/2, GetScreenHeight()/2 - 20, 20, WHITE);
                DrawText(t3, GetScreenWidth()/2 - s3/2, GetScreenHeight()/2 + 15, 20, LIGHTGRAY);
                DrawText(t4, GetScreenWidth()/2 - s4/2, GetScreenHeight()/2 + 70, 15, GRAY);
            EndDrawing();

            if (IsKeyPressed(KEY_ESCAPE)) break;
        }
    }
}