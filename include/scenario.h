#ifndef SCENARIO_H
#define SCENARIO_H

#include "raylib.h"
#include <stdbool.h>

#define MAX_ACTIONS 100
#define MAX_OPTIONS 4

typedef enum {
    ACTION_SPEAK,
    ACTION_QUESTION
} ActionType;

typedef struct {
    char person[64];
    char text[512];
} SpeakAction;

typedef struct {
    char question[512];
    char options[MAX_OPTIONS][128];
    int correctIndex;
    int level;
} QuestionAction;

typedef struct {
    ActionType type;
    union {
        SpeakAction speak;
        QuestionAction question;
    } data;
} ScenarioAction;

typedef struct {
    ScenarioAction actions[MAX_ACTIONS];
    int actionCount;
    int currentAction;
    bool completed;
} Scenario;

// Construtores e Manipuladores
Scenario CreateScenario();
void AddSpeak(Scenario* s, const char* person, const char* text);
void AddQuestion(Scenario* s, const char* question, const char* options[MAX_OPTIONS], int correctIndex, int level);

// Execução
void UpdateAndDrawScenario(Scenario* s);
bool IsScenarioFinished(Scenario* s);

#endif
