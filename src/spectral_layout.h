#ifndef SPECTRAL_LAYOUT_H
#define SPECTRAL_LAYOUT_H

#include "graph.h"

double** create_laplacian_matrix(Graph *graph);
void print_matrix(double **L, int n);
static void copy_matrix(double **src, double **target, int n);
static void identity_matrix(double **empty_matrix, int n);
static void jacobi_eigen(double **symmetric_matrix_A, double **eigenvector_matrix_V, int n);
void free_matrix(double **matrix, int n);

GraphLayout* solve_using_spectral_layout(Graph *graph);
#endif 