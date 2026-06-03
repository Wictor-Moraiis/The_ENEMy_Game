#include "questions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void InitQuestionDatabase() {
    srand(time(NULL));
}

int GetRandomQuestions(QuestionAction* output, int count, int level, int subject) {
    const DBQuestion* db = GetInternalQuestions();
    int total = GetInternalQuestionsCount();
    
    DBQuestion filtered[MAX_DB_QUESTIONS];
    int filteredCount = 0;

    for (int i = 0; i < total; i++) {
        if (db[i].level == level && db[i].subject == subject) {
            filtered[filteredCount++] = db[i];
        }
    }

    if (filteredCount == 0) return 0;

    int picked = (filteredCount < count) ? filteredCount : count;
    
    // Embaralhar
    for (int i = 0; i < filteredCount; i++) {
        int j = rand() % filteredCount;
        DBQuestion temp = filtered[i];
        filtered[i] = filtered[j];
        filtered[j] = temp;
    }

    for (int i = 0; i < picked; i++) {
        strncpy(output[i].question, filtered[i].question, 511);
        for (int j = 0; j < 4; j++) {
            strncpy(output[i].options[j], filtered[i].options[j], 127);
        }
        output[i].correctIndex = filtered[i].correctIndex;
        output[i].level = filtered[i].level;
    }

    return picked;
}
