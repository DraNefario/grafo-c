#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

int main() {
    // Definir os arquivos de entrada e o arquivo de saída
    const char *arquivo_pontos = "pontos.txt";
    const char *arquivo_vizinhos = "vizinhos.txt";
    const char *arquivo_saida = "saida.bin";

    // Gerar o arquivo binário a partir dos arquivos de pontos e conexões
    gerar_binario(arquivo_pontos, arquivo_vizinhos, arquivo_saida);

    // Criar o grafo e carregar os dados binários
    Grafo grafo;
    carregar_grafo(&grafo, arquivo_saida);

    // Solicitar os pontos de origem e destino
    char origem, destino;
    printf("Digite o ponto de origem: ");
    scanf(" %c", &origem);
    printf("Digite o ponto de destino: ");
    scanf(" %c", &destino);

    // Executar o algoritmo de Dijkstra
    dijkstra(&grafo, origem, destino);

    return 0;
}
