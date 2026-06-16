#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define MAX_SAVES 5
#define MAX_NAME_LENGTH 16

typedef struct {
    char name[MAX_NAME_LENGTH];
    int level;
    int lives;
    bool active;
} PlayerStats;

// Funções de Gerenciamento de Save
void LoadAllSaves(PlayerStats saves[MAX_SAVES]);
void SavePlayer(PlayerStats* player, int slot);
void CreateNewPlayer(PlayerStats* player, const char* name);

#endif
