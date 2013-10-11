/**
 * @file date.c
 * @brief Data structures and algorithms for handling dates and times.
 */

#include "date.h"

ucpcal_date ucpcal_date_scan(FILE *f) {
	/*
		Initialises the struct with all fields set to zero.
		From ISO 9899:1990, §6.5.7, page 72:

		If there are fewer initializers in a brace-enclosed list than
		there are members of an aggregate, the remainder of the
		aggregate shall be initialized implicitly the same as objects
		that have static storage duration.
	*/
	ucpcal_date date = {0};
	if (fscanf(f,
		"%d-%d-%d %d:%d",
		&date.year,
		&date.month,
		&date.day,
		&date.hour,
		&date.minute
	) == 5)
		date.good = 1;
	return date;
}

const char *ucpcal_duration_friendly(unsigned int minutes) {
	static char result[64] = "";
	int output_hours = minutes / 60;
	int output_minutes = minutes % 60;
	if (output_hours != 0 && output_minutes != 0)
		sprintf(
			result,
			"%u hour%s, %u minute%s",
			output_hours,
			output_hours == 1 ? "" : "s",
			output_minutes,
			output_minutes == 1 ? "" : "s"
		);
	else if (output_hours != 0)
		sprintf(
			result,
			"%u hour%s",
			output_hours,
			output_hours == 1 ? "" : "s"
		);
	else
		sprintf(
			result,
			"%u minute%s",
			output_minutes,
			output_minutes == 1 ? "" : "s"
		);
	return result;
}

const char *ucpcal_date_friendly(ucpcal_date date) {
	static char result[64] = "";
	static const char *months[] = {
		NULL, "January", "February", "March", "April",
		"May", "June", "July", "August",
		"September", "October", "November", "December"
	};
	if (
		date.year >= 0 &&
		date.month >= 1 && date.month <= 12 &&
		date.day >= 1 && date.day <= 31 &&
		date.hour >= 0 && date.hour <= 23 &&
		date.minute >= 0 && date.minute <= 59 &&
		date.good
	) {
		int hour = date.hour % 12;
		if (hour == 0)
			hour = 12;
		if (date.minute)
			sprintf(
				result,
				"%d %s %d, %d:%02d %cm",
				date.day,
				months[date.month],
				date.year,
				hour,
				date.minute,
				date.hour > 11 ? 'p' : 'a'
			);
		else
			sprintf(
				result,
				"%d %s %d, %d %cm",
				date.day,
				months[date.month],
				date.year,
				hour,
				date.hour > 11 ? 'p' : 'a'
			);
	} else {
		strcpy(result, "invalid date and/or time");
	}
	return result;
}
