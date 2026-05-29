#include "player.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define SAVE_FILE "data/saves.txt"

void LoadAllSaves(PlayerStats saves[MAX_SAVES]) {
    for (int i = 0; i < MAX_SAVES; i++) {
        saves[i].active = false;
        strcpy(saves[i].name, "Vazio");
    }

    FILE* file = fopen(SAVE_FILE, "r");
    if (!file) return;

    int slot;
    while (fscanf(file, "%d|%[^|]|%d|%d\n", &slot, saves[slot].name, &saves[slot].level, &saves[slot].lives) != EOF) {
        if (slot >= 0 && slot < MAX_SAVES) {
            saves[slot].active = true;
        }
    }

    fclose(file);
}

void SavePlayer(PlayerStats* player, int slot) {
    if (slot < 0 || slot >= MAX_SAVES) return;

    PlayerStats allSaves[MAX_SAVES];
    LoadAllSaves(allSaves);
    
    memcpy(&allSaves[slot], player, sizeof(PlayerStats));
    allSaves[slot].active = true;

    FILE* file = fopen(SAVE_FILE, "w");
    if (!file) return;

    for (int i = 0; i < MAX_SAVES; i++) {
        if (allSaves[i].active) {
            fprintf(file, "%d|%s|%d|%d\n", i, allSaves[i].name, allSaves[i].level, allSaves[i].lives);
        }
    }

    fclose(file);
}

void CreateNewPlayer(PlayerStats* player, const char* name) {
    strncpy(player->name, name, MAX_NAME_LENGTH - 1);
    player->level = 1;
    player->lives = 3;
    player->active = true;
}
