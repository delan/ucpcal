/**
 * @file ucpcal.h
 * @brief The main calendar program source file.
 */

#ifndef UCPCAL_H
#define UCPCAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gui.h"
#include "date.h"
#include "event.h"
#include "list.h"

/**
 * @brief A data structure for passing state to GTK+ callbacks.
 * Contains a window handle and a pointer to a linked list of events.
 */

typedef struct ucpcal_state {
	Window *win;
	ucpcal_list *list;
} ucpcal_state;

/**
 * @brief The main entry point for the calendar application.
 * @param argc the number of command line arguments
 * @param argv the command line argument vector
 * @return 1 where an error has occurred, 0 otherwise
 */

int main(int argc, char **argv);

/**
 * @brief Sets up, runs and cleans up calendar application GUI.
 * @param list a linked list of calendar events
 */

void ucpcal_gui(ucpcal_list *list);

/**
 * @brief Builds a heap allocated string from the current calendar for the GUI.
 * Be sure to use free() when finished.
 * @param list the linked list of calendar events
 * @return a heap allocated string with GUI calendar output
 */

char *ucpcal_gui_build_output(ucpcal_list *list);

/**
 * @brief GUI: loads calendar data from a file.
 * @param state the ucpcal_state consisting of a window and linked list
 */

void ucpcal_gui_load(void *state);

/**
 * @brief GUI: saves calendar data to a file.
 * @param state the ucpcal_state consisting of a window and linked list
 */

void ucpcal_gui_save(void *state);

/**
 * @brief GUI: adds an event to the current calendar.
 * @param state the ucpcal_state consisting of a window and linked list
 */

void ucpcal_gui_add(void *state);

/**
 * @brief GUI: edits an event in the current calendar.
 * @param state the ucpcal_state consisting of a window and linked list
 */

void ucpcal_gui_edit(void *state);

/**
 * @brief GUI: deletes an event from the current calendar.
 * @param state the ucpcal_state consisting of a window and linked list
 */

void ucpcal_gui_delete(void *state);

/**
 * @brief Reads a string from the given file handle until the next newline.
 * Allocates and reallocates buffers of increasing size as more space is
 * required, doubling the size of the buffer each time to only require O(log n)
 * reallocations, though in the worst case just under 50% of the space may be
 * wasted until the buffer is shrunk to only what is needed before returning.
 * Be sure to use free() when finished.
 * @param f the file handle to read from
 * @return a heap allocated string containing the input
 */

char *ucpcal_readline(FILE *f);

/**
 * @brief Loads calendar data from a file into a linked list of events.
 * @param list the linked list of calendar events
 * @param filename the filename to look for input data in
 */

void ucpcal_load(ucpcal_list *list, const char *filename);

/**
 * @brief Saves calendar data to a file from a linked list of events.
 * @param list the linked list of calendar events
 * @param filename the filename to output calendar data to
 */

void ucpcal_save(ucpcal_list *list, const char *filename);

#endif
