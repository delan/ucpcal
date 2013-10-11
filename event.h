/**
 * @file event.h
 * @brief Data structures and algorithms for calendar events.
 */

#ifndef UCPCAL_EVENT_H
#define UCPCAL_EVENT_H

#include "date.h"

/**
 * A data structure representing a calendar event.
 */

typedef struct ucpcal_event {
	ucpcal_date date_time;
	int duration_minutes;
	char *name;
	char *location;
} ucpcal_event;

#endif
