#include "gui.h"
#include "header.h"  // Per le funzioni di attacco (brute force, dizionario, social engineering)
#include <gtk/gtk.h>
#include <string.h>

// Callback per il cambio di selezione nel menu a tendina.
void on_attack_changed(GtkComboBoxText *combo, gpointer user_data) {
    AppWidgets *app = (AppWidgets *)user_data;
    const gchar *selected = gtk_combo_box_text_get_active_text(combo);
    // Mostra i campi extra solo se l'attacco scelto è "Social Engineering"
    if (selected && strcmp(selected, "Social Engineering") == 0) {
        gtk_widget_show(app->grid_extra);
    } else {
        gtk_widget_hide(app->grid_extra);
    }
}

// Callback per il pulsante "Hackera".
void on_hack_clicked(GtkWidget *widget, gpointer data) {
    AppWidgets *app = (AppWidgets *)data;
    const char *password = gtk_entry_get_text(GTK_ENTRY(app->entry_password));
    const char *selected_attack = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(app->combo_attack));
    int result = 0;

    if (!selected_attack) return;

    if (strcmp(selected_attack, "Brute Force") == 0) {
        result = brute_force_attack(password);
    } else if (strcmp(selected_attack, "Dizionario") == 0) {
        result = confronta_password("10-milion-password.txt", password);
    } else if (strcmp(selected_attack, "Social Engineering") == 0) {
        // Recupera i dati extra inseriti dall'utente per Social Engineering
        const char *info[8];
        info[0] = gtk_entry_get_text(GTK_ENTRY(app->entry_name));
        info[1] = gtk_entry_get_text(GTK_ENTRY(app->entry_surname));
        info[2] = gtk_entry_get_text(GTK_ENTRY(app->entry_day));
        info[3] = gtk_entry_get_text(GTK_ENTRY(app->entry_month));
        info[4] = gtk_entry_get_text(GTK_ENTRY(app->entry_year));
        info[5] = gtk_entry_get_text(GTK_ENTRY(app->entry_city));
        info[6] = gtk_entry_get_text(GTK_ENTRY(app->entry_pet));
        info[7] = NULL;
        result = social_engigneering_force_attack(info, password);
    }

    if (result)
        gtk_label_set_text(GTK_LABEL(app->label_result), "🔴 Password Hackerata!");
    else
        gtk_label_set_text(GTK_LABEL(app->label_result), "🟢 Password Sicura!");
}

// Funzione per avviare l'interfaccia grafica.
void start_gui(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Creazione della finestra principale.
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Password Security Checker");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Layout verticale
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Campo di input per la password.
    GtkWidget *entry_password = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_password), "Inserisci la password...");
    gtk_box_pack_start(GTK_BOX(vbox), entry_password, FALSE, FALSE, 0);

    // Menu a tendina per il tipo di attacco.
    GtkWidget *combo_attack = gtk_combo_box_text_new();
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_attack), NULL, "Brute Force");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_attack), NULL, "Dizionario");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_attack), NULL, "Social Engineering");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_attack), 0);
    gtk_box_pack_start(GTK_BOX(vbox), combo_attack, FALSE, FALSE, 0);

    // Container per i campi extra (per Social Engineering)
    GtkWidget *grid_extra = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid_extra), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_extra), 5);
    
    // Campi extra: Nome, Cognome, Giorno, Mese, Anno, Città, Nome animale
    GtkWidget *label_name = gtk_label_new("Nome:");
    GtkWidget *entry_name = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid_extra), label_name, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_extra), entry_name, 1, 0, 1, 1);

    GtkWidget *label_surname = gtk_label_new("Cognome:");
    GtkWidget *entry_surname = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid_extra), label_surname, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_extra), entry_surname, 1, 1, 1, 1);

    GtkWidget *label_day = gtk_label_new("Giorno:");
    GtkWidget *entry_day = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid_extra), label_day, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_extra), entry_day, 1, 2, 1, 1);

    GtkWidget *label_month = gtk_label_new("Mese:");
    GtkWidget *entry_month = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid_extra), label_month, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_extra), entry_month, 1, 3, 1, 1);

    GtkWidget *label_year = gtk_label_new("Anno:");
    GtkWidget *entry_year = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid_extra), label_year, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_extra), entry_year, 1, 4, 1, 1);

    GtkWidget *label_city = gtk_label_new("Città:");
    GtkWidget *entry_city = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid_extra), label_city, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_extra), entry_city, 1, 5, 1, 1);

    GtkWidget *label_pet = gtk_label_new("Nome animale:");
    GtkWidget *entry_pet = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid_extra), label_pet, 0, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_extra), entry_pet, 1, 6, 1, 1);

    // Nascondi inizialmente i campi extra.
    gtk_widget_hide(grid_extra);
    gtk_box_pack_start(GTK_BOX(vbox), grid_extra, FALSE, FALSE, 0);

    // Bottone "Hackera"
    GtkWidget *button_hack = gtk_button_new_with_label("🔓 Hackera");
    gtk_box_pack_start(GTK_BOX(vbox), button_hack, FALSE, FALSE, 0);

    // Label per il risultato
    GtkWidget *label_result = gtk_label_new("🔍 In attesa...");
    gtk_box_pack_start(GTK_BOX(vbox), label_result, FALSE, FALSE, 0);

    // Alloca la struttura AppWidgets e assegna i widget creati.
    AppWidgets *app = g_malloc(sizeof(AppWidgets));
    app->entry_password = entry_password;
    app->combo_attack = combo_attack;
    app->label_result = label_result;
    app->grid_extra = grid_extra;
    app->entry_name = entry_name;
    app->entry_surname = entry_surname;
    app->entry_day = entry_day;
    app->entry_month = entry_month;
    app->entry_year = entry_year;
    app->entry_city = entry_city;
    app->entry_pet = entry_pet;

    // Collega il segnale per il cambio di selezione nel menu a tendina.
    g_signal_connect(combo_attack, "changed", G_CALLBACK(on_attack_changed), app);
    // Collega il segnale per il bottone "Hackera".
    g_signal_connect(button_hack, "clicked", G_CALLBACK(on_hack_clicked), app);

    gtk_widget_show_all(window);
    // Nascondi i campi extra se la selezione iniziale non è Social Engineering.
    const gchar *sel = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_attack));
    if (sel && strcmp(sel, "Social Engineering") != 0) {
        gtk_widget_hide(grid_extra);
    }

    gtk_main();
}
