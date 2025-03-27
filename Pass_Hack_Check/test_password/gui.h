#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>

// Struttura per contenere i widget dell'interfaccia, inclusi i campi extra.
typedef struct {
    GtkWidget *entry_password;
    GtkWidget *combo_attack;
    GtkWidget *label_result;
    GtkWidget *grid_extra;
    GtkWidget *entry_name;
    GtkWidget *entry_surname;
    GtkWidget *entry_day;
    GtkWidget *entry_month;
    GtkWidget *entry_year;
    GtkWidget *entry_city;
    GtkWidget *entry_pet;
} AppWidgets;

// Funzione per avviare l'interfaccia grafica.
void start_gui(int argc, char *argv[]);

#endif // GUI_H
