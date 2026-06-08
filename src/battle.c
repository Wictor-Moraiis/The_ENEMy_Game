#include "battle.h"
#include "questions.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define FEEDBACK_DURATION 1.5f

static void LoadBattleQuestionsInternal(BattleState* b, Dificuldade diff) {
    int subject = 1; // Default Artes
    if (b->enemyId == CHAR_MATH_ENEMY) subject = 4; // Matemática
    else if (b->enemyId == CHAR_NATUREZA_BOSS) subject = 3; // Natureza
    else if (b->enemyId == CHAR_MASCARA_ARTES) subject = 1; // Artes/Linguagens
    else if (b->enemyId == CHAR_VOZ_GRAVE) subject = 2; // Humanas (Exemplo)

    int targetLevel = 1;
    if (diff == DIFICULDADE_MEDIA) targetLevel = 2;
    if (diff == DIFICULDADE_DIFICIL) targetLevel = 3;

    b->questionCount = GetRandomQuestions(b->questions, 3, targetLevel, subject);

    if (b->questionCount < 3) {
        int extra = GetRandomQuestions(&b->questions[b->questionCount], 3 - b->questionCount, 1, subject);
        b->questionCount += extra;
    }
}

void InitBattleState(BattleState* b, CharacterID enemyId, Dificuldade diff) {
    memset(b, 0, sizeof(BattleState));
    b->enemyId = enemyId;
    b->enemyHP = 200;
    b->maxEnemyHP = 200;
    b->ellieHP = 3;
    b->maxEllieHP = 3;
    b->finished = false;
    b->won = false;
    b->currentQuestion = 0;
    b->showFeedback = false;
    LoadBattleQuestionsInternal(b, diff);
}

void UpdateBattleLogic(BattleState* b, int choice, float delta) {
    if (b->finished) return;

    if (b->enemyHP <= 0) {
        b->won = true;
        b->finished = true;
        return;
    }

    if (b->ellieHP <= 0) {
        b->won = false;
        b->finished = true;
        return;
    }

    if (b->showFeedback) {
        b->feedbackTimer += delta;
        if (b->feedbackTimer >= FEEDBACK_DURATION) {
            b->showFeedback = false;
            b->feedbackTimer = 0;
            
            if (b->correctHit) {
                b->enemyHP -= 40;
            } else {
                b->ellieHP--;
                b->ellieFlashTimer = 0.5f;
            }
            
            b->currentQuestion++;
            if (b->currentQuestion >= b->questionCount && b->enemyHP > 0) {
                // Em caso real de engine, recarregaria ou daria erro. 
                // Para testes, vamos apenas resetar o índice.
                b->currentQuestion = 0; 
            }
        }
    } else if (choice != -1) {
        b->showFeedback = true;
        b->lastChoice = choice;
        b->correctHit = (choice == b->questions[b->currentQuestion].correctIndex);
        if (b->correctHit) b->damageFlashTimer = 0.5f;
    }

    if (b->damageFlashTimer > 0) b->damageFlashTimer -= delta;
    if (b->ellieFlashTimer > 0) b->ellieFlashTimer -= delta;
}

static void DrawWrappedText(const char* text, int x, int y, int maxWidth, int fontSize, Color color) {
    int currentLine = 0;
    Font font = GetFontDefault();
    char temp[1024];
    int lineStart = 0;
    int i = 0;
    int len = (int)strlen(text);

    while (i <= len) {
        int wordEnd = i;
        while (text[wordEnd] != '\0' && text[wordEnd] != ' ') wordEnd++;
        
        int nextLen = wordEnd - lineStart;
        if (nextLen >= 1024) nextLen = 1023;
        strncpy(temp, text + lineStart, nextLen);
        temp[nextLen] = '\0';

        if (MeasureTextEx(font, temp, (float)fontSize, 1.0f).x > maxWidth) {
            int lineLen = i - lineStart;
            if (lineLen > 0) {
                strncpy(temp, text + lineStart, lineLen);
                temp[lineLen] = '\0';
                DrawText(temp, x, y + (currentLine * (fontSize + 5)), fontSize, color);
                currentLine++;
                lineStart = i;
            }
        }

        if (text[wordEnd] == '\0') {
            DrawText(text + lineStart, x, y + (currentLine * (fontSize + 5)), fontSize, color);
            break;
        }
        i = wordEnd + 1;
    }
}

