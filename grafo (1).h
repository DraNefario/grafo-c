#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>

#ifndef MAX_PONTOS
#define MAX_PONTOS 12
#endif

#ifndef MAX_VIZINHOS
#define MAX_VIZINHOS 20
#endif

// Estrutura para representar um ponto
typedef struct {
    char id[2];       // ID do ponto (ex: "A", "B")
    double x, y;      // Coordenadas
    char rua1[100];   // Rua 1
    char rua2[100];   // Rua 2
} Ponto;

// Estrutura para representar uma conexão
typedef struct {
    char origem[2];   // Ponto de origem
    char destino[2];  // Ponto de destino
    char rua[100];    // Nome da rua
} Conexao;

// Estrutura para o grafo
typedef struct {
    Ponto *pontos;        // Agora é um ponteiro, permitindo alocação dinâmica
    Conexao *vizinhos;    // Agora é um ponteiro, permitindo alocação dinâmica
    int num_pontos;       // Número total de pontos
    int num_vizinhos;     // Número total de vizinhos/conexões
} Grafo;

// Funções para manipulação do grafo
void gerar_binario(const char *pontos, const char *vizinhos, const char *arquivo_saida);
void carregar_grafo(Grafo *grafo, const char *arquivo_bin);
void dijkstra(Grafo *grafo, const char *origem, const char *destino);

#endif // GRAFO_H
