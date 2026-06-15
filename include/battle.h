#ifndef BATTLE_H
#define BATTLE_H

#include "character.h"
#include "types.h"
#include "scenario.h"
#include "questions.h"

#define MAX_BATTLE_QUESTIONS 5

typedef struct {
    CharacterID enemyId;
    int enemyHP;
    int maxEnemyHP;
    int ellieHP;
    int maxEllieHP;
    bool finished;
    bool won;
    int currentQuestion;
    QuestionAction questions[MAX_BATTLE_QUESTIONS];
    int questionCount;
    
    bool showFeedback;
    int lastChoice;
    float feedbackTimer;
    bool correctHit;
    float damageFlashTimer;
    float ellieFlashTimer;
} BattleState;

void InitBattleState(BattleState* b, CharacterID enemyId, Dificuldade diff);
void UpdateBattleLogic(BattleState* b, int choice, float delta);
bool StartBattle(CharacterID enemyId, Dificuldade diff);

#endif
