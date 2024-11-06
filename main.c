/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define NUM_NOS 12
#define INF INT_MAX

typedef struct{
    char letra;
    float x, y;
}No;

typedef struct{
    int dest;
    double peso;
}Aresta;

typedef struct{
    Aresta arestas[NUM_NOS];
    int num_arestas;
}ListaDeArestas;

typedef struct{
    ListaDeArestas
adj[NUM_NOS];
}Grafo;

double dist(No a, No b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void inicia_grafo(Grafo *grafo){
    for (int i = 0; i < NUM_NOS; i++){
        grafo->adj[i].num_arestas = 0;
    }
}

void add_aresta(Grafo *grafo, int src, int dest, double peso){
    grafo->adj[src].arestas[grafo->adj[src].num_arestas++] = (Aresta)
    { dest, peso }
    
     grafo->adj[dest].arestas[grafo->adj[dest].num_arestas++] = (Aresta)
    { src, peso }
}

int menor_distancia(double dist[], int visitado[]){
    double min = INF;
    int min_index = -1;
    
    for (int i = 0; i < NUM_NOS; i++){
        if(!visited[] && dist[i] < min){
            min = dist[i];
            min_index = i;
        }
    }
    
    return min_index;
    
}

void dijkstra(Grafo * grafo, int src, int dest, double dist[], int prev[]){
    int visited[NUM_NOS] = {0};
    
    for (int i = 0; i < NUM_NOS; i++){
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[src] = 0;
    
    for(int i = 0; i < NUM_NOS - 1; i++){
        int u = menor_distancia(dist, visited);
        if(u == -1) break;
        
        visited[u] = 1;
    
    
        for (int j = 0; j < grafo->adj[u].num_arestas; j++){
            int v =
            grafo->adj[u].arestas[j].dest;
            double peso = 
            grafo->adj[u].arestas[j].peso;
            if(!visited[v] && dist[u] + peso < dist[v]){
                dist[v] = 
                dist[u] + peso;
                prev[v] = u;
            }
        }
    }
}

void imprimir_caminho(int prev[], int j){
    if (j == -1) return;
    imprimir_caminho(prev, prev[j]);
    print("%c ", 'A' + j);
}




int main() {
    FILE *file;
    int size = 0;

    // Alocação inicial
    array = (Carro *)malloc(capacidade * sizeof(Carro));
    if (array == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Carregando o arquivo
    file = fopen("vizinhos.txt", "r");
    if (file != NULL) {
        char linha[MAX_LENGTH_LINHA];
        while (fgets(linha, MAX_LENGTH_LINHA, file) != NULL) {
            linha[strcspn(linha, "\n")] = '\0';
            strncpy(array[size].arestas, linha);

            size++;
            if (size >= capacidade) {
                capacidade += INCREMENTO_TAMANHO;
                array = (Grafo *)realloc(array, capacidade * sizeof(grafo));
                if (array == NULL) {
                    printf("Erro ao alocar memória.\n");
                    fclose(file);
                    return 1;
                }
            }
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo vizinhos.txt\n");
    }
}















