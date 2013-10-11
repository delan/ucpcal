/**
 * @file ucpcal.c
 * @brief The main calendar program source file.
 */

#include "ucpcal.h"

int main(int argc, char **argv) {
	int return_value = 0;
	char *default_filename = NULL;
	ucpcal_date date = ucpcal_date_scan();
	printf(
		"======== %d %d %d %d %d\n",
		date.year,
		date.month,
		date.day,
		date.hour,
		date.minute
	);
	switch (argc) {
	case 1:
		break;
	case 2:
		default_filename = argv[1];
		break;
	default:
		fprintf(stderr, "Usage: %s [filename?]\n", argv[0]);
		return_value = 1;
		break;
	}
	return return_value;
}
