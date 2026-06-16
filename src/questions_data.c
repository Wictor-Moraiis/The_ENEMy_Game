#include "questions.h"

// Banco de dados estático em C
// Ordem: {nível, matéria, pergunta, {opções}, índice_correto}
// Matérias: 1-Artes/Linguagens, 2-Humanas, 3-Natureza, 4-Matemática
static const DBQuestion internalDB[] = {
    // === ARTES / LINGUAGENS (1) ===
    // Nível 1
    {1, 1, "Qual movimento brasileiro teve como marco a Semana de 22?", {"Modernismo", "Barroco", "Renascimento", "Surrealismo"}, 0},
    {1, 1, "Quem pintou o quadro 'Abaporu'?", {"Anita Malfatti", "Tarsila do Amaral", "Di Cavalcanti", "Cândido Portinari"}, 1},
    {1, 1, "Qual o nome da obra mais famosa de Leonardo da Vinci?", {"Mona Lisa", "A Última Ceia", "O Grito", "Guernica"}, 0},
    {1, 1, "Quem escreveu 'Dom Casmurro'?", {"Machado de Assis", "José de Alencar", "Clarice Lispector", "Jorge Amado"}, 0},
    {1, 1, "Qual destas é considerada uma cor primária?", {"Verde", "Laranja", "Azul", "Roxo"}, 2},
    {1, 1, "Quem é o autor de 'O Sítio do Picapau Amarelo'?", {"Monteiro Lobato", "Ziraldo", "Maurício de Sousa", "Ruth Rocha"}, 0},
    {1, 1, "Qual a principal característica do Cubismo?", {"Cores vivas", "Formas geométricas", "Realismo", "Luz e sombra"}, 1},

    // Nível 2
    {2, 1, "A antropofagia na arte brasileira propunha:", {"Cópia fiel", "Rejeição total", "Devorar influências", "Tradições coloniais"}, 2},
    {2, 1, "Qual artista criou as esculturas de 'Bichos'?", {"Lygia Clark", "Hélio Oiticica", "Vik Muniz", "Tomie Ohtake"}, 0},
    {2, 1, "O movimento Impressionista foca principalmente em:", {"Detalhes precisos", "Luz e cor", "Geometria", "Sentimentos internos"}, 1},
    {2, 1, "O que caracteriza o movimento Barroco?", {"Simplicidade", "Dualidade e ornamentação", "Racionalismo", "Minimalismo"}, 1},
    {2, 1, "Quem pintou o teto da Capela Sistina?", {"Donatello", "Michelangelo", "Rafael", "Leonardo da Vinci"}, 1},
    {2, 1, "O Realismo surgiu como oposição a qual movimento?", {"Barroco", "Modernismo", "Romantismo", "Arcadismo"}, 2},
    {2, 1, "Qual o principal representante do Arcadismo no Brasil?", {"Gregório de Matos", "Tomás Antônio Gonzaga", "Gonçalves Dias", "Castro Alves"}, 1},

    // Nível 3
    {3, 1, "Qual característica define o Surrealismo?", {"Realismo extremo", "Cenas oníricas", "Cores primárias", "Linhas retas"}, 1},
    {3, 1, "O que foi o Parnasianismo na literatura?", {"Foco no social", "Arte pela arte", "Subjetivismo", "Linguagem coloquial"}, 1},
    {3, 1, "Quem escreveu o épico 'Os Lusíadas'?", {"Fernando Pessoa", "Luís de Camões", "Eça de Queirós", "Saramago"}, 1},
    {3, 1, "Qual a obra-prima de João Guimarães Rosa?", {"Dom Casmurro", "Vidas Secas", "Grande Sertão: Veredas", "O Cortiço"}, 2},
    {3, 1, "A Semana de Arte Moderna de 1922 foi influenciada por:", {"Vanguardas Europeias", "Cultura Oriental", "Arte Rupestre", "Classicismo"}, 0},
    {3, 1, "Quem pintou o mural 'Guernica'?", {"Salvador Dalí", "Joan Miró", "Pablo Picasso", "Frida Kahlo"}, 2},
    {3, 1, "Em linguística, o que define a intertextualidade?", {"Texto sem autor", "Relação entre textos", "Erros de gramática", "Tradução literal"}, 1},

    // === HUMANAS (2) ===
    // Nível 1
    {1, 2, "Qual o principal objetivo da ONU?", {"Guerra", "Paz e segurança", "Controlar petróleo", "Socialismo"}, 1},
    {1, 2, "Em que ano começou a Primeira Guerra Mundial?", {"1914", "1939", "1918", "1945"}, 0},
    {1, 2, "Quem descobriu o Brasil (oficialmente)?", {"Vasco da Gama", "Pedro Álvares Cabral", "Cristóvão Colombo", "Américo Vespúcio"}, 1},
    {1, 2, "Quem foi o primeiro presidente do Brasil?", {"Deodoro da Fonseca", "Floriano Peixoto", "Getúlio Vargas", "Dom Pedro II"}, 0},
    {1, 2, "Qual continente é conhecido como o 'Velho Mundo'?", {"América", "Ásia", "Europa", "Oceania"}, 2},
    {1, 2, "Em que país da antiguidade surgiu a democracia?", {"Egito", "Roma", "Grécia", "China"}, 2},
    {1, 2, "Qual é a capital atual do Brasil?", {"Rio de Janeiro", "Salvador", "Brasília", "São Paulo"}, 2},

    // Nível 2
    {2, 2, "A 'Guerra Fria' foi marcada por:", {"Conflito direto", "Disputa ideológica", "Domínio Romano", "Rev. Industrial"}, 1},
    {2, 2, "O que foi o Iluminismo?", {"Movimento religioso", "Movimento intelectual", "Revolta camponesa", "Guerra civil"}, 1},
    {2, 2, "A Revolução Francesa teve como lema:", {"Ordem e Progresso", "Liberdade, Igualdade, Fraternidade", "Paz e Pão", "Deus, Pátria e Família"}, 1},
    {2, 2, "O que caracterizava o sistema do Feudalismo?", {"Capitalismo", "Posse de terra e vassalagem", "Indústria", "Comércio marítimo"}, 1},
    {2, 2, "Quem proclamou a Independência do Brasil?", {"José Bonifácio", "Dom Pedro I", "Dom João VI", "Tiradentes"}, 1},
    {2, 2, "Qual foi o estopim da Primeira Revolução Industrial?", {"Máquina a vapor", "Eletricidade", "Computador", "Internet"}, 0},
    {2, 2, "O que foi o regime do Apartheid na África do Sul?", {"Ditadura militar", "Segregação racial", "Monarquia", "Democracia direta"}, 1},

    // Nível 3
    {3, 2, "A 'Questão de Canudos' envolveu qual grupo?", {"Cangaceiros", "Monarquistas e Conselheiro", "Escravos", "Imigrantes"}, 1},
    {3, 2, "A queda do Muro de Berlim em 1989 simbolizou:", {"Início da 2ª Guerra", "Fim da Guerra Fria", "Revolução Francesa", "Paz de Versalhes"}, 1},
    {3, 2, "Quem foi o principal líder da Revolução Cubana?", {"Che Guevara", "Fidel Castro", "Hugo Chávez", "Simón Bolívar"}, 1},
    {3, 2, "O período da Ditadura Militar no Brasil (1964-1985) teve:", {"Plena liberdade", "Censura e reflexão", "Voto direto", "Fim da corrupção"}, 1},
    {3, 2, "O conceito de Globalização refere-se a:", {"Isolamento", "Integração mundial", "Fim das fronteiras", "Guerra total"}, 1},
    {3, 2, "Quem é o autor da famosa obra política 'O Príncipe'?", {"Hobbes", "Maquiavel", "Locke", "Rousseau"}, 1},
    {3, 2, "A Reforma Protestante do século XVI foi iniciada por:", {"João Paulo II", "Martinho Lutero", "Henrique VIII", "João Calvino"}, 1},

    // === NATUREZA (3) ===
    // Nível 1
    {1, 3, "Função dos glóbulos vermelhos:", {"Defesa", "Oxigênio", "Coagulação", "Insulina"}, 1},
    {1, 3, "Qual o estado físico do gelo?", {"Líquido", "Sólido", "Gasoso", "Plasma"}, 1},
    {1, 3, "Qual o maior planeta do Sistema Solar?", {"Terra", "Marte", "Júpiter", "Saturno"}, 2},
    {1, 3, "Qual gás é essencial para a respiração humana?", {"Nitrogênio", "Oxigênio", "Gás Carbônico", "Hélio"}, 1},
    {1, 3, "Quantos planetas compõem o nosso Sistema Solar?", {"7", "8", "9", "10"}, 1},
    {1, 3, "Qual é o único satélite natural da Terra?", {"Sol", "Lua", "Marte", "Estrela cadente"}, 1},
    {1, 3, "Em qual órgão ocorre a maior parte da digestão de proteínas?", {"Boca", "Estômago", "Intestino Grosso", "Fígado"}, 1},

    // Nível 2
    {2, 3, "O oxigênio na fotossíntese vem de:", {"CO2", "Luz", "Água e Luz", "Nitrogênio"}, 2},
    {2, 3, "O que propõe a Teoria da Seleção Natural de Darwin?", {"Uso e desuso", "Sobrevivência do mais apto", "Mutação dirigida", "Geração espontânea"}, 1},
    {2, 3, "Qual a principal função das mitocôndrias na célula?", {"Síntese proteica", "Produção de energia", "Digestão", "Divisão celular"}, 1},
    {2, 3, "O efeito estufa é um fenômeno relacionado a:", {"Resfriamento global", "Aquecimento atmosférico", "Buraco na camada de ozônio", "Chuvas ácidas"}, 1},
    {2, 3, "Qual o símbolo químico do elemento Ferro?", {"F", "Fe", "Ir", "Fo"}, 1},
    {2, 3, "O que define um ser vivo como autótrofo?", {"Come carne", "Produz o próprio alimento", "Vive na água", "É parasita"}, 1},
    {2, 3, "Qual a velocidade da luz no vácuo (aproximada)?", {"300 km/s", "300.000 km/s", "3.000 km/s", "30.000 km/s"}, 1},

    // Nível 3
    {3, 3, "Plantas produzem oxigênio a partir de:", {"Nitrogênio", "Glicose", "Luz e CO2", "Água"}, 2},
    {3, 3, "Qual a principal função do DNA?", {"Produzir energia", "Armazenar info genética", "Transportar oxigênio", "Digerir alimentos"}, 1},
    {3, 3, "A Primeira Lei de Newton também é conhecida como:", {"Lei da Gravidade", "Lei da Inércia", "Ação e Reação", "Conservação de Energia"}, 1},
    {3, 3, "O que caracteriza uma ligação química covalente?", {"Ganho de elétrons", "Compartilhamento de elétrons", "Perda de elétrons", "Atração magnética"}, 1},
    {3, 3, "Qual a função celular dos ribossomos?", {"Respiração", "Síntese de proteínas", "Transporte", "Armazenamento"}, 1},
    {3, 3, "Na termodinâmica, a entropia mede o quê?", {"Energia total", "Grau de desordem", "Calor específico", "Pressão"}, 1},
    {3, 3, "Quem desenvolveu a Teoria da Relatividade Geral?", {"Isaac Newton", "Albert Einstein", "Stephen Hawking", "Marie Curie"}, 1},

    // === MATEMÁTICA (4) ===
    // Nível 1
    {1, 4, "Quanto é a raiz quadrada de 144?", {"10", "12", "14", "16"}, 1},
    {1, 4, "Qual o valor de 2 elevado ao cubo?", {"4", "6", "8", "9"}, 2},
    {1, 4, "Quanto é o resultado de 7 vezes 8?", {"49", "54", "56", "63"}, 2},
    {1, 4, "Quantos graus possui um ângulo reto?", {"45°", "90°", "180°", "360°"}, 1},
    {1, 4, "O que define um número primo?", {"É par", "Divisível por 1 e por si mesmo", "Termina em 5", "É múltiplo de 3"}, 1},
    {1, 4, "Quanto é 15% de 200?", {"15", "20", "30", "45"}, 2},
    {1, 4, "Qual a área de um quadrado com lado de 5cm?", {"10cm²", "20cm²", "25cm²", "50cm²"}, 2},

    // Nível 2
    {2, 4, "Um triângulo de lados 3, 4 e 5 é:", {"Equilátero", "Isósceles", "Retângulo", "Obtuso"}, 2},
    {2, 4, "A soma dos ângulos internos de um triângulo é:", {"90°", "180°", "270°", "360°"}, 1},
    {2, 4, "Qual é a fórmula da área de um círculo?", {"2 * Pi * r", "Pi * r²", "Base * Altura", "L²"}, 1},
    {2, 4, "Em um triângulo retângulo, a hipotenusa é:", {"O menor lado", "O lado oposto ao ângulo reto", "A altura", "A base"}, 1},
    {2, 4, "Como se calcula o volume de um cubo de lado 'a'?", {"a²", "a³", "4 * a", "6 * a²"}, 1},
    {2, 4, "Resolva a equação simples: 2x + 4 = 10.", {"x = 2", "x = 3", "x = 4", "x = 5"}, 1},
    {2, 4, "O que caracteriza uma Progressão Aritmética (PA)?", {"Razão multiplicada", "Razão somada constante", "Números aleatórios", "Soma de quadrados"}, 1},

    // Nível 3
    {3, 4, "Qual o valor de Pi (aproximado)?", {"3.14", "3.15", "3.10", "3.16"}, 0},
    {3, 4, "O Teorema de Pitágoras é aplicado em triângulos:", {"Equiláteros", "Retângulos", "Isósceles", "Acutângulos"}, 1},
    {3, 4, "O que é um logaritmo de um número?", {"Sua raiz", "O expoente de uma base", "Seu dobro", "Sua metade"}, 1},
    {3, 4, "Qual a derivada da função f(x) = x²?", {"x", "2x", "x³", "2"}, 1},
    {3, 4, "A trigonometria estuda principalmente:", {"Círculos", "Relações nos triângulos", "Funções afins", "Probabilidade"}, 1},
    {3, 4, "O que é uma matriz na matemática?", {"Um gráfico", "Uma tabela de elementos", "Uma equação", "Um vetor único"}, 1},
    {3, 4, "Como se calcula o determinante de uma matriz 2x2 [[a,b],[c,d]]?", {"a+d - (b+c)", "ad - bc", "ab - cd", "ac - bd"}, 1}
};

static const int internalDBCount = sizeof(internalDB) / sizeof(internalDB[0]);

const DBQuestion* GetInternalQuestions() {
    return internalDB;
}

int GetInternalQuestionsCount() {
    return internalDBCount;
}