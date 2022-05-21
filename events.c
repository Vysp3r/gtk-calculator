#include "events.h"

//Add the value of the button to the end (widget: the button, data: the buttonData associated with the current button)
void add_text(GtkButton *widget, gpointer data) {
    buttonData *current = data;
    GtkText *entry = current->entry;
    GtkEntryBuffer *entryBuffer = gtk_text_get_buffer(entry);
    char *output = (char *) malloc(1 + strlen(gtk_entry_buffer_get_text(entryBuffer)) + strlen(current->value));
    strcpy(output, gtk_entry_buffer_get_text(entryBuffer));
    strcat(output, current->value);
    gtk_entry_buffer_set_text(entryBuffer, output, (int) strlen(output));
    free(output);
}

//Delete the last value from the GtkText component (widget: the button, data: the buttonData associated with the current button)
void del_text(GtkButton *widget, gpointer data) {
    buttonData *current = data;
    GtkText *entry = current->entry;
    GtkEntryBuffer *entryBuffer = gtk_text_get_buffer(entry);
    int length = (int) strlen(gtk_entry_buffer_get_text(entryBuffer));
    if (length > 0) {
        char output[--length];
        for (int i = 0; i < length; ++i)
            output[i] = gtk_entry_buffer_get_text(entryBuffer)[i];
        gtk_entry_buffer_set_text(entryBuffer, output, length);
    }
}

//Calculate the result of the GtkText component (widget: the button, data: the buttonData associated with the current button)
void get_result(GtkButton *widget, gpointer data) {

}