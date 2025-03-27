# Password Security Checker

## Descrizione
Il progetto "Password Security Checker" è un'applicazione sviluppata in C che permette di testare la sicurezza di una password tramite vari metodi di attacco. L'applicazione offre tre modalità di attacco: **Brute Force**, **Dizionario** e **Social Engineering**. L'utente può inserire una password e scegliere il tipo di attacco per verificare la robustezza della password. Il sistema supporta il parallelismo tramite **OpenMP**, migliorando l'efficienza e la velocità delle operazioni, specialmente in scenari di attacchi complessi.

## Funzionalità
- **Brute Force**: Prova tutte le combinazioni possibili per indovinare la password.
- **Dizionario**: Confronta la password con un dizionario predefinito di parole comuni.
- **Social Engineering**: Effettua un attacco basato su informazioni personali comuni per cercare di indovinare la password. (Vedi note sulla terminologia sotto.)

## Tecnologie Utilizzate
- **Linguaggio di Programmazione**: C
- **OpenMP**: Per il parallelismo e l'ottimizzazione delle prestazioni nelle operazioni di attacco.
- **GTK+ 3.0**: Per la creazione dell'interfaccia grafica dell'applicazione.
- **GCC**: Compilatore per la compilazione del codice C con supporto OpenMP.

## Come Usare
1. Compila il progetto utilizzando il comando:
   ```bash
   gcc -o main main.c attacco_dizionario.c brute_force.c gui.c libreria.c social_engineering_force_attack.c -I. $(pkg-config --cflags --libs gtk+-3.0) -fopenmp

