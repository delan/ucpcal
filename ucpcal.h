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
 * @brief The main entry point for the calendar application.
 * @param argc the number of command line arguments
 * @param argv the command line argument vector
 * @return 1 where an error has occurred, 0 otherwise
 */

int main(int argc, char **argv);

/**
 * @brief Sets up, runs and cleans up calendar application GUI.
 */

void ucpcal_gui(void);

void ucpcal_gui_load(void *data);

void ucpcal_gui_save(void *data);

void ucpcal_gui_add(void *data);

void ucpcal_gui_edit(void *data);

void ucpcal_gui_delete(void *data);

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
 * Automatically allocates and returns a new linked list, nodes and events.
 * Be sure to use ucpcal_list_free() when finished.
 * @param filename the filename to look for input data in
 * @return pointer to new ucpcal_list struct
 */

ucpcal_list *ucpcal_load(const char *filename);

#endif
