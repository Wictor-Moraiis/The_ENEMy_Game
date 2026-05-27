#ifndef GAME_H
#define GAME_H

#define MAX_LIVES 3

typedef enum {
    DIFICULDADE_FACIL,
    DIFICULDADE_MEDIA,
    DIFICULDADE_DIFICIL
} Dificuldade;

typedef struct {
    char pergunta[256];
    char opcoes[4][100];
    char resposta_correta;
    Dificuldade dificuldade;
} Questao;

void iniciar_tutorial();
void iniciar_nivel(int nivel);

#endif
