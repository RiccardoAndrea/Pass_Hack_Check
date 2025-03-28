#include "header.h"


int confronta_password(const char *file_dizionario, const char *password_target) {
    FILE *file = fopen(file_dizionario, "r");
    if (!file) {
        printf("Errore nell'aprire il file del dizionario\n");
        return -1;
    }
    printf("🔎 Tentativo dizionario...\n");
    char parola[100]; // buffer per la parola letta dal dizionario
    int trovato = 0;

    // Creiamo un array per contenere tutte le parole (per esempio 100000 parole)
    const int MAX_PAROLE = 10000;
    char dizionario[MAX_PAROLE][100];
    int n_parole = 0;

    // Leggiamo tutte le parole nel dizionario
    while (fgets(parola, sizeof(parola), file)) {
        parola[strcspn(parola, "\n")] = '\0'; // rimuovere il newline dalla parola
        if (n_parole < MAX_PAROLE) {
            strcpy(dizionario[n_parole], parola);
            n_parole++;
        } else {
            // Quando il dizionario è pieno, esegui la ricerca parallela
            #pragma omp parallel for shared(dizionario, n_parole, trovato) 
            for (int i = 0; i < n_parole; i++) {
                if (strcmp(dizionario[i], password_target) == 0) {
                    #pragma omp critical
                    {
                        printf("password crakkata: %s\n",password_target);
                        trovato = 1;  // Impostiamo "trovato" se la password è trovata
                    }
                }
            }

            // Se trovato, termina immediatamente
            if (trovato) {
                break;
            }

            // Resetta il dizionario e prepara per il prossimo blocco
            n_parole = 0;
        }
    }

    // Ultima ricerca con il dizionario rimanente
    if (!trovato) {
        #pragma omp parallel for shared(dizionario, n_parole, trovato) 
        for (int i = 0; i < n_parole; i++) {
            if (strcmp(dizionario[i], password_target) == 0) {
                #pragma omp critical
                {
                    trovato = 1;  // Impostiamo "trovato" se la password è trovata
                }
            }
        }
    }

    fclose(file);
    return trovato;
}
