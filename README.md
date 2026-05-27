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

## 📁 Estrutura do Projeto

A organização das pastas segue o padrão abaixo para facilitar o desenvolvimento e a inclusão de novos conteúdos:

*   `src/`: Contém todo o código-fonte em C (`.c`).
*   `include/`: Contém os arquivos de cabeçalho (`.h`).
*   `assets/`: Arquivos de mídia do jogo.
    *   `assets/graphics/`: Pasta destinada às **pixel arts** e sprites.
    *   `assets/audio/`: Pasta para trilhas sonoras e efeitos sonoros.
*   `data/`: Banco de dados das questões e configurações de níveis (arquivos `.txt` ou `.csv`).
*   `build/`: Pasta para os arquivos binários resultantes da compilação (geralmente ignorada pelo controle de versão).

## 🎨 Como Adicionar Conteúdo

### Pixel Arts
Para adicionar novas artes ao jogo, coloque os arquivos de imagem (preferencialmente `.png` para manter transparência) na pasta `assets/graphics/`.

### Questões do Quiz
As questões devem ser formatadas e inseridas nos arquivos dentro da pasta `data/`. Siga o padrão estabelecido nos arquivos de exemplo para garantir que o motor do jogo consiga lê-las corretamente.

---

## 🚀 Como Compilar e Rodar

Este projeto utiliza a linguagem C e a biblioteca **Raylib** para a interface gráfica e áudio. Abaixo estão as instruções detalhadas para configurar seu ambiente no macOS e no Windows.

### 🍎 macOS

**1. Instalar Dependências (via Homebrew)**
Se você não tem o Homebrew, instale-o primeiro. Depois, instale o compilador GCC e a biblioteca Raylib:
```bash
brew install gcc raylib
```

**2. Compilar**
No terminal, na raiz do projeto, execute:
```bash
gcc src/main.c -I include -I /opt/homebrew/include -L /opt/homebrew/lib -lraylib -o build/the_enemy_game
```

**3. Rodar**
```bash
./build/the_enemy_game
```

---

### 🪟 Windows

Para compilar no Windows, recomendamos o uso do **MSYS2** (MinGW-w64), que fornece um ambiente de desenvolvimento semelhante ao Linux.

**1. Instalar o MSYS2**
Baixe e instale o MSYS2 do site oficial: [msys2.org](https://www.msys2.org/).

**2. Instalar Dependências**
Abra o terminal **MSYS2 MinGW 64-bit** e instale a toolchain do GCC e a Raylib:
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-raylib
```
*(Aperte `Y` quando for solicitado para confirmar a instalação)*

**3. Compilar**
Abra o terminal **MSYS2 MinGW 64-bit**, navegue até a pasta do projeto e execute:
```bash
gcc src/main.c -I include -lraylib -lgdi32 -lwinmm -o build/the_enemy_game.exe
```
*(Nota: As flags `-lgdi32` e `-lwinmm` são necessárias no Windows para gráficos e áudio).*

**4. Rodar**
```bash
./build/the_enemy_game.exe
```
