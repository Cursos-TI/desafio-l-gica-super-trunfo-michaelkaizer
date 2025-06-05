#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    int populacao;
    float area;
    double pib;
    int pontos_turisticos;
} Cidade;

typedef struct {
    char pais[50];
    char estado;
    int numero;
    Cidade cidade;
    float densidade;
    double pib_per_capita;
    double super_poder;
} Carta;

char estados[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
Cidade cidades[8][4] = {
    { {"São Paulo", 12300000, 1521.11, 699.28, 35}, {"Campinas", 1220000, 795.43, 66.3, 12}, {"Santos", 433000, 280.67, 56.7, 8}, {"Ribeirão Preto", 720000, 650.9, 39.2, 14} },
    { {"Rio de Janeiro", 6748000, 1200.27, 341.3, 40}, {"Niterói", 513000, 133.9, 28.5, 11}, {"Petrópolis", 307000, 795.9, 12.7, 15}, {"Campos dos Goytacazes", 510000, 4032.2, 25.4, 10} },
    { {"Belo Horizonte", 2525000, 331.4, 88.6, 18}, {"Juiz de Fora", 573000, 1286.9, 21.2, 9}, {"Ouro Preto", 74000, 1245.3, 8.4, 20}, {"Uberlândia", 713000, 4567.4, 47.6, 16} },
    { {"Curitiba", 1969000, 434.9, 93.2, 21}, {"Londrina", 575000, 1650.5, 30.7, 7}, {"Maringá", 430000, 680.8, 29.4, 9}, {"Cascavel", 332000, 2100.1, 18.3, 6} },
    { {"Porto Alegre", 1483000, 496.8, 81.1, 17}, {"Caxias do Sul", 523000, 1650.7, 25.6, 8}, {"Pelotas", 346000, 1626.4, 15.2, 5}, {"Santa Maria", 285000, 1790.5, 10.8, 4} },
    { {"Salvador", 2885000, 706.8, 62.9, 25}, {"Feira de Santana", 619000, 1233.6, 17.7, 7}, {"Ilhéus", 158000, 1841.8, 6.4, 10}, {"Vitória da Conquista", 343000, 3204.3, 14.2, 5} },
    { {"Fortaleza", 2687000, 314.9, 49.8, 22}, {"Sobral", 213000, 2062.9, 11.3, 5}, {"Juazeiro do Norte", 275000, 2493.4, 9.7, 6}, {"Crato", 133000, 1179.3, 5.4, 7} },
    { {"Recife", 1666000, 218.4, 57.6, 30}, {"Olinda", 393000, 43.6, 9.5, 25}, {"Caruaru", 371000, 920.1, 12.1, 8}, {"Petrolina", 360000, 4383.5, 13.6, 10} }
};

Carta criar_carta(char pais[], char estado, int numero) {
    Carta carta;
    strcpy(carta.pais, pais);
    carta.estado = estado;
    carta.numero = numero;
    int estado_index = estado - 'A';
    carta.cidade = cidades[estado_index][numero - 1];
    carta.densidade = carta.cidade.populacao / carta.cidade.area;
    carta.pib_per_capita = (carta.cidade.pib * 1e9) / carta.cidade.populacao;
    carta.super_poder = carta.cidade.populacao +
                        carta.cidade.area +
                        carta.cidade.pib +
                        carta.cidade.pontos_turisticos +
                        carta.pib_per_capita +
                        (1.0 / carta.densidade);
    return carta;
}

void exibir_carta(Carta carta) {
    printf("\n====== Carta da Cidade ======\n");
    printf("País: %s\n", carta.pais);
    printf("Estado: %c\n", carta.estado);
    printf("Cidade: %s\n", carta.cidade.nome);
    printf("População: %d habitantes\n", carta.cidade.populacao);
    printf("Área: %.2f km²\n", carta.cidade.area);
    printf("PIB: R$ %.2f bilhões\n", carta.cidade.pib);
    printf("Pontos turísticos: %d\n", carta.cidade.pontos_turisticos);
    printf("Densidade populacional: %.2f hab/km²\n", carta.densidade);
    printf("PIB per capita: R$ %.2f\n", carta.pib_per_capita);
    printf("Super Poder: %.2f\n", carta.super_poder);
}

double obter_valor_atributo(Carta carta, int atributo) {
    switch (atributo) {
        case 1: return carta.cidade.populacao;
        case 2: return carta.cidade.area;
        case 3: return carta.cidade.pib;
        case 4: return carta.cidade.pontos_turisticos;
        case 5: return carta.densidade;
        default: return 0;
    }
}

void mostrar_nome_atributo(int atributo) {
    switch (atributo) {
        case 1: printf("População"); break;
        case 2: printf("Área"); break;
        case 3: printf("PIB"); break;
        case 4: printf("Pontos turísticos"); break;
        case 5: printf("Densidade demográfica"); break;
    }
}

void comparar_multiplos_atributos(Carta c1, Carta c2, int atributo1, int atributo2) {
    double valor1_c1 = obter_valor_atributo(c1, atributo1);
    double valor1_c2 = obter_valor_atributo(c2, atributo1);
    double valor2_c1 = obter_valor_atributo(c1, atributo2);
    double valor2_c2 = obter_valor_atributo(c2, atributo2);

    printf("\nComparando atributos:\n");
    printf("%s vs %s\n", c1.pais, c2.pais);

    printf("\nAtributo 1: "); mostrar_nome_atributo(atributo1); printf("\n");
    printf("%s: %.2f | %s: %.2f\n", c1.cidade.nome, valor1_c1, c2.cidade.nome, valor1_c2);

    int vencedor1;
    if (atributo1 == 5) vencedor1 = (valor1_c1 < valor1_c2) ? 1 : (valor1_c1 > valor1_c2) ? 2 : 0;
    else vencedor1 = (valor1_c1 > valor1_c2) ? 1 : (valor1_c1 < valor1_c2) ? 2 : 0;

    printf("Resultado: ");
    if (vencedor1 == 1) printf("%s venceu\n", c1.cidade.nome);
    else if (vencedor1 == 2) printf("%s venceu\n", c2.cidade.nome);
    else printf("Empate!\n");

    printf("\nAtributo 2: "); mostrar_nome_atributo(atributo2); printf("\n");
    printf("%s: %.2f | %s: %.2f\n", c1.cidade.nome, valor2_c1, c2.cidade.nome, valor2_c2);

    int vencedor2;
    if (atributo2 == 5) vencedor2 = (valor2_c1 < valor2_c2) ? 1 : (valor2_c1 > valor2_c2) ? 2 : 0;
    else vencedor2 = (valor2_c1 > valor2_c2) ? 1 : (valor2_c1 < valor2_c2) ? 2 : 0;

    printf("Resultado: ");
    if (vencedor2 == 1) printf("%s venceu\n", c1.cidade.nome);
    else if (vencedor2 == 2) printf("%s venceu\n", c2.cidade.nome);
    else printf("Empate!\n");

    double soma1 = valor1_c1 + valor2_c1;
    double soma2 = valor1_c2 + valor2_c2;

    printf("\nSoma dos atributos:\n");
    printf("%s: %.2f | %s: %.2f\n", c1.cidade.nome, soma1, c2.cidade.nome, soma2);

    printf("\nResultado final: ");
    if (soma1 > soma2) printf("%s venceu a rodada!\n", c1.cidade.nome);
    else if (soma2 > soma1) printf("%s venceu a rodada!\n", c2.cidade.nome);
    else printf("Empate!\n");
}

int menu_atributo(int excluido) {
    int opcao;
    while (1) {
        printf("\nEscolha um atributo:\n");
        if (excluido != 1) printf("1 - População\n");
        if (excluido != 2) printf("2 - Área\n");
        if (excluido != 3) printf("3 - PIB\n");
        if (excluido != 4) printf("4 - Pontos turísticos\n");
        if (excluido != 5) printf("5 - Densidade demográfica\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        if (opcao >= 1 && opcao <= 5 && opcao != excluido) break;
        printf("Opção inválida. Tente novamente.\n");
    }
    return opcao;
}

int main() {
    char pais1[50], pais2[50], estado1, estado2;
    int cidade1, cidade2;

    printf("Escolha a primeira carta:\n");
    printf("Digite o nome do País: ");
    scanf("%s", pais1);
    printf("Digite a letra do estado (A-H): ");
    scanf(" %c", &estado1);
    printf("Digite o número da cidade (1-4): ");
    scanf("%d", &cidade1);

    Carta carta1 = criar_carta(pais1, estado1, cidade1);
    exibir_carta(carta1);

    printf("\nEscolha a segunda carta:\n");
    printf("Digite o nome do País: ");
    scanf("%s", pais2);
    printf("Digite a letra do estado (A-H): ");
    scanf(" %c", &estado2);
    printf("Digite o número da cidade (1-4): ");
    scanf("%d", &cidade2);

    Carta carta2 = criar_carta(pais2, estado2, cidade2);
    exibir_carta(carta2);

    printf("\nAgora selecione dois atributos diferentes para comparar:\n");
    int atributo1 = menu_atributo(0);
    int atributo2 = menu_atributo(atributo1);

    comparar_multiplos_atributos(carta1, carta2, atributo1, atributo2);

    return 0;
}
