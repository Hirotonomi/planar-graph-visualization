#include "node.h"
#include "fileio.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph* load_graph_from_file(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) {perror("Błąd: Nie udało się otworzyć pliku wejściowego");
        return NULL;
    }

    int vertices_amount = find_max_vertex_id(file);

    if (vertices_amount == 0) {fprintf(stderr, "Błąd: Plik jest pusty lub ma zły format.\n");
        fclose(file);
        return NULL;
    }

    Graph *graph = create_graph(vertices_amount + 1);//TODO contemplate if vector on index 0 of *adj is ok to be perma empty

    char name[256];
    int from, to;
    double weight;

    while (fscanf(file, "%255s %d %d %lf", name, &from, &to, &weight) == 4) {
        add_edge(graph, from, to, weight, name);
    }

    fclose(file);
    return graph;
}
//TODO, dodać sprawdzenie from i to czy liczby są dodatnimi intami
int find_max_vertex_id(FILE *file) {
    if (file == NULL) return 0;

    char name[256];
    int from, to;
    double weight;
    int max_vertex = 0;

    while (fscanf(file, "%255s %d %d %lf", name, &from, &to, &weight) == 4) {
        if (from > max_vertex) max_vertex = from;
        if (to > max_vertex) max_vertex = to;
    }
//potrzebne zawrócić plik, na tym się wyjebałem w jimp1kolos
    rewind(file);
    return max_vertex;
}

void save_layout_human(const char *filepath, GraphLayout *layout) {
    FILE *f = fopen(filepath, "w");
    if (!f) {perror("Nie udało się otworzyć pliku do zapisu");return;}
    
    for (int i = 0; i < layout->count; i++) {
        fprintf(f, "%d %f %f\n", layout->nodes[i].id, layout->nodes[i].x, layout->nodes[i].y);
    }
    
    fclose(f);
    printf("Wyniki zapisano pomyślnie do: %s\n", filepath);
}

void save_layout_binary(const char *filepath, GraphLayout *layout) {
    FILE *f = fopen(filepath, "wb");
    if (!f) {perror("Nie udało się otworzyć pliku do zapisu");return;}

    for (int i = 0; i < layout->count; i++) {
        Node n = layout->nodes[i];
        fwrite(&n.id, sizeof(int), 1, f);      // 4 bytes
        fwrite(&n.x,  sizeof(double), 1, f);   // 8 bytes
        fwrite(&n.y,  sizeof(double), 1, f);   // 8 bytes
    }

    fclose(f);
    printf("Wyniki zapisano pomyślnie do: %s\n", filepath);
}