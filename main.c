#include "events.h"

static void initialize_components(GtkBuilder *builder, gpointer data) {
    buttonData *buttons = data;

    char *names[] = {"button0", "button1", "button2", "button3", "button4", "button5", "button6", "button7", "button8",
                     "button9", "buttonPlus", "buttonMinus", "buttonMultiply", "buttonDivision", "buttonPi",
                     "buttonLeftParenthesis", "buttonRightParenthesis", "buttonModulo",
                     "buttonPowerTwo", "buttonRoot", "buttonDot", "buttonPercentage", "buttonEqual", "buttonBack"};
    char *values[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "+", "-", "×", "÷", "π", "(", ")", "mod", "²",
                      "√", ".", "%", NULL, NULL};

    for (int i = 0; i < 24; ++i) {
        buttons[i].name = names[i];
        buttons[i].value = values[i];
        buttons[i].entry = (GtkText *) gtk_builder_get_object(builder, "entry");
        buttons[i].button = (GtkButton *) gtk_builder_get_object(builder, names[i]);
        if (values[i] != NULL) {
            g_signal_connect(buttons[i].button, "clicked", G_CALLBACK(add_text), &buttons[i]);
        } else if (i == 22) {
            g_signal_connect(buttons[i].button, "clicked", G_CALLBACK(get_result), &buttons[i]);
        } else if (i == 23) {
            g_signal_connect(buttons[i].button, "clicked", G_CALLBACK(del_text), &buttons[i]);
        }
    }
}

static void activate_cb(GtkApplication *app, gpointer data) {
    /* Construct a GtkBuilder instance and load our UI description */
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../main.ui", NULL);

    /* Connect signal handlers to the constructed widgets. */
    GObject *window = gtk_builder_get_object(builder, "window");
    gtk_window_set_application(GTK_WINDOW (window), app);

    /* Components initialization */
    initialize_components(builder, data);

    /* Show the main window */
    gtk_widget_show(GTK_WIDGET (window));

    /* We do not need the builder anymore */
    g_object_unref(builder);
}

int main(int argc, char *argv[]) {
    buttonData *buttons[24];

    g_autoptr (AdwApplication) app = NULL;

    app = adw_application_new("net.siakno.calculator", G_APPLICATION_FLAGS_NONE);

    adw_style_manager_set_color_scheme(adw_application_get_style_manager(app), ADW_COLOR_SCHEME_DEFAULT);

    g_signal_connect (app, "activate", G_CALLBACK(activate_cb), &buttons);

    return g_application_run(G_APPLICATION (app), argc, argv);
}