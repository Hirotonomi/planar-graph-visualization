#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

typedef struct {
    char *in_file;
    char *out_file;
    int algorithm;
    int binary; //0 if not bin 1 if bin
	int human; //human readable - 0 if nah 1 if yuh
} CodeRun;



int main(int argc, char *argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }
	srand((unsigned int)time(NULL));

    CodeRun arguments = {0};
    arguments.in_file = "input";
	arguments.out_file = "output";
	arguments.algorithm = 1;
	arguments.binary = 0;
	arguments.human = 0;

    for (int i = 2; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
			arguments.in_file = argv[++i];

		} else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
			arguments.out_file = argv[++i];

		} else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
			arguments.algorithm = parse_algorithm(argv[++i]);
			
			if (arguments.algorithm == -1){
				fprintf(stderr, "Taki alogorytm nie jest obsługiwany\n");
				return EXIT_FAILURE;
			}
		}  else if (strcmp(argv[i], "-b") == 0) {
			arguments.binary = 1;

		}  else if (strcmp(argv[i], "-h") == 0) {
			arguments.human = 1;

		} else {
			fprintf(stderr, "Nieznany lub niekompletny argument: %s\n", argv[i]);

			return EXIT_FAILURE;
		}
    }

    printf("Plik wejściowy: %s\n", arguments.in_file);
	printf("Plik wyjściowy: %s\n", arguments.out_file);
	printf("Algorytm: %d\n", arguments.algorithm);
	printf("Format binarny: %s\n", arguments.binary ? "tak" : "nie");
	printf("Czytelny dla człowieka: %s\n", arguments.human ? "tak" : "nie");

	

    return EXIT_SUCCESS;
}