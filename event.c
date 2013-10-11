/**
 * @file event.c
 * @brief Data structures and algorithms for calendar events.
 */

#include "event.h"

ucpcal_event *ucpcal_event_new(void) {
	ucpcal_event *event = (ucpcal_event *) calloc(sizeof(ucpcal_event), 1);
	/*
		The date fields and duration are all zero because of calloc().
		However, NULL is not guaranteed to be all-bits-zero, so we
		should set it manually here for portability.
	*/
	event->name = NULL;
	event->location = NULL;
	return event;
}

void ucpcal_event_free(ucpcal_event *event) {
	/*
		There is no need to ensure that name and location aren't NULL
		before freeing, because freeing a NULL pointer does nothing.
		However, we do need to check that event itself isn't NULL.
		From ISO 9899:1990, §7.10.3.2, page 154:

		If ptr is a null pointer, no action occurs.

	*/
	if (event) {
		free(event->name);
		free(event->location);
		free(event);
	}
}
