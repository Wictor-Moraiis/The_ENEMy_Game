#include "scenario.h"
#include <string.h>
#include <stdio.h>

#define TEXT_SPEED 0.03f // Velocidade do efeito (segundos por letra)
#define BOX_MARGIN 50
#define BOX_PADDING 20

Scenario CreateScenario() {
    Scenario s = {0};
    s.actionCount = 0;
    s.currentAction = 0;
    s.completed = false;
    s.textProgress = 0;
    s.textTimer = 0;
    s.isTextEffectDone = false;
    return s;
}

void AddSpeak(Scenario* s, CharacterID charId, const char* text) {
    if (s->actionCount >= MAX_ACTIONS) return;
    ScenarioAction* action = &s->actions[s->actionCount++];
    action->type = ACTION_SPEAK;
    action->data.speak.charId = charId;
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

// Função auxiliar para quebrar texto e desenhar dinamicamente
static void DrawWrappedText(const char* text, int x, int y, int maxWidth, int fontSize, Color color, int progress) {
    int currentLine = 0;
    int charCount = 0;
    char buffer[1024];
    strncpy(buffer, text, progress);
    buffer[progress] = '\0';

    // Usando uma fonte padrão para medição (ou a fonte da Raylib)
    Font font = GetFontDefault();
    Vector2 textSize = MeasureTextEx(font, buffer, (float)fontSize, 1.0f);
    
    // Simples wrapping por palavras
    char temp[1024];
    int lineStart = 0;
    int i = 0;

    while (buffer[i] != '\0') {
        int wordEnd = i;
        while (buffer[wordEnd] != '\0' && buffer[wordEnd] != ' ') wordEnd++;
        
        int nextLen = wordEnd - lineStart;
        strncpy(temp, buffer + lineStart, nextLen);
        temp[nextLen] = '\0';
        
        if (MeasureTextEx(font, temp, (float)fontSize, 1.0f).x > maxWidth) {
            // Desenha a linha atual até o último espaço
            int lineLen = i - lineStart;
            strncpy(temp, buffer + lineStart, lineLen);
            temp[lineLen] = '\0';
            DrawText(temp, x, y + (currentLine * (fontSize + 5)), fontSize, color);
            
            currentLine++;
            lineStart = i;
        }
        
        if (buffer[wordEnd] == '\0') {
            DrawText(buffer + lineStart, x, y + (currentLine * (fontSize + 5)), fontSize, color);
            break;
        }
        i = wordEnd + 1;
    }
}

static void DrawSpeakUI(Scenario* s, SpeakAction* speak) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    
    Character* character = GetCharacter(speak->charId);
    const char* name = character ? character->name : "Desconhecido";

    // Texto progressivo
    if (!s->isTextEffectDone) {
        s->textTimer += GetFrameTime();
        if (s->textTimer >= TEXT_SPEED) {
            s->textTimer = 0;
            s->textProgress++;
            if (s->textProgress >= (int)strlen(speak->text)) {
                s->textProgress = (int)strlen(speak->text);
                s->isTextEffectDone = true;
            }
        }
    }

    // Desenha imagem do personagem à direita
    if (character && character->texture.id > 0) {
        float scale = 4.0f; // Escala aumentada (Dobro da anterior)
        
        // Cálculo da altura da caixa para posicionar o personagem logo acima ou encostado nela
        int maxWidth = screenWidth - (BOX_MARGIN * 2) - (BOX_PADDING * 2);
        int fontSize = 20;
        int lineCount = 1 + (int)(strlen(speak->text) * 10 / maxWidth);
        int boxHeight = (lineCount * (fontSize + 5)) + (BOX_PADDING * 2) + 30;
        if (boxHeight < 120) boxHeight = 120;

        Vector2 pos = { 
            (float)screenWidth - (character->texture.width * scale) - 50, 
            (float)screenHeight - (character->texture.height * scale) - (screenHeight - (screenHeight - boxHeight - 30)) + 10
        };
        
        // Simplificando o cálculo da posição Y para garantir que o personagem "pouse" na caixa
        pos.y = (float)screenHeight - boxHeight - (character->texture.height * scale) - 20;

        DrawTextureEx(character->texture, pos, 0.0f, scale, WHITE);
    }
    
    // Cálculo Dinâmico da Caixa (Cresce com o progresso do texto, ou fixa no tamanho final)
    // Para simplificar e evitar jitter, calculamos o tamanho que o texto completo ocuparia
    int maxWidth = screenWidth - (BOX_MARGIN * 2) - (BOX_PADDING * 2);
    int fontSize = 20;
    
    // Estimativa simples de altura baseada na quebra de linha
    int lineCount = 1 + (int)(strlen(speak->text) * 10 / maxWidth); // Heurística
    int boxHeight = (lineCount * (fontSize + 5)) + (BOX_PADDING * 2) + 30;
    if (boxHeight < 120) boxHeight = 120; // Altura mínima

    // Caixa de diálogo
    Rectangle box = { BOX_MARGIN, (float)screenHeight - boxHeight - 30, (float)screenWidth - (BOX_MARGIN * 2), (float)boxHeight };
    DrawRectangleRec(box, Fade(BLACK, 0.8f));
    DrawRectangleLinesEx(box, 1, WHITE);
    
    // Nome do personagem
    DrawText(name, (int)box.x + BOX_PADDING, (int)box.y + 10, 20, GOLD);
    
    // Texto com Wrap e Progresso
    DrawWrappedText(speak->text, (int)box.x + BOX_PADDING, (int)box.y + 45, maxWidth, fontSize, RAYWHITE, s->textProgress);
    
    if (s->isTextEffectDone) {
        DrawText("Pressione [ENTER]", (int)box.x + (int)box.width - 130, (int)box.y + (int)box.height - 20, 12, GRAY);
    }
}

static void DrawQuestionUI(QuestionAction* q) {
    int screenWidth = GetScreenWidth();
    DrawText(q->question, 50, 100, 22, WHITE);
    char levelText[20];
    sprintf(levelText, "Nível: %d", q->level);
    DrawText(levelText, screenWidth - 100, 20, 15, RED);

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

    if (IsKeyPressed(KEY_S)) {
        s->completed = true;
        return;
    }

    ScenarioAction* current = &s->actions[s->currentAction];
    DrawText("Pressione [S] para pular", GetScreenWidth() - 160, 10, 10, DARKGRAY);

    if (current->type == ACTION_SPEAK) {
        DrawSpeakUI(s, &current->data.speak);
        
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (!s->isTextEffectDone) {
                // Se clicar durante o efeito, completa o texto instantaneamente
                s->textProgress = (int)strlen(current->data.speak.text);
                s->isTextEffectDone = true;
            } else {
                // Próxima ação
                s->currentAction++;
                s->textProgress = 0;
                s->textTimer = 0;
                s->isTextEffectDone = false;
            }
        }
    } else if (current->type == ACTION_QUESTION) {
        DrawQuestionUI(&current->data.question);
        int choice = -1;
        if (IsKeyPressed(KEY_ONE)) choice = 0;
        else if (IsKeyPressed(KEY_TWO)) choice = 1;
        else if (IsKeyPressed(KEY_THREE)) choice = 2;
        else if (IsKeyPressed(KEY_FOUR)) choice = 3;
        
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
            s->currentAction++;
            s->textProgress = 0;
            s->textTimer = 0;
            s->isTextEffectDone = false;
        }
    }

    if (s->currentAction >= s->actionCount) s->completed = true;
}

bool IsScenarioFinished(Scenario* s) {
    return s->completed;
}
