#ifndef NODE_H
#define NODE_H

typedef struct Node {
    double x;
    double y;
    int id;
} Node;

// Struktura trzymająca końcowe wyniki położeń wierzchołków
typedef struct {
    int count;   // Liczba wierzchołków
    Node *nodes; // Tablica wierzchołków
} GraphLayout;

#endif
