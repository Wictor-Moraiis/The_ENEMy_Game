#include "character.h"
#include <string.h>

static Character characters[10]; // Ajuste o tamanho conforme necessário
static int charCount = 0;

void InitCharacters() {
    // Personagem: Consciência (Sem imagem)
    characters[0] = (Character){CHAR_CONSCIENCIA, "Consciencia", "", {0}};
    
    // Personagem: Voz Grave (Sem imagem)
    characters[1] = (Character){CHAR_VOZ_GRAVE, "Voz Grave", "", {0}};
    
    // Personagem: Máscara de Artes
    characters[2] = (Character){CHAR_MASCARA_ARTES, "Entidade das Artes", "assets/graphics/theatrical-mask-languages.png", {0}};
    // Carrega a textura se o caminho não for vazio
    characters[2].texture = LoadTexture(characters[2].imagePath);

    characters[3] = (Character){CHAR_ELLIE, "Ellie", "assets/graphics/ellie_front.png", {0}};
    characters[3].texture = LoadTexture(characters[3].imagePath);

    charCount = 4;
}

Character* GetCharacter(CharacterID id) {
    for (int i = 0; i < charCount; i++) {
        if (characters[i].id == id) return &characters[i];
    }
    return NULL;
}

void UnloadCharacters() {
    for (int i = 0; i < charCount; i++) {
        if (characters[i].texture.id > 0) {
            UnloadTexture(characters[i].texture);
        }
    }
}
