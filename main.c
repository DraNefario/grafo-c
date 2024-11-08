#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

int main() {
    const char *arquivo_pontos = "pontos.txt";
    const char *arquivo_vizinhos = "vizinhos.txt";
    const char *arquivo_saida = "saida.bin";

    printf("Gerando arquivo binário...\n");
    gerar_binario(arquivo_pontos, arquivo_vizinhos, arquivo_saida);

    // Verificando se o arquivo binário foi criado corretamente
    FILE *fp_test = fopen(arquivo_saida, "rb");
    if (!fp_test) {
        printf("Erro ao abrir o arquivo binário.\n");
        return -1;
    }
    fclose(fp_test);

    // Criar o grafo e carregar os dados binários
    Grafo grafo;
    carregar_grafo(&grafo, arquivo_saida);

    if (grafo.num_pontos == 0) {
        printf("Erro: Nenhum ponto carregado.\n");
        return -1;
    }

    printf("Pontos carregados:\n");
    for (int i = 0; i < grafo.num_pontos; i++) {
        printf("Ponto %d: ID = %s, Coordenadas = (%.2f, %.2f)\n", 
               i, grafo.pontos[i].id, grafo.pontos[i].x, grafo.pontos[i].y);
    }

    char origem[2], destino[2];
    printf("Digite o ponto de origem: ");
    scanf(" %1s", origem);  
    printf("Digite o ponto de destino: ");
    scanf(" %1s", destino);  
    
    // Verificando se os pontos de origem e destino são válidos
    int origem_idx = -1, destino_idx = -1;
    for (int i = 0; i < grafo.num_pontos; i++) {
        if (strcmp(grafo.pontos[i].id, origem) == 0) {
            origem_idx = i;
        }
        if (strcmp(grafo.pontos[i].id, destino) == 0) {
            destino_idx = i;
        }
    }

    if (origem_idx == -1 || destino_idx == -1) {
        printf("Ponto de origem ou destino inválido.\n");
        return -1;
    }

    // Executar o algoritmo de Dijkstra
    printf("Executando Dijkstra...\n");
    dijkstra(&grafo, origem, destino);

    // Liberar a memória alocada
    free(grafo.pontos);
    free(grafo.vizinhos);

    return 0;
}
