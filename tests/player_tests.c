#include "test_macros.h"
#include "player.h"
#include <string.h>

void test_create_new_player() {
    PlayerStats p;
    CreateNewPlayer(&p, "TestPlayer");
    ASSERT(strcmp(p.name, "TestPlayer") == 0, "Player name should match");
    ASSERT(p.level == 1, "New player should start at level 1");
    ASSERT(p.lives == 3, "New player should start with 3 lives");
    ASSERT(p.active == true, "New player should be active");
}

// Nota: Testar Save/Load requer manipulação de arquivo, 
// o que pode ser perigoso em ambientes de teste se não usar arquivos temporários.

void run_player_tests() {
    RUN_TEST(test_create_new_player);
}
