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
