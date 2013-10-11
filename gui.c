/**
 * A set of simple functions for displaying a graphical user interface in C.
 * (Wraps around a much more complex library called GTK.)
 * 
 * Use this in your UCP assignment *as is*. You *do not* need to modify this 
 * code, or even (necessarily) understand how it works.
 * 
 * Author: David Cooper
 */

#include "gui.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <gtk/gtk.h>


/** Constants for the geometry of a window. */
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define PADDING 5


/**
 * Used internally by the addButton function, and the buttonClicked static 
 * function. Contains a callback function and the data to be passed to it.
 */
typedef struct {
    void (*function)(void*);
    void *data;
} Callback;


/**
 * Creates and returns a new GUI window. This window will have space for a set 
 * of buttons on the left, and an area to display text on the right. You must 
 * specify the window title.
 */
Window *createWindow(char *title)
{
    Window *win;
    GtkWidget *pane, *scrollArea, *textView;
    static int init = FALSE;
    
    assert(title != NULL);
    
    if(!init)
    {
        gtk_init(NULL, NULL);
        init = TRUE;
    }

    /* Create window */
    win = (Window*)malloc(sizeof(Window));
    win->gtkWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(win->gtkWindow), DEFAULT_WIDTH, DEFAULT_HEIGHT);
    gtk_window_set_title(GTK_WINDOW(win->gtkWindow), title);
    g_signal_connect(G_OBJECT(win->gtkWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);    
    
    /* Create hbox */
    pane = gtk_hbox_new(FALSE, 0); /*PADDING);*/
    gtk_container_add(GTK_CONTAINER(win->gtkWindow), pane);
    
    /* Create button container (vbox) on the left */
    win->buttonBox = gtk_vbutton_box_new();
    gtk_box_pack_start(GTK_BOX(pane), GTK_WIDGET(win->buttonBox), FALSE, TRUE, 0);    
    gtk_button_box_set_layout(GTK_BUTTON_BOX(win->buttonBox), GTK_BUTTONBOX_START);
    gtk_box_set_spacing(GTK_BOX(win->buttonBox), PADDING);
    gtk_container_set_border_width(GTK_CONTAINER(win->buttonBox), PADDING);
    
    /* Create scroll area on the right */
    scrollArea = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_end(GTK_BOX(pane), scrollArea, TRUE, TRUE, 0);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollArea), 
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrollArea),
                                        GTK_SHADOW_ETCHED_IN);
    
    /* Create text view within the scroll area */
    textView = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(scrollArea), textView);
    win->textBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textView), FALSE);
    
    return win;
}


/**
 * Sets the text displayed by the window. Specifically, this function will 
 * erase whatever text is currently displayed, and copy your new text into the
 * window.
 */
void setText(Window *window, char *newText)
{
    assert(window != NULL);
    assert(newText != NULL);
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(window->textBuffer), newText, -1);
}


/**
 * Not visible outside this file. This is a generic button-click event handler.
 * It's a go-between, between GTK and your assignment code, so that you don't
 * have to deal with GTK widgets directly.
 */
static void buttonClicked(GtkWidget *widget, gpointer data)
{
    Callback *callback = (Callback*)data;
    if(callback->function == NULL)
    {
        gtk_main_quit();
    }
    else
    {
        callback->function(callback->data);
    }
}

/**
 * not visible outside this file. This is a callback for cleaning up after the
 * first callback -- buttonClicked -- defined above.
 */
static void freeCallback(gpointer data, GClosure *closure)
{
    free(data);
}

/**
 * Adds a button to the window. You must specify:
 * window   -- as returned by createWindow.
 * label    -- a piece of text to appear on the button.
 * callback -- a function to be called later, if/when the button is pressed. 
 *             This function will take a void pointer. 
 * data     -- A pointer to a set of data (which can be whatever you like) to 
 *             be passed as a parameter to the callback function, if/when it is
 *             called. This is only means by which you can provide data to your
 *             callback function. (You *will* lose marks for using global
 *             variables.)
 */
void addButton(Window *window, char *label, void (*callback)(void*), void *data) 
{
    GtkWidget *button;
    Callback *callbackDetails;
    
    assert(window != NULL);
    assert(label != NULL);
    
    button = gtk_button_new_with_label(label);
    gtk_container_add(GTK_CONTAINER(window->buttonBox), button);
    
    callbackDetails = (gpointer)malloc(sizeof(Callback));
    callbackDetails->function = callback;
    callbackDetails->data = data;
    
    g_signal_connect_data(
        G_OBJECT(button), "clicked", 
        G_CALLBACK(buttonClicked), (gpointer)callbackDetails, (GClosureNotify)freeCallback, 0);
}

/**
 * Once you have set up the window, using createWindow and addButton, call 
 * runGUI to hand over control to the GUI system. This will display the window
 * and wait for user input (in the form of button presses).
 * 
 * When a button press occurs, the corresponding callback function you 
 * specified before will be called. The callback function itself must complete
 * the task the user wants to accomplish (using its data parameter).
 */
void runGUI(Window *window)
{
    assert(window != NULL);
    gtk_widget_show_all(GTK_WIDGET(window->gtkWindow));
    gtk_main();
}

/**
 * Frees a window. This should be done at the end of the program, once runGUI 
 * has finished.
 */
void freeWindow(Window *window)
{
    free(window);
}


