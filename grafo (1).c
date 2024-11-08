#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"

#define INF 99999999.0

void gerar_binario(const char *arquivo_pontos, const char *arquivo_vizinhos, const char *arquivo_saida) {
    FILE *fp_pontos = fopen(arquivo_pontos, "r");
    FILE *fp_vizinhos = fopen(arquivo_vizinhos, "r");
    FILE *fp_saida = fopen(arquivo_saida, "wb");

    if (!fp_pontos || !fp_vizinhos || !fp_saida) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    Grafo grafo;
    grafo.num_pontos = 0;
    // Ler pontos
    while (fscanf(fp_pontos, "%1s %lf %lf", grafo.pontos[grafo.num_pontos].id,
                  &grafo.pontos[grafo.num_pontos].x, &grafo.pontos[grafo.num_pontos].y) != EOF) {
        grafo.num_pontos++;
        if (grafo.num_pontos >= MAX_PONTOS) {
            printf("Erro: número máximo de pontos excedido.\n");
            break;
        }
    }

    printf("Número de pontos lidos: %d\n", grafo.num_pontos);

    grafo.num_vizinhos = 0;
    // Ler vizinhos
    while (fscanf(fp_vizinhos, "%1s %1s %s", grafo.vizinhos[grafo.num_vizinhos].origem,
                  grafo.vizinhos[grafo.num_vizinhos].destino, grafo.vizinhos[grafo.num_vizinhos].rua) != EOF) {
        grafo.num_vizinhos++;
        if (grafo.num_vizinhos >= MAX_VIZINHOS) {
            printf("Erro: número máximo de vizinhos excedido.\n");
            break;
        }
    }

    printf("Número de vizinhos lidos: %d\n", grafo.num_vizinhos);

    // Salvar o grafo no arquivo binário
    fwrite(&grafo.num_pontos, sizeof(int), 1, fp_saida);
    fwrite(grafo.pontos, sizeof(Ponto), grafo.num_pontos, fp_saida);
    fwrite(&grafo.num_vizinhos, sizeof(int), 1, fp_saida);
    fwrite(grafo.vizinhos, sizeof(Conexao), grafo.num_vizinhos, fp_saida);

    fclose(fp_pontos);
    fclose(fp_vizinhos);
    fclose(fp_saida);
}


void carregar_grafo(Grafo *grafo, const char *arquivo_bin) {
    FILE *fp = fopen(arquivo_bin, "rb");
    if (!fp) {
        printf("Erro ao abrir o arquivo binário.\n");
        return;
    }

    fread(&grafo->num_pontos, sizeof(int), 1, fp);
    if (grafo->num_pontos <= 0 || grafo->num_pontos > MAX_PONTOS) {
        printf("Erro: número de pontos inválido no arquivo binário.\n");
        fclose(fp);
        return;
    }

    grafo->pontos = (Ponto *)malloc(grafo->num_pontos * sizeof(Ponto));
    if (grafo->pontos == NULL) {
        printf("Erro ao alocar memória para os pontos.\n");
        fclose(fp);
        return;
    }

    fread(grafo->pontos, sizeof(Ponto), grafo->num_pontos, fp);

    fread(&grafo->num_vizinhos, sizeof(int), 1, fp);
    if (grafo->num_vizinhos <= 0 || grafo->num_vizinhos > MAX_VIZINHOS) {
        printf("Erro: número de vizinhos inválido no arquivo binário.\n");
        free(grafo->pontos);
        fclose(fp);
        return;
    }

    grafo->vizinhos = (Conexao *)malloc(grafo->num_vizinhos * sizeof(Conexao));
    if (grafo->vizinhos == NULL) {
        printf("Erro ao alocar memória para os vizinhos.\n");
        free(grafo->pontos);
        fclose(fp);
        return;
    }

    fread(grafo->vizinhos, sizeof(Conexao), grafo->num_vizinhos, fp);

    fclose(fp);
}


void dijkstra(Grafo *grafo, const char *origem, const char *destino) {
    double dist[grafo->num_pontos];
    bool visitado[grafo->num_pontos];

    for (int i = 0; i < grafo->num_pontos; i++) {
        dist[i] = INF;
        visitado[i] = false;
    }

    int origem_idx = -1, destino_idx = -1;
    for (int i = 0; i < grafo->num_pontos; i++) {
        if (strcmp(grafo->pontos[i].id, origem) == 0) {
            origem_idx = i;
        }
        if (strcmp(grafo->pontos[i].id, destino) == 0) {
            destino_idx = i;
        }
    }

    if (origem_idx == -1 || destino_idx == -1) {
        printf("Ponto de origem ou destino inválido.\n");
        return;
    }

    dist[origem_idx] = 0;

    for (int i = 0; i < grafo->num_pontos; i++) {
        int u = -1;
        double min_dist = INF;
        for (int j = 0; j < grafo->num_pontos; j++) {
            if (!visitado[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }

        if (u == -1) break;

        visitado[u] = true;

        for (int j = 0; j < grafo->num_vizinhos; j++) {
            if (strcmp(grafo->vizinhos[j].origem, grafo->pontos[u].id) == 0) {
                int v = -1;
                for (int k = 0; k < grafo->num_pontos; k++) {
                    if (strcmp(grafo->pontos[k].id, grafo->vizinhos[j].destino) == 0) {
                        v = k;
                        break;
                    }
                }
                if (v != -1 && dist[u] + 1 < dist[v]) {
                    dist[v] = dist[u] + 1;
                }
            }
        }
    }

    // Imprime a distância do ponto de origem para o ponto de destino
    printf("A distância do ponto %s para o ponto %s é %.2f\n", origem, destino, dist[destino_idx]);
}
