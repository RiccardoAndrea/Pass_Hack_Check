#include "header.h"

#define MAX_LEN 5  // Lunghezza massima della password brute-forzata
#define CHARSET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!?#@/+-[]{}"

void generate_combinations(char *attempt, int index, int max_length, const char *target, int *found) {
    if (*found) return; // Se abbiamo trovato la password, interrompiamo

    if (index == max_length) {
        attempt[index] = '\0';
        if (strcmp(attempt, target) == 0) {
            printf("\n[+] Password trovata: %s\n", attempt);
            #pragma omp critical
            {
                if (!*found) {
                    *found = 1;
                }
            }
        }
        return;
    }

    for (int i = 0; i < strlen(CHARSET); i++) {
        attempt[index] = CHARSET[i];
        generate_combinations(attempt, index + 1, max_length, target, found);
    }
}

int brute_force_attack(const char *target_password) {
    double start = omp_get_wtime();
    char attempt[MAX_LEN + 1];
    int found = 0;

    printf("🔎 Tentativo di brute-force...\n");
    omp_set_num_threads(4);// setto il numero di thread
    #pragma omp parallel for shared(found) private(attempt)
    for (int len = 1; len <= MAX_LEN; len++) {
        if (!found) generate_combinations(attempt, 0, len, target_password, &found);
    }
    double end = omp_get_wtime();
    printf("Tempo impiegato: %f secondi\n", end - start);
    if (found) 
        return 1;
    else
        return 0;
}
