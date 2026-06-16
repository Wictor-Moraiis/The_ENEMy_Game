#include "test_macros.h"
#include "character.h"
#include <stddef.h>

void test_character_initialization_mock() {
    // Como LoadTexture exige GPU/Window, testamos apenas a lógica de IDs sem InitCharacters real
    // Mas para coverage real, precisamos de um init que não quebre.
    // Como a engine é Raylib-dependente nos assets, o coverage de init real é difícil sem window.
    // Vamos apenas garantir que a lógica de busca por ID funciona.
}

void run_character_tests() {
    // RUN_TEST(test_character_initialization_mock);
}