/**
 * Displays an extra window, called a dialog box, with "Cancel" and "Ok" 
 * buttons and one or more spaces for user input. The parameters are as 
 * follows:
 * 
 * window      -- as returned by createWindow.
 * dialogTitle -- the title of the dialog box.
 * nInputs     -- the number of different input strings you want the user to 
 *                enter.
 * properties  -- an array of structs containing information on each input 
 *                space. See the InputProperties struct in gui.h. The length of 
 *                the array must correspond to nInputs.
 * inputs      -- an array of strings to store the user input. The number of 
 *                strings must correspond to nInputs. Each string must have 
 *                enough space for maxLength + 1 bytes (where maxLength is a 
 *                field in the InputProperties struct). Any pre-existing values
 *                will used as the initial values, as displayed when the dialog
 *                box is opened. If you want the inputs to be initially blank, 
 *                you must pass empty strings.
 * 
 * The function will return when the user presses a button -- TRUE for "Ok" or
 * FALSE otherwise. The function will not modify inputs unless the user presses
 * "Ok".
 */
int dialogBox(Window *window, char *dialogTitle, 
              int nInputs, InputProperties *properties, char **inputs)
{
    int i, response;
    GtkWidget *dialog, *contentArea, **entries, *label;
    
    assert(window != NULL);
    assert(dialogTitle != NULL);
    assert(nInputs >= 1);
    assert(properties != NULL);
    assert(inputs != NULL);
    
    /* Create a basic dialog box */
    dialog = gtk_dialog_new_with_buttons(
        dialogTitle,
        GTK_WINDOW(window->gtkWindow),
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
        GTK_STOCK_OK,     GTK_RESPONSE_OK,
        NULL
    );
    
    /* Add labels, text entry and text view widgets to the dialog box. */
    contentArea = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    entries = (GtkWidget**)malloc(nInputs * sizeof(GtkWidget*));
    for(i = 0; i < nInputs; i++)
    {
        assert(inputs[i] != NULL);
        assert(properties[i].maxLength >= 1);
        
        /* Add a label */
        label = gtk_label_new(properties[i].label);
        gtk_box_pack_start(GTK_BOX(contentArea), label, FALSE, TRUE, 0);
        
        if(properties[i].isMultiLine)
        {
            /* For multi-line inputting, we use a GtkTextView embedded inside
             * a GtkScrolledWindow. */
            GtkWidget *entry = gtk_text_view_new();
            gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(entry)),
                                     inputs[i], -1);
            
            entries[i] = gtk_scrolled_window_new(NULL, NULL);
            gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(entries[i]), 
                                           GTK_POLICY_AUTOMATIC,
                                           GTK_POLICY_AUTOMATIC);
            gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(entries[i]),
                                                GTK_SHADOW_IN);
            gtk_container_add(GTK_CONTAINER(entries[i]), entry);
            
            gtk_label_set_mnemonic_widget(GTK_LABEL(label), entry);
            gtk_box_pack_start(GTK_BOX(contentArea), entries[i], TRUE, TRUE, 0);
        }
        else
        {
            /* For single-line inputting, we use a GtkEntry widget by itself. */
            entries[i] = gtk_entry_new();
            gtk_entry_set_max_length(GTK_ENTRY(entries[i]), properties[i].maxLength);
            gtk_entry_set_text(GTK_ENTRY(entries[i]), inputs[i]);
            
            gtk_label_set_mnemonic_widget(GTK_LABEL(label), entries[i]);
            gtk_box_pack_start(GTK_BOX(contentArea), entries[i], FALSE, TRUE, 0);
        }        
    }
    
    /* Run the dialog, and (if "Ok" was pressed) copy and export the text 
     * input. */
    gtk_widget_show_all(dialog);
    response = (GTK_RESPONSE_OK == gtk_dialog_run(GTK_DIALOG(dialog)));
    if(response)
    {
        for(i = 0; i < nInputs; i++)
        {
            if(properties[i].isMultiLine)
            {
                /* To retrieve the multiline text, we need to extract the 
                 * GtkTextView from the GtkScrolledWindow, and then extract a 
                 * GtkTextBuffer from the GtkTextView. The buffer further 
                 * requires us to get start and end iterators in order to 
                 * extract the actual text. Phew! */
                char *in;
                GtkTextIter start, end;
                GtkTextBuffer *buffer = gtk_text_view_get_buffer(
                    GTK_TEXT_VIEW(gtk_bin_get_child(GTK_BIN(entries[i]))));
                gtk_text_buffer_get_bounds(buffer, &start, &end);                
                in = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
                strncpy(inputs[i], in, properties[i].maxLength);
                free(in); /* The extracted text is dynamically allocated too.*/
            }
            else
            {
                /* With GtkEntry, we just call get_text. No dynamic 
                 * allocation -- just a straight copy. */
                strncpy(inputs[i], 
                        gtk_entry_get_text(GTK_ENTRY(entries[i])), 
                        properties[i].maxLength);
            }
        }
    }
    gtk_widget_destroy(dialog);
    free(entries);
    return response;        
}

/**
 * Displays a simple message box window, with a message and a "Close" button.
 */
void messageBox(Window *window, char *message)
{
    GtkWidget *dialog;
    
    assert(window != NULL);
    assert(message != NULL);
    
    dialog = gtk_message_dialog_new(
        GTK_WINDOW(window->gtkWindow),
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_CLOSE,
        NULL
    );
    
    gtk_message_dialog_set_markup(GTK_MESSAGE_DIALOG(dialog), message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);        
}
