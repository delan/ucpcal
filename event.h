/**
 * @file event.h
 * @brief Data structures and algorithms for calendar events.
 */

#ifndef UCPCAL_EVENT_H
#define UCPCAL_EVENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"

/**
 * @brief A data structure representing a calendar event.
 * Always use heap allocated strings for name and location, because
 * ucpcal_event_free() will attempt to free() them.
 */

typedef struct ucpcal_event {
	/**
	 * The date and time of the event.
	 */
	ucpcal_date date;
	/**
	 * The duration of the event, in minutes.
	 */
	unsigned int duration;
	/**
	 * The name of the event. Only use heap allocated strings here!
	 */
	char *name;
	/**
	 * Location (optional). Only use heap allocated strings here!
	 */
	char *location;
} ucpcal_event;

/**
 * @brief Creates a new event struct on the heap.
 * Be sure to use ucpcal_event_free() when finished.
 * @return pointer to new event struct
 */

ucpcal_event *ucpcal_event_new(void);

/**
 * @brief Frees the memory used for an event struct.
 * Frees the memory pointed to by name and location, if they are not NULL.
 * @param event the event to be freed
 */

void ucpcal_event_free(ucpcal_event *event);

#endif
