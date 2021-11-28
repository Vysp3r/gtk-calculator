#ifndef GTKSANDBOX_WIDGETS_H
#define GTKSANDBOX_WIDGETS_H

struct line *find(int id, void *user_data);

void insertWidgets(void *user_data);

void createLines(int amount, void *user_data);

void freeMemory(void *user_data);

//A list of widgets
struct widget {
    GtkWidget *wid;
    struct widget *next;
};

//A list of GtkBox identified with an ID which contains a list of widgets
struct line {
    int id;
    GtkWidget *box;
    struct widget *head;
    struct line *next;
};

typedef struct {
    GtkWidget *main;
    struct line *head;
} lines;

#endif //GTKSANDBOX_WIDGETS_H
