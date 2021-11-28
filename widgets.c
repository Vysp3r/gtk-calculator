#include <stdio.h>
#include <gtk/gtk.h>
#include "widgets.h" //Widgets Handler
#include "events.h" //Events Handler

struct line *find(int id, void *user_data) {
    lines *appLines = (lines *) user_data;
    struct line *current = appLines->head;

    if (appLines->head == NULL) {
        return NULL;
    }

    while (current->id != id) {
        if (current->next == NULL)
            return NULL;
        else
            current = current->next;
    }

    return current;
}

void insertWidgets(void *user_data) {
    lines *appLines = (lines *) user_data;

    for (int i = 0; i < 6; ++i) {
        int amount = 4;
        if (i == 0) amount = 1;
        if (i == 5) amount = 2;

        struct line *currentLine = find(i, appLines);
        currentLine->head = NULL;

        for (int x = 0; x < amount; ++x) {
            struct widget *link = (struct widget *) malloc(sizeof(struct widget));
            char *widgetsLabel[5][4] = {{"7", "8", "9", "/"},
                                        {"4", "5", "6", "*"},
                                        {"1", "2", "3", "+"},
                                        {"0", ".", "%", "-"},
                                        {"<", "=", NULL, NULL}};
            if (i == 0) {
                link->wid = gtk_entry_new();
                gtk_widget_set_can_focus(link->wid, false);
            } else {
                link->wid = gtk_button_new_with_label(widgetsLabel[i - 1][x]);
                void (*fun_ptr)(GtkButton *, gpointer) = &onClick_NumPad;
                if (strcmp(widgetsLabel[i - 1][x], "<") == 0) fun_ptr = &onClick_Back;
                else if (strcmp(widgetsLabel[i - 1][x], "=") == 0) fun_ptr = &onClick_Equal;
                g_signal_connect (link->wid, "clicked", G_CALLBACK(fun_ptr), appLines);
            }
            if (currentLine != NULL) gtk_box_append(GTK_BOX (currentLine->box), link->wid);
            link->next = currentLine->head;
            currentLine->head = link;
        }
    }
}

void createLines(int amount, void *user_data) {
    lines *appLines = (lines *) user_data;
    appLines->head = NULL;

    for (int i = 0; i < amount; ++i) {
        struct line *link = (struct line *) malloc(sizeof(struct line));
        link->id = i;
        link->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
        link->next = appLines->head;
        appLines->head = link;

        gtk_box_set_homogeneous(GTK_BOX (link->box), true);
        gtk_widget_set_margin_top(link->box, 20);
        if (i == 5) gtk_widget_set_margin_bottom(link->box, 20);
        gtk_widget_set_margin_start(link->box, 20);
        gtk_widget_set_margin_end(link->box, 20);
        gtk_box_append(GTK_BOX (appLines->main), link->box);
    }
}

void freeMemory(void *user_data) {
    lines *appLines = (lines *) user_data;

    struct line *currentLine = appLines->head;
    while (currentLine) {
        struct line *tempLine = currentLine;

        struct widget *currentWidget = currentLine->head;
        while (currentWidget) {
            struct widget *tempWidget = currentWidget;
            currentWidget = currentWidget->next;
            free(tempWidget);
        }

        currentLine = currentLine->next;
        free(tempLine);
    }

    free(appLines);
    appLines = NULL;
}
