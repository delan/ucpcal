/**
 * @file date.h
 * @brief Data structures and algorithms for handling dates and times.
 */

#ifndef UCPCAL_DATE_H
#define UCPCAL_DATE_H

#include <stdio.h>

/**
 * A simple data structure that stores a date in the Gregorian calendar, and
 * a time of the day on the 24-hour clock.
 */

typedef struct ucpcal_date {
	int year;
	int month;
	int day;
	int hour;
	int minute;
} ucpcal_date;

/**
 * Reads a date from stdin in the format "YYYY-MM-DD HH:MM".
 * @return the struct ucpcal_date value of the input date
 */

ucpcal_date ucpcal_date_scan(void);

/**
 * @brief Expresses a duration in minutes as a friendly string.
 * The string contains hours and/or minutes where necessary. Uses a static
 * character array for storage to avoid heap allocation, but beware that this
 * makes the function non-reentrant. 40 bytes for the static buffer is enough,
 * even in the worst case where the platform's int type is 64 bits.
 * @return a const-qualified string representation of the duration.
 */

const char *ucpcal_duration_friendly(int minutes);

#endif
