#include "scenario.h"
#include <string.h>
#include <stdio.h>

#define TEXT_SPEED 0.03f
#define BOX_MARGIN 50
#define BOX_PADDING 20
#define FEEDBACK_DURATION 1.5f // Tempo que a resposta correta/errada fica na tela

Scenario CreateScenario() {
    Scenario s = {0};
    s.actionCount = 0;
    s.currentAction = 0;
    s.completed = false;
    s.textProgress = 0;
    s.textTimer = 0;
    s.isTextEffectDone = false;
    s.currentBg = (Texture2D){0};
    strcpy(s.currentBgPath, "");
    s.showFeedback = false;
    s.lastChoice = -1;
    s.feedbackTimer = 0;
    s.lastCharId = CHAR_NONE;
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

void AddBackground(Scenario* s, const char* imagePath) {
    if (s->actionCount >= MAX_ACTIONS) return;
    ScenarioAction* action = &s->actions[s->actionCount++];
    action->type = ACTION_BACKGROUND;
    strncpy(action->data.background.imagePath, imagePath, sizeof(action->data.background.imagePath) - 1);
}

static void DrawWrappedText(const char* text, int x, int y, int maxWidth, int fontSize, Color color, int progress) {
    int currentLine = 0;
    char buffer[1024];
    strncpy(buffer, text, progress);
    buffer[progress] = '\0';
    Font font = GetFontDefault();
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

static void DrawCharacter(CharacterID charId, bool isQuestion) {
    if (charId == CHAR_NONE) return;
    Character* character = GetCharacter(charId);
    if (!character || character->texture.id <= 0) return;

    int sw = GetScreenWidth();
    int sh = GetScreenHeight();
    float scale = (charId == CHAR_ELLIE) ? 1.0f : 4.0f;
    
    // Se for pergunta, posiciona mais à direita e sem a caixa de diálogo
    Vector2 pos;
    if (isQuestion) {
        pos = (Vector2){ (float)sw - (character->texture.width * scale) - 20, (float)sh - (character->texture.height * scale) - 20 };
    } else {
        // Altura estimada da caixa de diálogo (120-150px)
        pos = (Vector2){ (float)sw - (character->texture.width * scale) - 50, (float)sh - 120 - (character->texture.height * scale) - 20 };
    }
    
    DrawTextureEx(character->texture, pos, 0.0f, scale, WHITE);
}

static void DrawSpeakUI(Scenario* s, SpeakAction* speak) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Character* character = GetCharacter(speak->charId);
    const char* name = character ? character->name : "Desconhecido";

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

    DrawCharacter(speak->charId, false);
    
    int maxWidth = screenWidth - (BOX_MARGIN * 2) - (BOX_PADDING * 2);
    int fontSize = 20;
    int lineCount = 1 + (int)(strlen(speak->text) * 10 / maxWidth);
    int boxHeight = (lineCount * (fontSize + 5)) + (BOX_PADDING * 2) + 30;
    if (boxHeight < 120) boxHeight = 120;

    Rectangle box = { BOX_MARGIN, (float)screenHeight - boxHeight - 30, (float)screenWidth - (BOX_MARGIN * 2), (float)boxHeight };
    DrawRectangleRec(box, Fade(BLACK, 0.8f));
    DrawRectangleLinesEx(box, 1, WHITE);
    DrawText(name, (int)box.x + BOX_PADDING, (int)box.y + 10, 20, GOLD);
    DrawWrappedText(speak->text, (int)box.x + BOX_PADDING, (int)box.y + 45, maxWidth, fontSize, RAYWHITE, s->textProgress);
    if (s->isTextEffectDone) DrawText("Pressione [ENTER]", (int)box.x + (int)box.width - 130, (int)box.y + (int)box.height - 20, 12, GRAY);
}

static void DrawQuestionUI(Scenario* s, QuestionAction* q) {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    DrawCharacter(s->lastCharId, true);

    DrawText(q->question, 50, sh/4, 22, WHITE);
    char levelText[20];
    sprintf(levelText, "Nível: %d", q->level);
    DrawText(levelText, sw - 120, 20, 15, RED);

    for (int i = 0; i < MAX_OPTIONS; i++) {
        Rectangle rect = { 50, (float)(sh/4 + 80 + i * 55), (float)(sw - 100), 45 };
        bool mouseOver = CheckCollisionPointRec(GetMousePosition(), rect);
        
        Color boxColor = BLACK;
        Color outlineColor = GRAY;
        Color textColor = WHITE;

        if (s->showFeedback) {
            if (i == q->correctIndex) {
                boxColor = Fade(GREEN, 0.6f);
                outlineColor = GREEN;
                textColor = WHITE;
            } else if (i == s->lastChoice) {
                boxColor = Fade(RED, 0.6f);
                outlineColor = RED;
                textColor = WHITE;
            }
        } else if (mouseOver) {
            boxColor = DARKGRAY;
            outlineColor = GOLD;
            textColor = GOLD;
        }

        DrawRectangleRec(rect, boxColor);
        DrawRectangleLinesEx(rect, 1, outlineColor);
        
        char optionText[150];
        sprintf(optionText, "[%d] %s", i + 1, q->options[i]);
        DrawText(optionText, (int)rect.x + 20, (int)rect.y + 10, 18, textColor);
    }
}

void UpdateAndDrawScenario(Scenario* s) {
    if (s->completed || s->currentAction >= s->actionCount) {
        s->completed = true;
        return;
    }

    // Processar todas as mudanças de background sequenciais e atualizar lastCharId
    while (s->currentAction < s->actionCount) {
        ScenarioAction* current = &s->actions[s->currentAction];
        if (current->type == ACTION_BACKGROUND) {
            if (s->currentBg.id > 0) UnloadTexture(s->currentBg);
            if (strlen(current->data.background.imagePath) > 0) {
                s->currentBg = LoadTexture(current->data.background.imagePath);
                strcpy(s->currentBgPath, current->data.background.imagePath);
            } else {
                s->currentBg = (Texture2D){0};
                strcpy(s->currentBgPath, "");
            }
            s->currentAction++;
        } else {
            break;
        }
    }

    if (s->currentAction >= s->actionCount) {
        s->completed = true;
        return;
    }

    if (s->currentBg.id > 0) {
        DrawTexturePro(s->currentBg, (Rectangle){0, 0, (float)s->currentBg.width, (float)s->currentBg.height},
                       (Rectangle){0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, (Vector2){0, 0}, 0, WHITE);
    } else {
        ClearBackground(BLACK);
    }

    if (IsKeyPressed(KEY_S)) {
        s->completed = true;
        return;
    }

    ScenarioAction* current = &s->actions[s->currentAction];
    if (current->type == ACTION_SPEAK) {
        s->lastCharId = current->data.speak.charId;
        DrawSpeakUI(s, &current->data.speak);
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (!s->isTextEffectDone) {
                s->textProgress = (int)strlen(current->data.speak.text);
                s->isTextEffectDone = true;
            } else {
                s->currentAction++;
                s->textProgress = 0;
                s->textTimer = 0;
                s->isTextEffectDone = false;
            }
        }
    } else if (current->type == ACTION_QUESTION) {
        DrawQuestionUI(s, &current->data.question);
        
        if (s->showFeedback) {
            s->feedbackTimer += GetFrameTime();
            if (s->feedbackTimer >= FEEDBACK_DURATION) {
                s->showFeedback = false;
                s->feedbackTimer = 0;
                s->lastChoice = -1;
                s->currentAction++;
                s->textProgress = 0;
                s->textTimer = 0;
                s->isTextEffectDone = false;
            }
        } else {
            int choice = -1;
            if (IsKeyPressed(KEY_ONE)) choice = 0;
            else if (IsKeyPressed(KEY_TWO)) choice = 1;
            else if (IsKeyPressed(KEY_THREE)) choice = 2;
            else if (IsKeyPressed(KEY_FOUR)) choice = 3;
            
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                int sw = GetScreenWidth();
                int sh = GetScreenHeight();
                for (int i = 0; i < MAX_OPTIONS; i++) {
                    Rectangle rect = { 50, (float)(sh/4 + 80 + i * 55), (float)(sw - 100), 45 };
                    if (CheckCollisionPointRec(GetMousePosition(), rect)) {
                        choice = i;
                        break;
                    }
                }
            }

            if (choice != -1) {
                s->showFeedback = true;
                s->lastChoice = choice;
                s->feedbackTimer = 0;
            }
        }
    }

    if (s->currentAction >= s->actionCount) s->completed = true;
}

bool IsScenarioFinished(Scenario* s) {
    return s->completed;
}

void UnloadScenarioResources(Scenario* s) {
    if (s->currentBg.id > 0) {
        UnloadTexture(s->currentBg);
        s->currentBg = (Texture2D){0};
    }
}
