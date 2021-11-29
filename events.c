#include <stdio.h>
#include <gtk/gtk.h>
#include "widgets.h" //Widgets Handler
#include "events.h" //Events Handler

//WARNING - This file is prone to change a lot each updates, so no worries about how the first version looks, it will improve over time

//Handle what happens when you click on the digits and operators buttons
void onClick_NumPad(GtkButton *btn, void *user_data) {
    lines *appLines = (lines *) user_data;
    GtkWidget *entryWidget = find(0, appLines)->head->wid;
    //Check if the textbox is exist
    if (entryWidget != NULL) {
        GtkEntryBuffer *entry = gtk_entry_get_buffer(GTK_ENTRY (entryWidget));
        //IDEA - Add a bool to lines and use it has a state (true if the entry is showing something that was not set by the user)
        if (strcmp(gtk_entry_buffer_get_text(entry), "Malformed expression") == 0 ||
            strcmp(gtk_entry_buffer_get_text(entry), "Conversion error occurred") == 0 ||
            strcmp(gtk_entry_buffer_get_text(entry), "The value provided was out of range") == 0)
            gtk_entry_buffer_set_text(entry, gtk_button_get_label(btn), 1);
        else {
            char *output = (char *) malloc(
                    1 + strlen(gtk_entry_buffer_get_text(entry)) + strlen(gtk_button_get_label(btn)));
            strcpy(output, gtk_entry_buffer_get_text(entry));
            strcat(output, gtk_button_get_label(btn));
            gtk_entry_buffer_set_text(entry, output, strlen(output));
            free(output);
        }
    }
}

//Handle what happens when you click on the equal button
void onClick_Equal(GtkButton *btn, void *user_data) {
    lines *appLines = (lines *) user_data;
    GtkWidget *entryWidget = find(0, appLines)->head->wid;
    //Check if the textbox is exist
    if (entryWidget != NULL) {
        GtkEntryBuffer *entry = gtk_entry_get_buffer(GTK_ENTRY (find(0, appLines)->head->wid));
        char operators[4] = {'/', '*', '+', '-'};
        int operatorsCount = 0;
        int *operatorsLocation = (int *) malloc(0 * sizeof(int));
        bool error = false;
        const char *input = gtk_entry_buffer_get_text(entry);
        char *output = (char *) malloc(1 + strlen(input));
        strcpy(output, input);
        //Check how many operators the input contains
        for (int i = 0; i < strlen(input); ++i)
            for (int j = 0; j < 4; ++j)
                if (input[i] == operators[j])
                    operatorsCount++;
        //Check if the input contains operators
        if (operatorsCount) {
            operatorsLocation = (int *) realloc(operatorsLocation, operatorsCount);
            int counter = 0;
            //Stores the operators location in an array
            for (int i = 0; i < strlen(input); ++i)
                for (int j = 0; j < 4; ++j)
                    if (input[i] == operators[j])
                        operatorsLocation[counter++] = i;
        }
        //Check if the input start with an operator
        for (int j = 0; j < 4; ++j)
            if (input[0] == operators[j])
                error = true;
        //Check if the input finish with an operator (if there's no error)
        if (!error)
            for (int j = 0; j < 4; ++j)
                if (input[strlen(input) - 1] == operators[j])
                    error = true;
        //Check if the input does not have two operator one after another (if there's no error)
        if (!error)
            if (1 != operatorsCount)
                for (int i = 0; i < operatorsCount; ++i)
                    for (int j = 0; j < operatorsCount; ++j)
                        if (operatorsLocation[i] + 1 == operatorsLocation[j] ||
                            operatorsLocation[i] - 1 == operatorsLocation[j])
                            error = true;
        //Split the expression and convert the parts in long then store them in an array
        long data[operatorsCount + 1];
        if (!error && operatorsCount) {
            char *token;
            char *eptr;
            char *temp = (char *) malloc(1 + strlen(input));
            int counter = 0;
            strcpy(temp, input);
            token = strtok(temp, operators);
            while (token != NULL) {
                data[counter] = strtol(token, &eptr, 10);
                /* If the result is 0, test for an error */
                if (data[counter] == 0) {
                    /* If a conversion error occurred, display a message and exit */
                    if (errno == EINVAL) {
                        strcpy(output, "Conversion error occurred");
                        token = NULL;
                    }
                }

                /* If the result is equal to LONG_MIN or LONG_MAX, test for a range error */
                if (data[counter] == LONG_MIN || data[counter] == LONG_MAX) {
                    /* If the value provided was out of range, display a warning message */
                    if (errno == ERANGE) {
                        strcpy(output, "The value provided was out of range");
                        token = NULL;
                    }
                }
                token = strtok(NULL, operators);
                counter++;
            }
        }
        //Resolve the expression
        if (!error && operatorsCount){
            //Add verification to verifiy if the value is within range for the long type
            long result = 0;
            for (int i = 0; i < operatorsCount; ++i) {
                //Addition
                if(input[operatorsLocation[i]] == 43){
                    result = data[i] + data[i+1];
                }
                //Subtraction
                if(input[operatorsLocation[i]] == 45){
                    result = data[0] - data[i+1];
                }
                // Division
                if(input[operatorsLocation[i]] == 47){
                    result = data[0] / data[i+1];
                }
                // Multiplication
                if(input[operatorsLocation[i]] == 42){
                    result = data[0] * data[i+1];
                }
            }
            //DANGEROUS
            sprintf(output,"%ld",result);
        }
        //Throw an error message if the expression contains errors
        if (error)
            strcpy(output, "Malformed expression");
        //Output the result
        gtk_entry_buffer_set_text(entry, output, strlen(output));
        //Deallocating dynamic memory
        free(operatorsLocation);
        free(output);
    }
}

//Handle what happens when you click on the back button
void onClick_Back(GtkButton *btn, void *user_data) {
    lines *appLines = (lines *) user_data;
    GtkWidget *entryWidget = find(0, appLines)->head->wid;
    //Check if the textbox is exist
    if (entryWidget != NULL) {
        GtkEntryBuffer *entry = gtk_entry_get_buffer(GTK_ENTRY (find(0, appLines)->head->wid));
        //Check if the textbox is not empty
        if (strlen(gtk_entry_buffer_get_text(entry)) > 0) {
            int length = strlen(gtk_entry_buffer_get_text(entry)) - 1;
            char output[length];
            //Create a char array with one char less to store all the char of the input except the last one
            for (int i = 0; i < length; ++i)
                output[i] = gtk_entry_buffer_get_text(entry)[i];
            gtk_entry_buffer_set_text(entry, output, length);
        }
    }
}