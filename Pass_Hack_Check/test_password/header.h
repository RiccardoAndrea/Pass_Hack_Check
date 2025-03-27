#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <fcntl.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>


int brute_force_attack(const char *);
int lunghezza_vettore_stringhe(const char **);
void stampa_parallela(const char **);
int confronta_password( char * , const char *);
int social_engigneering_force_attack(const char **, const char * );
#endif // HEADER_H

