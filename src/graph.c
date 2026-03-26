#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FIXME: redo error handling cause bad??
// TODO: remove print_graph later, only for debugging purposes

void vector_init(Vector *vector) {
    vector->size = 0;
    vector->capacity = 4; // Initial capacity
    vector->data = malloc(vector->capacity * sizeof(Edge));
    if (!vector->data) {
        perror("Failed to allocate memory for vector data");
        exit(EXIT_FAILURE);
    }
}

void vector_push_back(Vector *vector, Edge e) {
    if (vector->size >= vector->capacity) {
        vector->capacity *= 2;
        vector->data = realloc(vector->data, vector->capacity * sizeof(Edge));
        if (!vector->data) {
            perror("Failed to reallocate memory for vector data");
            exit(EXIT_FAILURE);
        }
    }
    vector->data[vector->size++] = e;
}

void vector_free(Vector *vector) {
    for (int i = 0; i < vector->size; i++) {
        free(vector->data[i].name);
    }
    free(vector->data);
}

Graph *create_graph(int verticies) {
    Graph *graph = malloc(sizeof(Graph));
    graph->verticies_num = verticies;
    graph->adj = malloc(verticies * sizeof(Vector));
    for (int i = 0; i < verticies; i++) {
        vector_init(&graph->adj[i]);
    }
    return graph;
}

void add_edge(Graph *graph, int from, int to, double weight, char *name) {
    Edge e;
    e.to = to;
    e.weight = weight;
    e.name = strdup(name);
    if (!e.name) {
        perror("Failed to allocate memory for edge name");
        exit(EXIT_FAILURE);
    }
    Edge reverse_e;
    reverse_e.to = from;
    reverse_e.weight = weight;
    reverse_e.name = strdup(name);
    if (!reverse_e.name) {
        perror("Failed to allocate memory for reverse edge name");
        exit(EXIT_FAILURE);
    }
    vector_push_back(&graph->adj[from], e);
    vector_push_back(&graph->adj[to], reverse_e);
}

void free_graph(Graph *graph) {
    for (int i = 0; i < graph->verticies_num; i++) {
        vector_free(&graph->adj[i]);
    }
    free(graph->adj);
    free(graph);
}

void print_graph(Graph *graph) {
    for (int i = 0; i < graph->verticies_num; i++) {
        printf("Vertex %d:\n", i);
        for (int j = 0; j < graph->adj[i].size; j++) {
            Edge e = graph->adj[i].data[j];
            printf("  -> %d (weight: %.2f, name: %s)\n", e.to, e.weight,
                   e.name);
        }
    }
}
