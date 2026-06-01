#ifndef SCENARIO_H
#define SCENARIO_H

#include "raylib.h"
#include "character.h"
#include <stdbool.h>

#define MAX_ACTIONS 100
#define MAX_OPTIONS 4

typedef enum {
    ACTION_SPEAK,
    ACTION_QUESTION,
    ACTION_BACKGROUND
} ActionType;

typedef struct {
    CharacterID charId;
    char text[512];
} SpeakAction;

typedef struct {
    char question[512];
    char options[MAX_OPTIONS][128];
    int correctIndex;
    int level;
} QuestionAction;

typedef struct {
    char imagePath[128];
} BackgroundAction;

typedef struct {
    ActionType type;
    union {
        SpeakAction speak;
        QuestionAction question;
        BackgroundAction background;
    } data;
} ScenarioAction;

typedef struct {
    ScenarioAction actions[MAX_ACTIONS];
    int actionCount;
    int currentAction;
    bool completed;
    
    // Fundo atual
    Texture2D currentBg;
    char currentBgPath[128];

    // Controle de Texto Dinâmico
    int textProgress;
    float textTimer;
    bool isTextEffectDone;
} Scenario;

// Construtores e Manipuladores
Scenario CreateScenario();
void AddSpeak(Scenario* s, CharacterID charId, const char* text);
void AddQuestion(Scenario* s, const char* question, const char* options[MAX_OPTIONS], int correctIndex, int level);
void AddBackground(Scenario* s, const char* imagePath);

// Execução
void UpdateAndDrawScenario(Scenario* s);
bool IsScenarioFinished(Scenario* s);
void UnloadScenarioResources(Scenario* s);

#endif
