#ifndef QUESTIONS_H
#define QUESTIONS_H

#include "scenario.h"

#define MAX_DB_QUESTIONS 500

typedef struct {
    int level;
    int subject;
    char question[512];
    char options[4][128];
    int correctIndex;
} DBQuestion;

void InitQuestionDatabase();
void ResetUsedQuestions();
int GetRandomQuestions(QuestionAction* output, int count, int level, int subject);

const DBQuestion* GetInternalQuestions();
int GetInternalQuestionsCount();

#endif
