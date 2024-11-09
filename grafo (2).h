#ifndef GRAFO_H
#define GRAFO_H

#define MAX_PONTOS 100  // Increased number of points
#define MAX_VIZINHOS 200  // Increased number of neighbors

typedef struct {
    char id[2];       // ID of the point (e.g., "A", "B")
    double x, y;      // Coordinates
    char rua1[100];   // First street name
    char rua2[100];   // Second street name
} Ponto;

typedef struct {
    char origem[2];   // Origin point ID
    char destino[2];  // Destination point ID
    char rua[100];    // Connecting street name
} Conexao;

typedef struct {
    Ponto pontos[MAX_PONTOS];
    Conexao vizinhos[MAX_VIZINHOS];
    int num_pontos;
    int num_vizinhos;
} Grafo;

// Function declarations
void gerar_binario(const char *arquivo_pontos, const char *arquivo_vizinhos, const char *arquivo_saida);
void carregar_grafo(Grafo *grafo, const char *arquivo_bin);
void dijkstra(Grafo *grafo, const char *origem, const char *destino);

#endif // GRAFO_H
