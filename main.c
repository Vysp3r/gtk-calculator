/*
 * Author: Charles Malouin (Vysp3r)
 */

#include <stdio.h>
#include <gtk/gtk.h>
#include "widgets.h" //Widgets Handler

static void activate(GtkApplication *app, void *user_data) {
    GtkWidget *window;
    lines *appLines = (lines *) user_data;

    //Create the main window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW (window), 200, 200);

    //Create the main box
    appLines->main = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(appLines->main, 200, 300);
    gtk_window_set_child(GTK_WINDOW (window), appLines->main);

    //Create and insert the widgets
    createLines(6, appLines);
    insertWidgets(appLines);

    gtk_widget_show(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    lines *appLines = (lines *) malloc(sizeof(lines));

    app = gtk_application_new("calculator.siakno.net", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK(activate), appLines);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);
    freeMemory(appLines); //Free all manually allocated memory

    return status;
}
