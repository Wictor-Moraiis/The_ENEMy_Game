#ifndef GAME_H
#define GAME_H

#include "types.h"

#define MAX_LIVES 3

typedef struct {
    char pergunta[256];
    char opcoes[4][100];
    char resposta_correta;
    Dificuldade dificuldade;
} Questao;

// Protótipos de fluxo de jogo
void ExecutarJogo();
void IniciarTutorial();

#endif
