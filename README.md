# The ENEMy Game

Um jogo de RPG onde o conhecimento é a sua maior arma. Enfrente os desafios do ENEM em uma jornada épica que começa nos seus sonhos.

## 📝 Contexto do Jogo

O jogo inicia com o protagonista em um **sonho**, que serve como o **Tutorial**. Nele, você aprenderá as mecânicas básicas de combate e exploração.

O jogo é dividido em:
1.  **Tutorial (O Sonho):** Introdução às mecânicas.
2.  **Nível 1 (Áreas do 1º Dia):** Questões de Linguagens, Códigos e suas Tecnologias / Ciências Humanas e suas Tecnologias.
3.  **Nível 2 (Áreas do 2º Dia):** Questões de Ciências da Natureza e suas Tecnologias / Matemática e suas Tecnologias.

## ⚔️ Mecânicas de Combate

No **The ENEMy Game**, os ataques são realizados através de um quiz.
*   **Ataque Bem-Sucedido:** Responda corretamente para causar dano ao inimigo.
*   **Dificuldade vs Dano:**
    *   **Fácil:** Causa uma porcentagem menor de dano.
    *   **Médio:** Causa dano moderado.
    *   **Difícil:** Causa dano crítico (alta porcentagem).
*   **Defesa e Vidas:** Você possui vidas limitadas. Cada erro nas questões resulta em perda de HP/Vida. Se suas vidas chegarem a zero, o jogo acaba.

## 📁 Estrutura do Projeto (Refatorado)

*   `src/`:
    *   `main.c`: Inicialização da Raylib e Splash Screen.
    *   `game.c`: Lógica de fluxo do jogo e níveis.
    *   `scenario.c`: Core da Engine de Cenários.
*   `include/`:
    *   `types.h`: Definições globais de enums e structs básicas.
    *   `game.h`: Constantes e protótipos do jogo.
    *   `scenario.h`: Definições e funções da engine de cenários.

## 🎬 Engine de Cenários

A engine permite criar cutscenes e quizzes de forma programática.

### Como Criar uma Cena
No arquivo `src/game.c`, você pode criar um novo cenário e encadear ações:

```c
Scenario cena = CreateScenario();

// Adicionar um diálogo
AddSpeak(&cena, "Nome", "Texto do diálogo");

// Adicionar uma pergunta
const char* opcoes[] = {"A", "B", "C", "D"};
AddQuestion(&cena, "Pergunta?", opcoes, 0, 1); // (Cena, Pergunta, Opções, Índice Correto, Nível)
```

### Como Executar
No seu loop principal ou função de fase:
```c
while (!IsScenarioFinished(&cena)) {
    BeginDrawing();
        UpdateAndDrawScenario(&cena);
    EndDrawing();
}
```

*Nota: A funcionalidade de **Skip (Tecla S)** é automática e padrão para todos os cenários.*

---

## 🚀 Como Compilar e Rodar

### 🍎 macOS
```bash
gcc src/*.c -I include -I /opt/homebrew/include -L /opt/homebrew/lib -lraylib -o build/the_enemy_game
```

### 🪟 Windows (MSYS2)
```bash
gcc src/*.c -I include -lraylib -lgdi32 -lwinmm -o build/the_enemy_game.exe
```

**4. Rodar**
```bash
./build/the_enemy_game.exe
```
