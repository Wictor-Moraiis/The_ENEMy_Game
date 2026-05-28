#include "scenario.h"
#include <string.h>
#include <stdio.h>

Scenario CreateScenario() {
    Scenario s = {0};
    s.actionCount = 0;
    s.currentAction = 0;
    s.completed = false;
    return s;
}

void AddSpeak(Scenario* s, const char* person, const char* text) {
    if (s->actionCount >= MAX_ACTIONS) return;
    
    ScenarioAction* action = &s->actions[s->actionCount++];
    action->type = ACTION_SPEAK;
    strncpy(action->data.speak.person, person, sizeof(action->data.speak.person) - 1);
    strncpy(action->data.speak.text, text, sizeof(action->data.speak.text) - 1);
}

void AddQuestion(Scenario* s, const char* question, const char* options[MAX_OPTIONS], int correctIndex, int level) {
    if (s->actionCount >= MAX_ACTIONS) return;

    ScenarioAction* action = &s->actions[s->actionCount++];
    action->type = ACTION_QUESTION;
    strncpy(action->data.question.question, question, sizeof(action->data.question.question) - 1);
    for (int i = 0; i < MAX_OPTIONS; i++) {
        strncpy(action->data.question.options[i], options[i], sizeof(action->data.question.options[i]) - 1);
    }
    action->data.question.correctIndex = correctIndex;
    action->data.question.level = level;
}

static void DrawSpeakUI(SpeakAction* speak) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    
    // Caixa de diálogo
    DrawRectangle(50, screenHeight - 150, screenWidth - 100, 120, Fade(BLACK, 0.8f));
    DrawRectangleLines(50, screenHeight - 150, screenWidth - 100, 120, WHITE);
    
    // Nome do personagem
    DrawText(speak->person, 70, screenHeight - 140, 20, GOLD);
    
    // Texto
    DrawText(speak->text, 70, screenHeight - 100, 18, RAYWHITE);
    
    DrawText("Pressione [ENTER] para continuar", screenWidth - 250, screenHeight - 50, 12, GRAY);
}

static void DrawQuestionUI(QuestionAction* q) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    
    // Pergunta
    DrawText(q->question, 50, 100, 22, WHITE);
    
    // Nível
    char levelText[20];
    sprintf(levelText, "Nível: %d", q->level);
    DrawText(levelText, screenWidth - 100, 20, 15, RED);

    // Opções
    for (int i = 0; i < MAX_OPTIONS; i++) {
        Rectangle rect = { 50, (float)(180 + i * 50), (float)(screenWidth - 100), 40 };
        
        bool mouseOver = CheckCollisionPointRec(GetMousePosition(), rect);
        DrawRectangleRec(rect, mouseOver ? DARKGRAY : BLACK);
        DrawRectangleLinesEx(rect, 1, mouseOver ? GOLD : GRAY);
        
        char optionText[150];
        sprintf(optionText, "%d. %s", i + 1, q->options[i]);
        DrawText(optionText, (int)rect.x + 20, (int)rect.y + 10, 18, WHITE);
    }
}

void UpdateAndDrawScenario(Scenario* s) {
    if (s->completed || s->currentAction >= s->actionCount) {
        s->completed = true;
        return;
    }

    // Lógica global de Skip (Padrão da Engine)
    if (IsKeyPressed(KEY_S)) {
        s->completed = true;
        return;
    }

    ScenarioAction* current = &s->actions[s->currentAction];
    
    // Indicador visual de Skip
    DrawText("Pressione [S] para pular", GetScreenWidth() - 160, 10, 10, DARKGRAY);

    if (current->type == ACTION_SPEAK) {
        DrawSpeakUI(&current->data.speak);
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            s->currentAction++;
        }
    } else if (current->type == ACTION_QUESTION) {
        DrawQuestionUI(&current->data.question);
        
        int choice = -1;
        if (IsKeyPressed(KEY_ONE)) choice = 0;
        else if (IsKeyPressed(KEY_TWO)) choice = 1;
        else if (IsKeyPressed(KEY_THREE)) choice = 2;
        else if (IsKeyPressed(KEY_FOUR)) choice = 3;
        
        // Clique do mouse nas opções
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < MAX_OPTIONS; i++) {
                Rectangle rect = { 50, (float)(180 + i * 50), (float)(GetScreenWidth() - 100), 40 };
                if (CheckCollisionPointRec(GetMousePosition(), rect)) {
                    choice = i;
                    break;
                }
            }
        }

        if (choice != -1) {
            // Aqui poderíamos emitir um som ou processar a resposta
            // Por enquanto, apenas avançamos
            s->currentAction++;
        }
    }

    if (s->currentAction >= s->actionCount) {
        s->completed = true;
    }
}

bool IsScenarioFinished(Scenario* s) {
    return s->completed;
}
