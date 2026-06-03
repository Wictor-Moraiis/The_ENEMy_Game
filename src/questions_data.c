#include "questions.h"

// Banco de dados estático em C
static const DBQuestion internalDB[] = {
    // ARTES (1)
    {1, 1, "Qual movimento brasileiro teve como marco a Semana de 22?", {"Modernismo", "Barroco", "Renascimento", "Surrealismo"}, 0},
    {1, 1, "Quem pintou o quadro 'Abaporu'?", {"Anita Malfatti", "Tarsila do Amaral", "Di Cavalcanti", "Cândido Portinari"}, 1},
    {2, 1, "A antropofagia na arte brasileira propunha:", {"Cópia fiel", "Rejeição total", "Devorar influências", "Tradições coloniais"}, 2},
    {2, 1, "Qual artista criou as esculturas de 'Bichos'?", {"Lygia Clark", "Hélio Oiticica", "Vik Muniz", "Tomie Ohtake"}, 0},
    {2, 1, "O movimento Impressionista foca principalmente em:", {"Detalhes precisos", "Luz e cor", "Geometria", "Sentimentos internos"}, 1},
    {3, 1, "Qual característica define o Surrealismo?", {"Realismo extremo", "Cenas oníricas", "Cores primárias", "Linhas retas"}, 1},

    // HUMANAS (2)
    {1, 2, "Qual o principal objetivo da ONU?", {"Guerra", "Paz e segurança", "Controlar petróleo", "Socialismo"}, 1},
    {2, 2, "A 'Guerra Fria' foi marcada por:", {"Conflito direto", "Disputa ideológica", "Domínio Romano", "Rev. Industrial"}, 1},
    {3, 2, "A 'Questão de Canudos' envolveu qual grupo?", {"Cangaceiros", "Monarquistas e Conselheiro", "Escravos", "Imigrantes"}, 1},
    {1, 2, "Em que ano começou a Primeira Guerra Mundial?", {"1914", "1939", "1918", "1945"}, 0},
    {1, 2, "Quem descobriu o Brasil (oficialmente)?", {"Vasco da Gama", "Pedro Álvares Cabral", "Cristóvão Colombo", "Américo Vespúcio"}, 1},
    {2, 2, "O que foi o Iluminismo?", {"Movimento religioso", "Movimento intelectual", "Revolta camponesa", "Guerra civil"}, 1},
    {2, 2, "A Revolução Francesa teve como lema:", {"Ordem e Progresso", "Liberdade, Igualdade, Fraternidade", "Paz e Pão", "Deus, Pátria e Família"}, 1},

    // NATUREZA (3)
    {1, 3, "Função dos glóbulos vermelhos:", {"Defesa", "Oxigênio", "Coagulação", "Insulina"}, 1},
    {2, 3, "O oxigênio na fotossíntese vem de:", {"CO2", "Luz", "Água e Luz", "Nitrogênio"}, 2},
    {3, 3, "Plantas produzem oxigênio a partir de:", {"Nitrogênio", "Glicose", "Luz e CO2", "Água"}, 2},
    {1, 3, "Qual o estado físico do gelo?", {"Líquido", "Sólido", "Gasoso", "Plasma"}, 1},
    {3, 3, "Qual a principal função do DNA?", {"Produzir energia", "Armazenar info genética", "Transportar oxigênio", "Digerir alimentos"}, 1},

    // MATEMÁTICA (4)
    {1, 4, "Quanto é a raiz quadrada de 144?", {"10", "12", "14", "16"}, 1},
    {2, 4, "Um triângulo de lados 3, 4 e 5 é:", {"Equilátero", "Isósceles", "Retângulo", "Obtuso"}, 2},
    {3, 4, "Qual o valor de Pi (aproximado)?", {"3.14", "3.15", "3.10", "3.16"}, 0},
    {1, 4, "Qual o valor de 2 elevado ao cubo?", {"4", "6", "8", "9"}, 2},
    {2, 4, "A soma dos ângulos internos de um triângulo é:", {"90°", "180°", "270°", "360°"}, 1},
    {3, 4, "O Teorema de Pitágoras é aplicado em triângulos:", {"Equiláteros", "Retângulos", "Isósceles", "Acutângulos"}, 1}

};

static const int internalDBCount = sizeof(internalDB) / sizeof(internalDB[0]);

const DBQuestion* GetInternalQuestions() {
    return internalDB;
}

int GetInternalQuestionsCount() {
    return internalDBCount;
}
