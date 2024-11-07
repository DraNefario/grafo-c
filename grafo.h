#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>

#define MAX_PONTOS 12
#define MAX_VIZINHOS 20

// Estrutura para representar um ponto
typedef struct {
    char id[2];
    double x, y;
    char rua1[50];
    char rua2[50];
} Ponto;

// Estrutura para representar uma conexão
typedef struct {
    char origem[2];
    char destino[2];
    char rua[50];
} Conexao;

// Estrutura para o grafo
typedef struct {
    Ponto pontos[MAX_PONTOS];
    Conexao vizinhos[MAX_VIZINHOS];
    int num_pontos;
    int num_vizinhos;
} Grafo;

void gerar_binario(const char *pontos, const char *vizinhos, const char *arquivo_saida);
void carregar_grafo(Grafo *grafo, const char *arquivo_bin);
void dijkstra(Grafo *grafo, char origem, char destino);

#endif // GRAFO_H
