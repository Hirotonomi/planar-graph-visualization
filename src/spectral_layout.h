#ifndef LAPLACIAN_H
#define LAPLACIAN_H

#include "graph.h"

/**
 * @brief Creates a Laplacian matrix for a given graph.
 * * The Laplacian matrix L is defined as L = D - A, where:
 * - D is the degree matrix (diagonal matrix with vertex degrees).
 * - A is the adjacency matrix.
 * * @param graph Pointer to the Graph structure.
 * @return double** Pointer to the allocated n x n Laplacian matrix.
 */
double** create_laplacian_matrix(Graph *graph);

/**
 * @brief Prints the Laplacian matrix to the standard output.
 * * @param L The Laplacian matrix (2D array).
 * @param n Number of vertices (dimensions of the matrix).
 */
void print_laplacian_matrix(double **L, int n);

/**
 * @brief Frees the memory allocated for a 2D matrix.
 * * @param matrix The matrix to be freed.
 * @param n Number of rows in the matrix.
 */
void free_matrix(double **matrix, int n);

#endif // LAPLACIAN_H