static void DrawHPBar(int x, int y, int width, int height, int current, int max, const char* label) {
    float percent = (float)current / max;
    if (percent < 0) percent = 0;
    
    DrawRectangle(x, y, width, height, BLACK);
    DrawRectangle(x, y, (int)(width * percent), height, percent > 0.3f ? GREEN : RED);
    DrawRectangleLines(x, y, width, height, WHITE);
    DrawText(label, x, y - 20, 15, WHITE);
    
    char hpText[32];
    sprintf(hpText, "%d/%d", current, max);
    DrawText(hpText, x + width - MeasureText(hpText, 15), y + height + 5, 15, WHITE);
}

bool StartBattle(CharacterID enemyId, Dificuldade diff) {
    BattleState b;
    InitBattleState(&b, enemyId, diff);
    
    Character* enemy = GetCharacter(enemyId);
    Character* ellie = GetCharacter(CHAR_ELLIE);
    Texture2D bg = LoadTexture("assets/graphics/livro_background.png");

    while (!WindowShouldClose() && !b.finished) {
        float delta = GetFrameTime();
        int choice = -1;

        if (!b.showFeedback) {
            if (IsKeyPressed(KEY_ONE)) choice = 0;
            else if (IsKeyPressed(KEY_TWO)) choice = 1;
            else if (IsKeyPressed(KEY_THREE)) choice = 2;
            else if (IsKeyPressed(KEY_FOUR)) choice = 3;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                int sw = GetScreenWidth();
                int sh = GetScreenHeight();
                QuestionAction* q = &b.questions[b.currentQuestion];
                int boxWidth = 400;
                int padding = 20;
                int charsPerLine = (boxWidth - padding * 2) / 10;
                int lines = 1 + (int)(strlen(q->question) / charsPerLine);
                int questionHeight = lines * 25;
                int optionsHeight = 4 * 45;
                int boxHeight = questionHeight + optionsHeight + padding * 2;
                int boxY = sh/2 - boxHeight/2;

                for (int i = 0; i < MAX_OPTIONS; i++) {
                    Rectangle rect = { (float)sw - boxWidth, (float)(boxY + questionHeight + padding + i * 45), 350, 35 };
                    if (CheckCollisionPointRec(GetMousePosition(), rect)) {
                        choice = i;
                        break;
                    }
                }
            }
        }

        UpdateBattleLogic(&b, choice, delta);

        // --- Draw ---
        int sw = GetScreenWidth();
        int sh = GetScreenHeight();

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(bg, (Rectangle){0, 0, (float)bg.width, (float)bg.height},
                          (Rectangle){0, 0, (float)sw, (float)sh}, (Vector2){0, 0}, 0, Fade(WHITE, 0.5f));

            if (enemy && enemy->texture.id > 0) {
                float enemyScale = 3.0f;
                float offsetX = (b.damageFlashTimer > 0) ? (float)sin(GetTime() * 40) * 10 : 0;
                Vector2 enemyPos = { (float)sw - (enemy->texture.width * enemyScale) - 100 + offsetX, 50 };
                Color tint = (b.damageFlashTimer > 0) ? RED : WHITE;
                DrawTextureEx(enemy->texture, enemyPos, 0, enemyScale, tint);
                DrawHPBar((int)enemyPos.x, 40, 200, 15, b.enemyHP, b.maxEnemyHP, enemy->name);
            }

            if (ellie && ellie->texture.id > 0) {
                float ellieScale = 1.0f; 
                float offsetX = (b.ellieFlashTimer > 0) ? (float)sin(GetTime() * 40) * 5 : 0;
                Vector2 elliePos = { 50 + offsetX, (float)sh - (ellie->texture.height * ellieScale) - 100 };
                Color tint = (b.ellieFlashTimer > 0) ? RED : WHITE;
                DrawTextureEx(ellie->texture, elliePos, 0, ellieScale, tint);
                DrawHPBar(100, sh - 60, 200, 15, b.ellieHP, b.maxEllieHP, "Ellie (Vidas)");
            }

            QuestionAction* q = &b.questions[b.currentQuestion];
            int fontSize = 20;
            int boxWidth = 400;
            int padding = 20;
            int charsPerLine = (boxWidth - padding * 2) / 10;
            int lines = 1 + (int)(strlen(q->question) / charsPerLine);
            int questionHeight = lines * 25;
            int optionsHeight = 4 * 45;
            int boxHeight = questionHeight + optionsHeight + padding * 2;
            int boxY = sh/2 - boxHeight/2;

            DrawRectangle(sw - boxWidth - 20, boxY, boxWidth, boxHeight, Fade(BLACK, 0.8f));
            DrawRectangleLines(sw - boxWidth - 20, boxY, boxWidth, boxHeight, WHITE);
            DrawWrappedText(q->question, sw - boxWidth, boxY + padding, boxWidth - padding * 2, fontSize, GOLD);

            for (int i = 0; i < 4; i++) {
                Rectangle rect = { (float)sw - boxWidth, (float)(boxY + questionHeight + padding + i * 45), 350, 35 };
                Color boxColor = BLACK;
                Color textColor = WHITE;
                if (b.showFeedback) {
                    if (i == q->correctIndex) boxColor = GREEN;
                    else if (i == b.lastChoice) boxColor = RED;
                } else if (CheckCollisionPointRec(GetMousePosition(), rect)) {
                    boxColor = DARKGRAY;
                }
                DrawRectangleRec(rect, boxColor);
                DrawRectangleLinesEx(rect, 1, GRAY);
                char optionText[150];
                sprintf(optionText, "[%d] %s", i + 1, q->options[i]);
                DrawText(optionText, (int)rect.x + 10, (int)rect.y + 10, 15, textColor);
            }
        EndDrawing();
    }

    if (b.won) {
        float winTimer = 0;
        const char* t1 = "VITÓRIA!";
        const char* t2 = "VOCÊ SUPEROU O DESAFIO!";
        const char* t3 = TextFormat("Inimigo %s derrotado.", enemy->name);
        int s1 = MeasureText(t1, 50);
        int s2 = MeasureText(t2, 20);
        int s3 = MeasureText(t3, 15);
        while (winTimer < 3.0f && !WindowShouldClose()) {
            winTimer += GetFrameTime();
            BeginDrawing();
                ClearBackground(BLACK);
                DrawText(t1, GetScreenWidth()/2 - s1/2, GetScreenHeight()/2 - 60, 50, GOLD);
                DrawText(t2, GetScreenWidth()/2 - s2/2, GetScreenHeight()/2 + 10, 20, WHITE);
                DrawText(t3, GetScreenWidth()/2 - s3/2, GetScreenHeight()/2 + 40, 15, GRAY);
            EndDrawing();
        }
    } else if (b.finished && !b.won) {
        float loseTimer = 0;
        const char* t1 = "GAME OVER";
        const char* t2 = "A PRESSÃO FOI DEMAIS...";
        int s1 = MeasureText(t1, 50);
        int s2 = MeasureText(t2, 20);
        while (loseTimer < 3.0f && !WindowShouldClose()) {
            loseTimer += GetFrameTime();
            BeginDrawing();
                ClearBackground(BLACK);
                DrawText(t1, GetScreenWidth()/2 - s1/2, GetScreenHeight()/2 - 40, 50, RED);
                DrawText(t2, GetScreenWidth()/2 - s2/2, GetScreenHeight()/2 + 20, 20, RAYWHITE);
            EndDrawing();
        }
    }

    UnloadTexture(bg);
    return b.won;
}
