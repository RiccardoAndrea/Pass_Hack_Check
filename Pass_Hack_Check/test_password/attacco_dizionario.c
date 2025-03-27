#include "header.h"


int apri_file(char * path)
{
  int fd = open(path, O_RDONLY);
  if(fd == -1){
    perror("open");
    return -1;
  }
  printf("File aperto con successo\n");
  return fd;
}


int confronta_password(char *nome_file, const char *password) {
  
  double start = omp_get_wtime();
  int num_threads = omp_get_max_threads();
  
  int fd = apri_file(nome_file);
  if(fd == -1)
    return -1;
  int file_size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  close(fd);
  
  int block_size = file_size / num_threads;
  printf("Numero di thread disponibili: %d\n", num_threads);
  
  int password_trovata = 0;
  
  #pragma omp parallel shared(block_size, file_size, nome_file, password_trovata)
  {
      int fd = apri_file(nome_file);
      if(fd != -1){
        int id_thread = omp_get_thread_num();
        int start_pos = id_thread * block_size;
        int end_pos = (id_thread == num_threads - 1) ? file_size : start_pos + block_size;
        
        lseek(fd, start_pos, SEEK_SET);
        
        printf("Thread %d: Leggo da %ld a %ld\n", id_thread, (long)start_pos, (long)end_pos);

        char buffer[1024];
        char last_line[1024] = ""; 
        int bytes_read;
        int total_bytes_read = 0;
        
        // Variabile per tenere il contenuto concatenato
        char chunk[2048];
        chunk[0] = '\0';
        
        while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            total_bytes_read += bytes_read;
            
            // Concateno last_line e buffer
            snprintf(chunk, sizeof(chunk), "%s%s", last_line, buffer);
            
            // Cerca l'ultima occorrenza di '\n'
            char *last_nl = strrchr(chunk, '\n');
            if(last_nl != NULL) {
                // Termina la stringa alla posizione dell'ultima newline
                *(last_nl + 1) = '\0';
                
                // Salva il resto (dopo l'ultima newline) in last_line per il prossimo ciclo
                strncpy(last_line, last_nl + 1, sizeof(last_line) - 1);
                last_line[sizeof(last_line) - 1] = '\0';
            } else {
                // Nessun newline trovato: l'intero chunk potrebbe essere una riga incompleta
                // Copia tutto in last_line
                strncpy(last_line, chunk, sizeof(last_line) - 1);
                last_line[sizeof(last_line) - 1] = '\0';
                // Non processare il chunk finché non arrivi a un newline
                continue;
            }
            
            // Ora processa tutte le righe complete nel chunk
            char *line = strtok(chunk, "\n");
            while (line != NULL) {
                printf("Riga: %s\n", line);
                if(strcmp(line, password) == 0) {
                    printf("Password trovata!\n");
                    #pragma omp critical
                    {
                        password_trovata = 1;
                    }
                    #pragma omp cancel parallel  
                    break;
                }
                line = strtok(NULL, "\n");
            }
            
            if(password_trovata == 1){
              #pragma omp cancel parallel  
              break; 
            }
            if (start_pos + total_bytes_read >= end_pos) 
                break;
        }
        close(fd);
      } else {
          printf("Errore apertura file nel blocco parallelo\n");
      }
  }
  
  double end = omp_get_wtime();
  printf("Tempo impiegato: %f secondi\n", end - start);
  return password_trovata;
}

