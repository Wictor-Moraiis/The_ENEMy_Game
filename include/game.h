#ifndef GAME_H
#define GAME_H

#include "types.h"
#include "battle.h"
#include "player.h"

#define MAX_LIVES 3


// Protótipos de fluxo de jogo
void ExecutarJogo(PlayerStats* player, int slot);
void IniciarTutorial();
void IniciarNivel1();
void IniciarNivel2();

#endif
