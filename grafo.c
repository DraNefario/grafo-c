#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

void gerar_binario(const char *pontos, const char *vizinhos, const char *arquivo_saida) {
    FILE *pontos_file = fopen(pontos, "r");
    FILE *vizinhos_file = fopen(vizinhos, "r");

    if (!pontos_file || !vizinhos_file) {
        printf("Erro ao abrir os arquivos de texto.\n");
        if (!pontos_file) {
            printf("Erro ao abrir o arquivo de pontos: %s\n", pontos);
        }
        if (!vizinhos_file) {
            printf("Erro ao abrir o arquivo de vizinhos: %s\n", vizinhos);
        }
        return;
    }

    Grafo grafo;
    grafo.num_pontos = 0;
    grafo.num_vizinhos = 0;

    // Ler os pontos
    while (fscanf(pontos_file, "%49s\n%lf %lf\n%49[^\n]\n%49[^\n]\n",
                  grafo.pontos[grafo.num_pontos].id,
                  &grafo.pontos[grafo.num_pontos].x,
                  &grafo.pontos[grafo.num_pontos].y,
                  grafo.pontos[grafo.num_pontos].rua1,
                  grafo.pontos[grafo.num_pontos].rua2) == 5) {
        grafo.num_pontos++;
        if (grafo.num_pontos >= MAX_PONTOS) break;
    }

    // Ler as conexões
    while (fscanf(vizinhos_file, "%49s\n%49s\n%49[^\n]\n",
                  grafo.vizinhos[grafo.num_vizinhos].origem,
                  grafo.vizinhos[grafo.num_vizinhos].destino,
                  grafo.vizinhos[grafo.num_vizinhos].rua) == 3) {
        grafo.num_vizinhos++;
        if (grafo.num_vizinhos >= MAX_VIZINHOS) break;
    }

    // Criar o arquivo binário
    FILE *output = fopen(arquivo_saida, "wb");
    if (!output) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        fclose(pontos_file);
        fclose(vizinhos_file);
        return;
    }

    // Gravar o número de pontos e conexões no arquivo binário
    fwrite(&grafo.num_pontos, sizeof(int), 1, output);
    fwrite(&grafo.num_vizinhos, sizeof(int), 1, output);

    // Gravar os dados no arquivo binário
    fwrite(grafo.pontos, sizeof(Ponto), grafo.num_pontos, output);
    fwrite(grafo.vizinhos, sizeof(Conexao), grafo.num_vizinhos, output);

    fclose(pontos_file);
    fclose(vizinhos_file);
    fclose(output);

    printf("Arquivo binário gerado com sucesso!\n");
}

void carregar_grafo(Grafo *grafo, const char *arquivo_bin) {
    FILE *arquivo = fopen(arquivo_bin, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo binário.\n");
        return;
    }

    fread(&grafo->num_pontos, sizeof(int), 1, arquivo);
    fread(&grafo->num_vizinhos, sizeof(int), 1, arquivo);

    fread(grafo->pontos, sizeof(Ponto), grafo->num_pontos, arquivo);
    fread(grafo->vizinhos, sizeof(Conexao), grafo->num_vizinhos, arquivo);

    fclose(arquivo);
}

void dijkstra(Grafo *grafo, char origem, char destino) {
    printf("Executando Dijkstra de %c para %c\n", origem, destino);
    // Implementar o algoritmo de Dijkstra aqui
}
