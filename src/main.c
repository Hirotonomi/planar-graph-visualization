#include "graph.h"
#include "utils.h"
#include "node.h"
#include "math.h"
#include "fileio.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>   


typedef struct {
    char *in_file;
    char *out_path;
    char *out_file;
    int algorithm;
    int binary; // 0 if not bin 1 if bin
    int human;  // human readable - 0 if nah 1 if yuh
} Arguments;

int main(int argc, char *argv[]) {
    Arguments args = {0};
    args.in_file = "input.txt";
    args.out_path = ".";
    args.out_file = "output";
    args.algorithm = 1;
    args.binary = 0;
    args.human = 0;

    int opt = 0;
    while ((opt = getopt(argc, argv, "i:o:n:a:bh")) != -1) {
        switch (opt) {
        case 'i':
            args.in_file = optarg;
            break;
        case 'o':
            args.out_path = optarg;
            break;
        case 'n':
            args.out_file = optarg;
            break;
        case 'a':
            args.algorithm = parse_algorithm(optarg);
            if (args.algorithm == -1) {
                fprintf(stderr, "Taki algorytm nie jest obsługiwany\n");
                return EXIT_FAILURE;
            }
            break;
        case 'b':
            args.binary = 1;
            break;
        case 'h':
            args.human = 1;
            break;
        default:
            fprintf(stderr, "Nieznany lub niekompletny argument: -%c\n",
                    optopt);
            return EXIT_FAILURE;
        }
    }
    if (args.binary == 0 && args.human == 0) {
        printf("Nie wybrano formatu wyjściowego, domyślnie ustawiono na "
               "binarny\n");
        args.binary = 1;
    }

    int vertices_amount = find_max_vertex_id(args.in_file);
    
    if (vertices_amount == 0) {
        fprintf(stderr, "Blad: plik ma zły format, mozliwe: 1 lub 0 wierzcholkow, same niedodatnie id wierzcholkow.\n");
        return EXIT_FAILURE;
    }

    printf("Plik wejściowy: %s\n", args.in_file);
    printf("Ścieżka wyjściowa: %s\n", args.out_path);
    printf("Plik wyjściowy: %s\n", args.out_file);
    printf("Algorytm: %d\n", args.algorithm);
    printf("Format binarny: %s\n", args.binary ? "tak" : "nie");
    printf("Czytelny dla człowieka: %s\n", args.human ? "tak" : "nie");
  
    printf("Wczytywanie grafu z pliku: %s...\n", args.in_file);
    Graph *graph = load_graph_from_file(args.in_file, vertices_amount);

    if (graph == NULL) {
        fprintf(stderr, "Błąd: Nie udało się wczytac grafu. Sprawdź czy plik istnieje i ma poprawny format.\n");
        return EXIT_FAILURE;
    }

    printf("Graf wczytany pomyslnie!\n");
    print_graph(graph);

    GraphLayout *layout = NULL;

    if (args.algorithm == 1) {
        //================================================================
        printf("→ Algorytm 1 (Tutte) - dummy layout (tymczasowy)\n");
        layout = malloc(sizeof(GraphLayout));
        if (layout) {
            layout->count = graph->vertices_num;
            layout->nodes = malloc(layout->count * sizeof(Node));
            if (layout->nodes) {
                for (int i = 0; i < layout->count; i++) {
                    layout->nodes[i].id = i;
                    layout->nodes[i].x = i; 
                    layout->nodes[i].y = i; 
                }
            }
        }
        //===============================================================
    }
    else if (args.algorithm == 2) {
        //to delete =============================================
        printf("→ Algorytm 2 (Spectral) - dummy layout\n");
        layout = malloc(sizeof(GraphLayout));
        if (layout) {
            layout->count = graph->vertices_num;
            layout->nodes = malloc(layout->count * sizeof(Node));
            if (layout->nodes) {
                for (int i = 0; i < layout->count; i++) {
                    layout->nodes[i].id = i;
                    layout->nodes[i].x = i * 8.0;
                    layout->nodes[i].y = (i % 2 == 0) ? 0.0 : 10.0;
                }
            }
        }
    }
    //==========================================================

    if (layout == NULL || layout->nodes == NULL) {
        fprintf(stderr, "Błąd: Nie udało się stworzyć layoutu.\n");
        free_graph(graph);
        return EXIT_FAILURE;
    }

    char full_path[512];
    if (args.binary) {
        snprintf(full_path, sizeof(full_path), "%s/%s.bin", args.out_path, args.out_file);
        save_layout_binary(full_path, layout);
    } else if (args.human) {
        snprintf(full_path, sizeof(full_path), "%s/%s.txt", args.out_path, args.out_file);
        save_layout_human(full_path, layout);
    }

    free(layout->nodes);
    free(layout);
    free_graph(graph);
  
    return EXIT_SUCCESS;
}