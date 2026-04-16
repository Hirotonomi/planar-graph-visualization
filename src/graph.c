#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: remove print_graph later, only for debugging purposes
//---------------VECTORS----------------
/**
 * Initializes a vector with an initial capacity of 4.
 * @param vector The vector to initialize.
 */
void vector_init(Vector *vector) {
    vector->size = 0;
    vector->capacity = 4; // Initial capacity
    vector->data = malloc(vector->capacity * sizeof(Edge));
    if (!vector->data) {
        perror("Failed to allocate memory for vector data");
        exit(EXIT_FAILURE);
    }
}

/**
 * Adds an edge to the vector, resizing by factor of 2 if necessary.
 * @param vector The vector to add the edge to.
 * @param e The edge to add.
 */
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

/**
 * Frees the memory allocated for the vector, including the edge names.
 * @param vector The vector to free.
 */
void vector_free(Vector *vector) {
    for (int i = 0; i < vector->size; i++) {
        free(vector->data[i].name);
    }
    free(vector->data);
}

//---------------GRAPH----------------
/**
 * Creates a graph with the specified number of vertices.
 * @param vertices The number of vertices in the graph.
 * @return A pointer to the created graph.
 */
Graph *create_graph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    if (!graph) {
        perror("Failed to allocate memory for graph");
        exit(EXIT_FAILURE);
    }
    graph->vertices_num = vertices;
    graph->adj = malloc(vertices * sizeof(Vector));
    if (!graph->adj) {
        perror("Failed to allocate memory for graph adjacency list");
        free(graph);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < vertices; i++) {
        vector_init(&graph->adj[i]);
    }
    return graph;
}

/**
 * Adds an edge to the graph, creating a reverse edge for undirected graphs.
 * @param graph The graph to add the edge to.
 * @param from The starting vertex of the edge.
 * @param to The ending vertex of the edge.
 * @param weight The weight of the edge.
 * @param name The name of the edge.
 */
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

/**
 * Frees the memory allocated for the graph, including all edges and their
 * names.
 * @param graph The graph to free.
 */
void free_graph(Graph *graph) {
    for (int i = 0; i < graph->vertices_num; i++) {
        vector_free(&graph->adj[i]);
    }
    free(graph->adj);
    free(graph);
}

/**
 * Prints the graph for debugging purposes.
 * @param graph The graph to print.
 */
void print_graph(Graph *graph) {
    for (int i = 0; i < graph->vertices_num; i++) {
        printf("Vertex %d:\n", i);
        for (int j = 0; j < graph->adj[i].size; j++) {
            Edge e = graph->adj[i].data[j];
            printf("  -> %d (weight: %.2f, name: %s)\n", e.to, e.weight,
                   e.name);
        }
    }
}
