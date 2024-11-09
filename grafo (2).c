#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"

#define INF 99999999.0

// Generates the binary file from text files
void gerar_binario(const char *arquivo_pontos, const char *arquivo_vizinhos, const char *arquivo_saida) {
    FILE *fp_pontos = fopen(arquivo_pontos, "r");
    FILE *fp_vizinhos = fopen(arquivo_vizinhos, "r");
    FILE *fp_saida = fopen(arquivo_saida, "wb");

    if (!fp_pontos || !fp_vizinhos || !fp_saida) {
        printf("Error opening files.\n");
        return;
    }

    Grafo grafo = { .num_pontos = 0, .num_vizinhos = 0 };

    // Read points
    while (fscanf(fp_pontos, "%2s %lf %lf %99s %99s",
                  grafo.pontos[grafo.num_pontos].id,
                  &grafo.pontos[grafo.num_pontos].x,
                  &grafo.pontos[grafo.num_pontos].y,
                  grafo.pontos[grafo.num_pontos].rua1,
                  grafo.pontos[grafo.num_pontos].rua2) != EOF) {
        if (grafo.num_pontos >= MAX_PONTOS) {
            printf("Maximum number of points exceeded.\n");
            break;
        }
        grafo.num_pontos++;
    }

    // Read connections
    while (fscanf(fp_vizinhos, "%2s %2s %99s",
                  grafo.vizinhos[grafo.num_vizinhos].origem,
                  grafo.vizinhos[grafo.num_vizinhos].destino,
                  grafo.vizinhos[grafo.num_vizinhos].rua) != EOF) {
        if (grafo.num_vizinhos >= MAX_VIZINHOS) {
            printf("Maximum number of neighbors exceeded.\n");
            break;
        }
        grafo.num_vizinhos++;
    }

    fwrite(&grafo, sizeof(Grafo), 1, fp_saida);

    fclose(fp_pontos);
    fclose(fp_vizinhos);
    fclose(fp_saida);
}

// Loads graph data from a binary file
void carregar_grafo(Grafo *grafo, const char *arquivo_bin) {
    FILE *fp = fopen(arquivo_bin, "rb");
    if (!fp) {
        printf("Error opening binary file.\n");
        return;
    }
    fread(grafo, sizeof(Grafo), 1, fp);
    fclose(fp);
}

// Calculates Euclidean distance between two points
double calcular_distancia(Ponto p1, Ponto p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// Dijkstra's algorithm to find the shortest path and print instructions
void dijkstra(Grafo *grafo, const char *origem, const char *destino) {
    double dist[MAX_PONTOS];
    int prev[MAX_PONTOS];
    int origem_idx = -1, destino_idx = -1;

    // Initialize distances and find indices for origin and destination
    for (int i = 0; i < grafo->num_pontos; i++) {
        dist[i] = INF;
        prev[i] = -1;
        if (strcmp(grafo->pontos[i].id, origem) == 0) origem_idx = i;
        if (strcmp(grafo->pontos[i].id, destino) == 0) destino_idx = i;
    }

    if (origem_idx == -1 || destino_idx == -1) {
        printf("Invalid start or end point.\n");
        return;
    }

    dist[origem_idx] = 0;

    // Main loop of Dijkstra's algorithm
    for (int i = 0; i < grafo->num_pontos; i++) {
        int u = -1;
        for (int j = 0; j < grafo->num_pontos; j++) {
            if (dist[j] < dist[u]) u = j;
        }

        for (int j = 0; j < grafo->num_vizinhos; j++) {
            if (strcmp(grafo->vizinhos[j].origem, grafo->pontos[u].id) == 0) {
                int v = -1;
                for (int k = 0; k < grafo->num_pontos; k++) {
                    if (strcmp(grafo->pontos[k].id, grafo->vizinhos[j].destino) == 0) {
                        v = k;
                        break;
                    }
                }
                double dist_uv = calcular_distancia(grafo->pontos[u], grafo->pontos[v]);
                if (dist[u] + dist_uv < dist[v]) {
                    dist[v] = dist[u] + dist_uv;
                    prev[v] = u;
                }
            }
        }
    }

    // Print the path and instructions
    printf("Shortest path from %s to %s with instructions:\n", origem, destino);

    // Reconstruct the path from destination to origin
    int path[MAX_PONTOS];
    int path_length = 0;
    int current = destino_idx;

    // Ensure that the destination is reachable
    if (prev[current] == -1 && current != origem_idx) {
        printf("No path found between %s and %s.\n", origem, destino);
        return;
    }

    while (current != origem_idx) {
        path[path_length++] = current;
        current = prev[current];
    }
    path[path_length++] = origem_idx;

    // Print the reconstructed path and the corresponding streets
    for (int i = path_length - 1; i > 0; i--) {
        int current = path[i];
        int next = path[i - 1];

        // Find the street connecting the current and next point
        int found = 0;
        for (int j = 0; j < grafo->num_vizinhos; j++) {
            if (strcmp(grafo->vizinhos[j].origem, grafo->pontos[current].id) == 0 &&
                strcmp(grafo->vizinhos[j].destino, grafo->pontos[next].id) == 0) {
                printf("From %s to %s via %s\n", grafo->pontos[current].id, grafo->pontos[next].id, grafo->vizinhos[j].rua);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Error: No street found between %s and %s\n", grafo->pontos[current].id, grafo->pontos[next].id);
            return;
        }
    }

    printf("Arrived at %s\n", grafo->pontos[path[0]].id);
}
