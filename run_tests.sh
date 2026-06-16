#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "Compilando suíte de testes com Coverage..."

# Limpar build anterior
rm -rf build
mkdir -p build

FLAGS="-O0 -g -fprofile-arcs -ftest-coverage -I include -I /opt/homebrew/include"
LIBS="-L /opt/homebrew/lib -lraylib"

# Compilar src na raiz para o gcov encontrar os caminhos relativos
gcc $FLAGS -c src/questions.c -o build/questions.o
gcc $FLAGS -c src/questions_data.c -o build/questions_data.o
gcc $FLAGS -c src/player.c -o build/player.o
gcc $FLAGS -c src/battle.c -o build/battle.o
gcc $FLAGS -c src/scenario.c -o build/scenario.o
gcc $FLAGS -c src/character.c -o build/character.o

# Compilar testes (agora incluindo character_tests)
gcc $FLAGS -c tests/question_tests.c -o build/question_tests.o
gcc $FLAGS -c tests/player_tests.c -o build/player_tests.o
gcc $FLAGS -c tests/battle_tests.c -o build/battle_tests.o
gcc $FLAGS -c tests/scenario_tests.c -o build/scenario_tests.o
gcc $FLAGS -c tests/character_tests.c -o build/character_tests.o
gcc $FLAGS -c tests/runner.c -o build/runner.o

# Linkar tudo
gcc build/*.o $LIBS -fprofile-arcs -o build/test_runner

if [ $? -eq 0 ]; then
    echo -e "${GREEN}Executando testes...${NC}\n"
    ./build/test_runner
    
    echo -e "\n${GREEN}Relatório de Cobertura (Resumo):${NC}"
    # Mover os .gcda gerados para a raiz temporariamente para o gcov
    cp build/*.gcda src/ 2>/dev/null
    cp build/*.gcno src/ 2>/dev/null
    
    # Rodar gcov nos arquivos da src
    gcov src/*.c | grep -A 1 "File 'src"
    
    # Limpar sujeira na src
    rm src/*.gcda src/*.gcno 2>/dev/null
else
    echo -e "${RED}Erro na compilação.${NC}"
    exit 1
fi
