#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "node.h"

double** create_laplacian_matrix(Graph *graph) {
    int vertices_num = graph->vertices_num;
    double **laplacian_matrix = malloc(vertices_num * sizeof(double *));
    if (laplacian_matrix == NULL) {
        perror("Blad alokacji pamieci macierzy Laplace'a - wiersze");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < vertices_num; i++) {
        laplacian_matrix[i] = calloc(vertices_num, sizeof(double));
        if (laplacian_matrix[i] == NULL) {
            perror("Blad alokacji pamieci macierzy Laplace'a - kolumny");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 1; i <= vertices_num; i++) {           
        double degree = 0.0;
        for (int k = 0; k < graph->adj[i].size; k++) {
            int j = graph->adj[i].data[k].to;       
            laplacian_matrix[i-1][j-1] -= 1;                          
            degree += 1;
        }
        laplacian_matrix[i-1][i-1] += degree;                         
    }
    return laplacian_matrix;
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

static void identity_matrix(double **empty_matrix, int n) {
    for (int i = 0; i < n; i++) {
        memset(empty_matrix[i], 0, n * sizeof(double));   // troche przekombinowane ale działa :p
        empty_matrix[i][i] = 1.0;
    }
}

static void copy_matrix(double **src, double **target, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            target[i][j] = src[i][j];
}

void free_matrix(double **matrix, int n) {
    if (matrix == NULL) return;
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

/*GraphLayout*/ void solve_using_spectral_layout(Graph *graph)
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