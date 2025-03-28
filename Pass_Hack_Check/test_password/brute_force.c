#include "header.h"
#define MAX_LENGHT 3
#define MAX_LEN 5  // Lunghezza massima della password brute-forzata
#define CHARSET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!?#@/+-[]{}_"

void generate_combinations(char *attempt, int index, int max_length, const char *target, int *found) {
    if (*found) return; // Se abbiamo trovato la password, interrompiamo

    if (index == max_length) {
        attempt[index] = '\0';
        //printf("crackpass e: %s\n",attempt);
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

void generate_combinations_with_base(char *attempt, const char *base, int base_len, int index, int max_length, const char *target, int *found) {
    if (*found) return;  // Se la password è stata trovata, fermiamo l'esecuzione

    // Se raggiungiamo la lunghezza massima della parte aggiunta
    if (index == max_length) {
        attempt[base_len + index] = '\0';  // Terminiamo la stringa
        printf("crackpass e: %s\n",attempt);
        if (strcmp(attempt, target) == 0) {  // Controlliamo se la combinazione è corretta
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

    // Proviamo tutti i caratteri del charset
    for (int i = 0; i < strlen(CHARSET); i++) {
        attempt[base_len + index] = CHARSET[i];  // Aggiungiamo un carattere alla stringa
        generate_combinations_with_base(attempt, base, base_len, index + 1, max_length, target, found);  // Chiamata ricorsiva
    }
}

int brute_force_attack_with_base(const char *base, const char *target_password) {
    double start = omp_get_wtime();
    int found = 0;
    int base_len = strlen(base);
    char attempt[MAX_LENGHT + 1 + base_len];  // Spazio per la base più la parte aggiunta

    printf("🔎 Tentativo di brute-force con aggiunta a base...\n");
    omp_set_num_threads(4);  // Imposto il numero di thread per il parallelismo

    // Parallelizzo il brute-force per tutte le lunghezze della parte aggiunta, da 1 a MAX_LEN
    #pragma omp parallel for shared(found) private(attempt)
    for (int len = 1; len <= MAX_LENGHT; len++) {
        if (!found) {
            strncpy(attempt, base, base_len);  // Copio la base iniziale nella variabile di tentativo
            generate_combinations_with_base(attempt, base, base_len, 0, len, target_password, &found);  // Chiamata ricorsiva per generare le combinazioni
        }
    }

    double end = omp_get_wtime();
    printf("Tempo impiegato: %f secondi\n", end - start);

    return found ? 1 : 0;  // Se abbiamo trovato la password, ritorna 1, altrimenti 0
}

