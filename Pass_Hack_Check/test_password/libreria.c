#include "header.h"
int lunghezza_vettore_stringhe(const char *vettore[]) {
    int count = 0;
    while (vettore[count] != NULL) {
        count++;
    }
    return count;
}


