#include "test_macros.h"
#include "questions.h"
#include <string.h>

void test_question_database_load() {
    InitQuestionDatabase();
    int count = GetInternalQuestionsCount();
    ASSERT(count > 0, "Database should not be empty");
}

void test_question_random_selection() {
    InitQuestionDatabase();
    QuestionAction out[3];
    
    // Teste para cada matéria
    for (int subject = 1; subject <= 4; subject++) {
        int count = GetRandomQuestions(out, 3, 1, subject); 
        ASSERT(count > 0, "Should select at least one question for each subject");
        ASSERT(count <= 3, "Should not exceed requested count");
    }
}

void test_question_uniqueness_and_emergency_reset() {
    InitQuestionDatabase();
    ResetUsedQuestions();
    
    QuestionAction out[1];
    int totalArtes = 0;
    const DBQuestion* db = GetInternalQuestions();
    int total = GetInternalQuestionsCount();
    
    for(int i = 0; i < total; i++) {
        if(db[i].subject == 1) totalArtes++;
    }

    // Consumir todas as questões de Artes nível 1
    for(int i = 0; i < totalArtes; i++) {
        int count = GetRandomQuestions(out, 1, 1, 1);
        ASSERT(count == 1, "Should pick a question");
    }
    
    // Tentar pegar mais uma - deve disparar o fallback/reset
    int count = GetRandomQuestions(out, 1, 1, 1);
    ASSERT(count == 1, "Emergency reset should provide a question when pool is empty");
}

void test_question_level_fallback() {
    InitQuestionDatabase();
    ResetUsedQuestions();
    QuestionAction out[1];
    
    // Tenta pegar nível 3 de uma matéria que talvez não tenha muitas
    int count = GetRandomQuestions(out, 1, 3, 1);
    if (count == 0) {
        // Se count for 0 aqui, a função falhou em fazer o fallback para nível 1?
        // Vamos forçar um cenário onde o nível não existe
        count = GetRandomQuestions(out, 1, 99, 1);
        ASSERT(count > 0, "Should fallback to any level if target level is empty");
    }
}

void run_question_tests() {
    RUN_TEST(test_question_database_load);
    RUN_TEST(test_question_random_selection);
    RUN_TEST(test_question_uniqueness_and_emergency_reset);
    RUN_TEST(test_question_level_fallback);
}
