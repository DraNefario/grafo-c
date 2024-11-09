// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

// Auxiliary program function to generate binary file
void gerar_binario_interactive() {
    char arquivo_pontos[100], arquivo_vizinhos[100], arquivo_saida[100];

    // Prompt the user for input and output filenames
    printf("Enter the filename for points (pontos.txt): ");
    scanf("%99s", arquivo_pontos);
    printf("Enter the filename for neighbors (vizinhos.txt): ");
    scanf("%99s", arquivo_vizinhos);
    printf("Enter the output binary filename (saida.bin): ");
    scanf("%99s", arquivo_saida);

    // Call gerar_binario function
    gerar_binario(arquivo_pontos, arquivo_vizinhos, arquivo_saida);
    printf("Binary file '%s' generated successfully.\n\n", arquivo_saida);
}

// Main program function to find shortest path
void dijkstra_interactive() {
    char arquivo_bin[100], origem[2], destino[2];
    Grafo grafo;

    // Prompt the user for the binary filename
    printf("Enter the binary filename to load (saida.bin): ");
    scanf("%99s", arquivo_bin);

    // Load the graph from the binary file
    carregar_grafo(&grafo, arquivo_bin);

    // Prompt the user for origin and destination points
    printf("Enter the starting point ID (e.g., A): ");
    scanf(" %2s", origem);
    printf("Enter the destination point ID (e.g., E): ");
    scanf(" %2s", destino);

    // Run Dijkstra's algorithm to find the shortest path
    dijkstra(&grafo, origem, destino);
}

// Main interactive menu
void interactive_menu() {
    int choice;

    do {
        printf("City Navigation Program\n");
        printf("1. Generate Binary File from Text Files\n");
        printf("2. Find Shortest Path Between Points\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                gerar_binario_interactive();
                break;
            case 2:
                dijkstra_interactive();
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

int main() {
    interactive_menu();
    return 0;
}

