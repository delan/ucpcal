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
 * @brief Reads a string from stdin until the next newline.
 * Allocates and reallocates buffers of increasing size as more space is
 * required, doubling the size of the buffer each time to only require O(log n)
 * reallocations, though in the worst case just under 50% of the space may be
 * wasted until the buffer is shrunk to only what is needed before returning.
 * You should free() the returned string when you are no longer using it.
 * @return a heap allocated string containing the input
 */

char *ucpcal_readline(void);

#endif
