#ifndef GRAPH_H
#define GRAPH_H

typedef struct Edge {
    int to;
    double weight;
    char *name;
} Edge;

typedef struct Vector {
    Edge *data;
    int size;
    int capacity;
} Vector;

typedef struct Graph {
    int verticies_num;
    Vector *adj;
} Graph;

void vector_init(Vector *vector);
void vector_push_back(Vector *vector, Edge e);
void vector_free(Vector *vector);

Graph *create_graph(int verticies);
void add_edge(Graph *graph, int from, int to, double weight, char *name);
void free_graph(Graph *graph);
void print_graph(Graph *graph); // TODO: for debugging purposes, remove later

#endif
