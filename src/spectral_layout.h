#ifndef SPECTRAL_LAYOUT_H
#define SPECTRAL_LAYOUT_H

#include "graph.h"

double** create_laplacian_matrix(Graph *graph);

void print_laplacian_matrix(double **L, int n);

void free_matrix(double **matrix, int n);

void solve_using_spectral_layout(Graph *graph);
#endif 