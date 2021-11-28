#include <stdio.h>
#include <gtk/gtk.h>
#include "widgets.h" //Widgets Handler
#include "events.h" //Events Handler

void onClick_NumPad(GtkButton *btn, void *user_data) {
    lines *appLines = (lines *) user_data;
    GtkWidget *entryWidget = find(0, appLines)->head->wid;
    if (entryWidget != NULL) {
        GtkEntryBuffer *entry = gtk_entry_get_buffer(GTK_ENTRY (entryWidget));
        char *output = (char *) malloc(
                1 + strlen(gtk_entry_buffer_get_text(entry)) + strlen(gtk_button_get_label(btn)));
        strcpy(output, gtk_entry_buffer_get_text(entry));
        strcat(output, gtk_button_get_label(btn));
        gtk_entry_buffer_set_text(entry, output, strlen(output));
        free(output);
    }
}

void onClick_Equal(GtkButton *btn, void *user_data) {
    lines *appLines = (lines *) user_data;
    GtkWidget *entryWidget = find(0, appLines)->head->wid;
    if (entryWidget != NULL) {
        GtkEntryBuffer *entry = gtk_entry_get_buffer(GTK_ENTRY (find(0, appLines)->head->wid));
        bool valid = false;
        char *output;
        if (!valid)
            output = "Malformed expression";
        gtk_entry_buffer_set_text(entry, output, strlen(output));
    }
}

void onClick_Back(GtkButton *btn, void *user_data) {
    lines *appLines = (lines *) user_data;
    GtkWidget *entryWidget = find(0, appLines)->head->wid;
    if (entryWidget != NULL) {
        GtkEntryBuffer *entry = gtk_entry_get_buffer(GTK_ENTRY (find(0, appLines)->head->wid));
        if (strlen(gtk_entry_buffer_get_text(entry)) > 0) {
            ulong length = strlen(gtk_entry_buffer_get_text(entry)) - 1;
            char output[length];
            for (int i = 0; i < length; ++i)
                output[i] = gtk_entry_buffer_get_text(entry)[i];
            gtk_entry_buffer_set_text(entry, output, length);
        }
    }
}