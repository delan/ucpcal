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
 * @brief Reads a string from stdin until the next newline.
 * Allocates and reallocates buffers of increasing size as more space is
 * required, doubling the size of the buffer each time to only require O(log n)
 * reallocations, though in the worst case just under 50% of the space may be
 * wasted until the buffer is shrunk to only what is needed before returning.
 * Be sure to use free() when finished.
 * @return a heap allocated string containing the input
 */

char *ucpcal_readline(void);

#endif
