#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graph.h"
#include "node.h"

double** create_laplacian_matrix(Graph *graph) {
    int n = graph->vertices_num;
    double **laplacian_matrix = malloc(n * sizeof(double *));
    if (laplacian_matrix == NULL) {
        perror("Blad alokacji pamieci macierzy Laplace'a - wiersze");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        laplacian_matrix[i] = calloc(n, sizeof(double));
        if (laplacian_matrix[i] == NULL) {
            perror("Blad alokacji pamieci macierzy Laplace'a - kolumny");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 1; i <= n; i++) {           
        double degree = 0.0;
        for (int k = 0; k < graph->adj[i].size; k++) {
            int j = graph->adj[i].data[k].to;       
            laplacian_matrix[i-1][j-1] -= 1.0;                          
            degree += 1.0;
        }
        laplacian_matrix[i-1][i-1] += degree;                         
    }
    return laplacian_matrix;
}


static void identity_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        memset(matrix[i], 0, n * sizeof(double));
        matrix[i][i] = 1.0;
    }
}

static void copy_matrix(double **source, double **destination, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            destination[i][j] = source[i][j];
}

void print_matrix(double **matrix, int n) {
    printf("\n--- Macierz Laplace'a (%d x %d) ---\n", n, n);
    
    printf("     ");
    for (int j = 1; j <= n; j++) {
        printf("[%d]      ", j);
    }
    printf("\n");

    for (int i = 1; i <= n; i++) {
        printf("[%d] ", i);
        for (int j = 1; j <= n; j++) {
            printf("%8.3f ", matrix[i-1][j-1]); 
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

GraphLayout*/ void solve_using_spectral_layout(Graph *graph)
{
    if (graph == NULL || graph->vertices_num < 2) {
        fprintf(stderr, "Błąd: Graf jest pusty lub ma za mało wierzchołków do spectral layout.\n");
        // return NULL;
    }

    double **L = create_laplacian_matrix(graph);
    //(debug)
    int n = graph->vertices_num;
    print_laplacian_matrix(L, n);
    //debug

    free_matrix(L, n);
    // free_eigenvectors(eigenvectors, 2);   
    // return layout;
}