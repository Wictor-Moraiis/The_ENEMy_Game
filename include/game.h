#ifndef GAME_H
#define GAME_H

#include "types.h"
#include "battle.h"
#include "player.h"

#define MAX_LIVES 3


// Protótipos de fluxo de jogo
void ExecutarJogo(PlayerStats* player, int slot);
bool IniciarTutorial();
bool IniciarNivel1();
bool IniciarNivel2();
bool IniciarNivel3();
#endif
