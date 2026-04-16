#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

double** create_laplacian_matrix(Graph *graph) {
    int n = graph->vertices_num;
    double **L = malloc(n * sizeof(double *));
    if (L == NULL) {
        perror("Blad alokacji pamieci macierzy Laplace'a - wiersze");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        L[i] = calloc(n, sizeof(double));
        if (L[i] == NULL) {
            perror("Blad alokacji pamieci macierzy Laplace'a - kolumny");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 1; i <= n; i++) {           
        double degree = 0.0;
        for (int k = 0; k < graph->adj[i].size; k++) {
            int j = graph->adj[i].data[k].to;       
            L[i-1][j-1] -= 1;                          
            degree += 1;
        }
        L[i-1][i-1] += degree;                         
    }
    return L;
}

void print_laplacian_matrix(double **L, int n) {
    printf("\n--- Macierz Laplace'a (%d x %d) ---\n", n, n);
    
    // Nagłówek kolumn
    printf("     ");
    for (int j = 1; j <= n; j++) {
        printf("[%d]      ", j);
    }
    printf("\n");

    for (int i = 1; i <= n; i++) {
        printf("[%d] ", i);
        for (int j = 1; j <= n; j++) {
            printf("%8.3f ", L[i-1][j-1]); 
        }
        printf("\n");
    }
    printf("------------------------------------\n\n");
}

void free_matrix(double **matrix, int n) {
    if (matrix == NULL) return;
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}