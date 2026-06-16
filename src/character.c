#include "character.h"
#include <string.h>

static Character characters[10]; // Ajuste o tamanho conforme necessário
static int charCount = 0;

void InitCharacters() {
    // Personagem: Consciência (Sem imagem)
    characters[0] = (Character){CHAR_CONSCIENCIA, "Consciência", "", {0}};
    
    // Personagem: Voz Grave (Sem imagem)
    characters[1] = (Character){CHAR_VOZ_GRAVE, "Voz Grave", "", {0}};
    
    // Personagem: Máscara de Artes
    characters[2] = (Character){CHAR_MASCARA_ARTES, "Roger Gramathor", "assets/graphics/enemy_languages.png", {0}};
    // Carrega a textura se o caminho não for vazio
    characters[2].texture = LoadTexture(characters[2].imagePath);

    characters[3] = (Character){CHAR_ELLIE, "Ellie", "assets/graphics/ellie.png", {0}};
    characters[3].texture = LoadTexture(characters[3].imagePath);

    characters[4] = (Character){CHAR_MATH_ENEMY, "Math Murdock", "assets/graphics/enemy_math.png", {0}};
    characters[4].texture = LoadTexture(characters[4].imagePath);

    characters[5] = (Character){CHAR_NATUREZA_BOSS, "Jefferson Mutagenox", "assets/graphics/enemy_nature.png", {0}};
    characters[5].texture = LoadTexture(characters[5].imagePath);

    //add o globo aqui
    characters[6] = (Character){CHAR_ENEMY_HUMANITIES, "Atlas Mentis", "assets/graphics/enemy_humanities.png", {0}};
    characters[6].texture = LoadTexture(characters[6].imagePath);
    
    charCount = 7; 
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
