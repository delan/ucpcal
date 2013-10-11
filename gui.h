/**
 * A set of simple functions for displaying a graphical user interface in C.
 * (Wraps around a much more complex library called GTK.)
 * 
 * Use this in your UCP assignment *as is*. You *do not* need to modify this 
 * code, or even (necessarily) understand how it works.
 * 
 * Note -- to compile gui.c to gui.o, you need to write this:
 * gcc -c gui.c `pkg-config --cflags --libs gtk+-2.0`
 * 
 * Author: David Cooper
 */

#ifndef GUI_H
#define GUI_H

/* A struct representing a GUI Window. You don't need to access its fields, but
 * simply pass pointer to it to the functions declared below. */
typedef struct {
    void *gtkWindow;
    void *buttonBox;
    void *textBuffer;
} Window;

/**
 * An array of InputProperties structs -- one array element for each input 
 * space -- must be passed to the dialogBox function. The fields are as 
 * follows:
 * label       -- a string label (prompt) to be displayed next to the input space.
 * maxLength   -- the maximum number of characters the user can enter.
 * isMultiLine -- TRUE if the user is allowed to enter multiple lines of text;
 *                FALSE if only a single line is required.
 */
typedef struct {
    char *label;
    int maxLength;
    int isMultiLine;
} InputProperties;


/**
 * Creates and returns a new GUI window. This window will have space for a set 
 * of buttons on the left, and an area to display text on the right. You must 
 * specify the window title.
 */
Window *createWindow(char *title);


/**
 * Sets the text displayed by the window. Specifically, this function will 
 * erase whatever text is currently displayed, and copy your new text into the
 * window.
 */
void setText(Window *window, char *newText);


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
void addButton(Window *window, char *label, void (*callback)(void*), void *data);


/**
 * Once you have set up the window, using createWindow and addButton, call 
 * runGUI to hand over control to the GUI system. This will display the window
 * and wait for user input (in the form of button presses).
 * 
 * When a button press occurs, the corresponding callback function you 
 * specified before will be called. The callback function itself must complete
 * the task the user wants to accomplish (using its data parameter).
 */
void runGUI(Window *window);


/**
 * Frees a window. This should be done at the end of the program, once runGUI 
 * has finished.
 */
void freeWindow(Window *window);


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
int dialogBox(Window *window, char *dialogTitle, int nInputs, 
              InputProperties *properties, char **inputs);


/**
 * Displays a simple message box window, with a message and a "Close" button.
 */
void messageBox(Window *window, char *message);

#endif