#include "battle.h"
#include "questions.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_BATTLE_QUESTIONS 5
#define FEEDBACK_DURATION 1.5f

typedef struct {
    CharacterID enemyId;
    int enemyHP;
    int maxEnemyHP;
    bool finished;
    bool won;
    int currentQuestion;
    QuestionAction questions[MAX_BATTLE_QUESTIONS];
    int questionCount;
    
    bool showFeedback;
    int lastChoice;
    float feedbackTimer;
    bool correctHit;
    float damageFlashTimer; // Timer para o filtro vermelho
} BattleState;

static void LoadBattleQuestions(BattleState* b, Dificuldade diff) {
    int subject = 1; // Default Artes
    if (b->enemyId == CHAR_MATH_ENEMY) subject = 1; // Artes/Linguagens
    else if (b->enemyId == CHAR_NATUREZA_BOSS) subject = 3; // Natureza

    // Nível da questão: se diff for DIFICIL, tenta pegar questões nível 3, etc.
    int targetLevel = 1;
    if (diff == DIFICULDADE_MEDIA) targetLevel = 2;
    if (diff == DIFICULDADE_DIFICIL) targetLevel = 3;

    // Pega 3 questões do nível atual
    b->questionCount = GetRandomQuestions(b->questions, 3, targetLevel, subject);

    // Se não tiver o suficiente no nível alvo, tenta outros níveis para completar
    if (b->questionCount < 3) {
        int extra = GetRandomQuestions(&b->questions[b->questionCount], 3 - b->questionCount, 1, subject);
        b->questionCount += extra;
    }
}

static int CalculateDamage(int level) {
    if (level == 1) return 50;  // 4 acertos
    if (level == 2) return 100; // 2 acertos
    if (level == 3) return 200; // 1 acerto (Boss)
    return 40;
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

void StartBattle(CharacterID enemyId, Dificuldade diff) {
    BattleState b = {0};
    b.enemyId = enemyId;
    b.enemyHP = 200;
    b.maxEnemyHP = 200;
    b.finished = false;
    b.won = false;
    b.currentQuestion = 0;
    b.showFeedback = false;
    
    LoadBattleQuestions(&b, diff);
    
    Character* enemy = GetCharacter(enemyId);
    Character* ellie = GetCharacter(CHAR_ELLIE);
    Texture2D bg = LoadTexture("assets/graphics/livro_background.png");

    while (!WindowShouldClose() && !b.finished) {
        // --- Update ---
        if (b.enemyHP <= 0) {
            b.won = true;
            b.finished = true;
            break;
        }

        if (b.showFeedback) {
            b.feedbackTimer += GetFrameTime();
            if (b.feedbackTimer >= FEEDBACK_DURATION) {
                b.showFeedback = false;
                b.feedbackTimer = 0;
                
                if (b.correctHit) {
                    int damage = CalculateDamage(b.questions[b.currentQuestion].level);
                    b.enemyHP -= damage;
                }
                
                b.currentQuestion++;
                if (b.currentQuestion >= b.questionCount && b.enemyHP > 0) {
                    // Loop questions if needed or fail battle
                    b.currentQuestion = 0; 
                }
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
                    Rectangle rect = { (float)sw - 400, (float)(sh/2 + 20 + i * 45), 350, 35 };
                    if (CheckCollisionPointRec(GetMousePosition(), rect)) {
                        choice = i;
                        break;
                    }
                }
            }

            if (choice != -1) {
                b.showFeedback = true;
                b.lastChoice = choice;
                b.correctHit = (choice == b.questions[b.currentQuestion].correctIndex);
                if (b.correctHit) b.damageFlashTimer = 0.5f; // Meio segundo de flash vermelho
            }
        }

        if (b.damageFlashTimer > 0) b.damageFlashTimer -= GetFrameTime();

        // --- Draw ---
        int sw = GetScreenWidth();
        int sh = GetScreenHeight();

        BeginDrawing();
            ClearBackground(BLACK);
            
            // Fundo
            DrawTexturePro(bg, (Rectangle){0, 0, (float)bg.width, (float)bg.height},
                          (Rectangle){0, 0, (float)sw, (float)sh}, (Vector2){0, 0}, 0, Fade(WHITE, 0.5f));

            // Enemy (Segundo Plano - Topo Direito)
            if (enemy && enemy->texture.id > 0) {
                float enemyScale = 3.0f;
                float offsetX = (b.damageFlashTimer > 0) ? (float)sin(GetTime() * 40) * 10 : 0;
                Vector2 enemyPos = { (float)sw - (enemy->texture.width * enemyScale) - 100 + offsetX, 50 };
                
                Color tint = (b.damageFlashTimer > 0) ? RED : WHITE;
                DrawTextureEx(enemy->texture, enemyPos, 0, enemyScale, tint);
                
                DrawHPBar((int)enemyPos.x, 40, 200, 15, b.enemyHP, b.maxEnemyHP, enemy->name);
            }

            // Ellie (Primeiro Plano - Baixo Esquerda)
            if (ellie && ellie->texture.id > 0) {
                float ellieScale = 1.0f; 
                Vector2 elliePos = { 50, (float)sh - (ellie->texture.height * ellieScale) - 100 };
                DrawTextureEx(ellie->texture, elliePos, 0, ellieScale, WHITE);
                DrawHPBar(100, sh - 60, 200, 15, 3, 3, "Ellie (Vidas)");
            }

            // Question UI
            QuestionAction* q = &b.questions[b.currentQuestion];
            DrawRectangle(sw - 420, sh/2 - 50, 400, 280, Fade(BLACK, 0.7f));
            DrawRectangleLines(sw - 420, sh/2 - 50, 400, 280, WHITE);
            DrawText(q->question, sw - 400, sh/2 - 30, 20, GOLD);

            for (int i = 0; i < 4; i++) {
                Rectangle rect = { (float)sw - 400, (float)(sh/2 + 20 + i * 45), 350, 35 };
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
    }

    UnloadTexture(bg);
}
