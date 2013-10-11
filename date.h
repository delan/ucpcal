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

#endif
