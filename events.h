#ifndef GTKCALCULATOR_EVENTS_H
#define GTKCALCULATOR_EVENTS_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <adwaita.h>

void add_text(GtkButton *widget, gpointer data);

void del_text(GtkButton *widget, gpointer data);

void get_result(GtkButton *widget, gpointer data);

typedef struct {
    GtkButton *button;
    GtkText *entry;
    char *value;
    char *name;
} buttonData;

#endif //GTKCALCULATOR_EVENTS_H
