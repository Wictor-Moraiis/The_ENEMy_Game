#include "test_macros.h"
#include "battle.h"

void test_battle_initialization() {
    BattleState b;
    InitBattleState(&b, CHAR_MATH_ENEMY, DIFICULDADE_FACIL);
    
    ASSERT(b.enemyHP == 200, "Enemy HP should start at 200");
    ASSERT(b.ellieHP == 3, "Ellie HP should start at 3");
    ASSERT(b.finished == false, "Battle should not be finished initially");
    ASSERT(b.enemyId == CHAR_MATH_ENEMY, "Enemy ID should match");
}

void test_battle_damage_logic() {
    BattleState b;
    InitBattleState(&b, CHAR_MATH_ENEMY, DIFICULDADE_FACIL);
    
    int correct = b.questions[0].correctIndex;
    UpdateBattleLogic(&b, correct, 0.1f);
    ASSERT(b.showFeedback == true, "Should show feedback after choice");
    
    UpdateBattleLogic(&b, -1, 2.0f); // Finaliza feedback
    ASSERT(b.enemyHP == 160, "Enemy should take 40 damage");
    ASSERT(b.currentQuestion == 1, "Should advance to next question");
}

void test_battle_loss_logic() {
    BattleState b;
    InitBattleState(&b, CHAR_MATH_ENEMY, DIFICULDADE_FACIL);
    
    int wrong = (b.questions[0].correctIndex + 1) % 4;
    UpdateBattleLogic(&b, wrong, 0.1f);
    UpdateBattleLogic(&b, -1, 2.0f);
    
    ASSERT(b.ellieHP == 2, "Ellie should lose 1 HP");
    ASSERT(b.finished == false, "Battle should continue if HP > 0");
}

void test_battle_game_over() {
    BattleState b;
    InitBattleState(&b, CHAR_MATH_ENEMY, DIFICULDADE_FACIL);
    
    b.ellieHP = 1;
    int wrong = (b.questions[0].correctIndex + 1) % 4;
    UpdateBattleLogic(&b, wrong, 0.1f);
    UpdateBattleLogic(&b, -1, 2.0f);
    
    ASSERT(b.ellieHP == 0, "Ellie HP should be 0");
    // Lógica processa fim no próximo update ou no final do atual
    UpdateBattleLogic(&b, -1, 0.1f);
    ASSERT(b.won == false, "Should be marked as loss");
    ASSERT(b.finished == true, "Battle should be finished");
}

void test_battle_victory() {
    BattleState b;
    InitBattleState(&b, CHAR_MATH_ENEMY, DIFICULDADE_FACIL);
    
    b.enemyHP = 40;
    int correct = b.questions[0].correctIndex;
    UpdateBattleLogic(&b, correct, 0.1f);
    UpdateBattleLogic(&b, -1, 2.0f);
    
    ASSERT(b.enemyHP <= 0, "Enemy HP should be 0");
    UpdateBattleLogic(&b, -1, 0.1f);
    ASSERT(b.won == true, "Should be marked as won");
    ASSERT(b.finished == true, "Battle should be finished");
}

void test_battle_question_loop() {
    BattleState b;
    InitBattleState(&b, CHAR_MATH_ENEMY, DIFICULDADE_FACIL);
    
    // Forçar fim das questões mockadas
    b.currentQuestion = b.questionCount - 1;
    int correct = b.questions[b.currentQuestion].correctIndex;
    UpdateBattleLogic(&b, correct, 0.1f);
    UpdateBattleLogic(&b, -1, 2.0f);
    
    ASSERT(b.currentQuestion == 0, "Should loop back to question 0");
}

void test_battle_timers() {
    BattleState b;
    InitBattleState(&b, CHAR_MATH_ENEMY, DIFICULDADE_FACIL);
    
    b.damageFlashTimer = 0.5f;
    UpdateBattleLogic(&b, -1, 0.2f);
    ASSERT(b.damageFlashTimer < 0.5f, "Flash timer should decrease");
}

void run_battle_tests() {
    RUN_TEST(test_battle_initialization);
    RUN_TEST(test_battle_damage_logic);
    RUN_TEST(test_battle_loss_logic);
    RUN_TEST(test_battle_game_over);
    RUN_TEST(test_battle_victory);
    RUN_TEST(test_battle_question_loop);
    RUN_TEST(test_battle_timers);
}
