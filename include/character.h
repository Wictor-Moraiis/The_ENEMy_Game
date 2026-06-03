#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"

typedef struct {
    int id;
    char name[64];
    char imagePath[128];
    Texture2D texture;
} Character;

// IDs de Personagens para facilitar o uso
typedef enum {
    CHAR_NONE = 0,
    CHAR_CONSCIENCIA,
    CHAR_VOZ_GRAVE,
    CHAR_MASCARA_ARTES,
    CHAR_ELLIE,
    CHAR_MATH_ENEMY,
    CHAR_NATUREZA_BOSS
    // Adicione novos IDs aqui
} CharacterID;

// Funções de gerenciamento
void InitCharacters();
Character* GetCharacter(CharacterID id);
void UnloadCharacters();

#endif
