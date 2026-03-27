#include <stdio.h>
#include <stdlib.h>
#include "node.h"

void save_layout_human(const char *filepath, GraphLayout *layout) {
    FILE *f = fopen(filepath, "w");
    if (!f) {perror("Nie udało się otworzyć pliku do zapisu");return;}
    
    for (int i = 0; i < layout->count; i++) {
        fprintf(f, "%d %f %f\n", layout->nodes[i].id, layout->nodes[i].x, layout->nodes[i].y);
    }
    
    fclose(f);
    printf("Wyniki zapisano pomyślnie do: %s\n", filepath);
}