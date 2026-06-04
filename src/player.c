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
    char name[MAX_NAME_LENGTH];
    int level, lives;
    
    // Formato: slot|nome|level|lives
    while (fscanf(file, "%d|%[^|]|%d|%d\n", &slot, name, &level, &lives) != EOF) {
        if (slot >= 0 && slot < MAX_SAVES) {
            saves[slot].active = true;
            strncpy(saves[slot].name, name, MAX_NAME_LENGTH - 1);
            saves[slot].level = level;
            saves[slot].lives = lives;
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
