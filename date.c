/**
 * @file date.c
 * @brief Data structures and algorithms for handling dates and times.
 */

#include "date.h"

ucpcal_date ucpcal_date_scan(void) {
	/*
		Initialises the struct with all fields set to zero.
		From ISO 9899:1990, §6.5.7, page 72:

		If there are fewer initializers in a brace-enclosed list than
		there are members of an aggregate, the remainder of the
		aggregate shall be initialized implicitly the same as objects
		that have static storage duration.
	*/
	ucpcal_date date = {0};
	scanf(
		"%d-%d-%d %d:%d",
		&date.year,
		&date.month,
		&date.day,
		&date.hour,
		&date.minute
	);
	return date;
}

const char *ucpcal_duration_friendly(int minutes) {
	static char result[40] = "";
	int output_hours = minutes / 60;
	int output_minutes = minutes % 60;
	if (output_hours != 0 && output_minutes != 0)
		snprintf(
			result,
			sizeof(result),
			"%d hour%s, %d minute%s",
			output_hours,
			output_hours == 1 ? "" : "s",
			output_minutes,
			output_minutes == 1 ? "" : "s"
		);
	else if (output_hours != 0)
		snprintf(
			result,
			sizeof(result),
			"%d hour%s",
			output_hours,
			output_hours == 1 ? "" : "s"
		);
	else
		snprintf(
			result,
			sizeof(result),
			"%d minute%s",
			output_minutes,
			output_minutes == 1 ? "" : "s"
		);
	return result;
}
