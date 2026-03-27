#include "graph.h"
#include "utils.h"
#include "node.h"
#include "fileio.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


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
    while (opt = getopt(argc, argv, "i:o:n:a:bh"), opt != -1) {
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
                fprintf(stderr, "Taki alogorytm nie jest obsługiwany\n");
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

    printf("Plik wejściowy: %s\n", args.in_file);
    printf("Ścieżka wyjściowa: %s\n", args.out_path);
    printf("Plik wyjściowy: %s\n", args.out_file);
    printf("Algorytm: %d\n", args.algorithm);
    printf("Format binarny: %s\n", args.binary ? "tak" : "nie");
    printf("Czytelny dla człowieka: %s\n", args.human ? "tak" : "nie");
  
    printf("Wczytywanie grafu z pliku: %s...\n", args.in_file);
    Graph *graph = load_graph_from_file(args.in_file);

    if (graph == NULL) {
        fprintf(stderr, "Błąd: Nie udało się wczytać grafu. Sprawdź czy plik istnieje i ma poprawny format.\n");
        return EXIT_FAILURE;
    }

    printf("Graf wczytany pomyslnie!\n");
    print_graph(graph);
    if (args.algorithm==1){

    }
    else if (args.algorithm==2)
    {
        /* code */
    }
    //bez else bo obsługa sprawdzania algorytmu jest wcześniej
    
    free_graph(graph);
  
    return EXIT_SUCCESS;
}
