#include "questions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

static bool usedQuestions[MAX_DB_QUESTIONS] = {false};

void InitQuestionDatabase() {
    srand(time(NULL));
    ResetUsedQuestions();
}

void ResetUsedQuestions() {
    for (int i = 0; i < MAX_DB_QUESTIONS; i++) {
        usedQuestions[i] = false;
    }
}

int GetRandomQuestions(QuestionAction* output, int count, int level, int subject) {
    const DBQuestion* db = GetInternalQuestions();
    int total = GetInternalQuestionsCount();
    
    int filteredIndices[MAX_DB_QUESTIONS];
    int filteredCount = 0;

    // Filtrar apenas questões não utilizadas daquela matéria e nível
    for (int i = 0; i < total && i < MAX_DB_QUESTIONS; i++) {
        if (db[i].level == level && db[i].subject == subject && !usedQuestions[i]) {
            filteredIndices[filteredCount++] = i;
        }
    }

    // Se não houver questões não usadas desse nível, tenta relaxar a busca
    if (filteredCount == 0) {
        for (int i = 0; i < total && i < MAX_DB_QUESTIONS; i++) {
            if (db[i].subject == subject && !usedQuestions[i]) {
                filteredIndices[filteredCount++] = i;
            }
        }
    }

    // EMERGÊNCIA: Se ainda assim não houver nada, resetamos o banco desta matéria
    if (filteredCount == 0) {
        for (int i = 0; i < total && i < MAX_DB_QUESTIONS; i++) {
            if (db[i].subject == subject) {
                usedQuestions[i] = false;
                filteredIndices[filteredCount++] = i;
            }
        }
    }

    if (filteredCount == 0) return 0;

    int picked = (filteredCount < count) ? filteredCount : count;
    
    // Embaralhar índices
    for (int i = 0; i < filteredCount; i++) {
        int j = rand() % filteredCount;
        int temp = filteredIndices[i];
        filteredIndices[i] = filteredIndices[j];
        filteredIndices[j] = temp;
    }

    // Copiar e marcar como usada
    for (int i = 0; i < picked; i++) {
        int idx = filteredIndices[i];
        usedQuestions[idx] = true; 

        strncpy(output[i].question, db[idx].question, 511);
        for (int j = 0; j < 4; j++) {
            strncpy(output[i].options[j], db[idx].options[j], 127);
        }
        output[i].correctIndex = db[idx].correctIndex;
        output[i].level = db[idx].level;
    }

    return picked;
}
