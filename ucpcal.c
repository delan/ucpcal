/**
 * @file ucpcal.c
 * @brief The main calendar program source file.
 */

#include "ucpcal.h"

int main(int argc, char **argv) {
	int return_value = 0;
	char *default_filename = NULL;
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

char *ucpcal_readline(void) {
	/* A sane starting buffer size that may minimise reallocations. */
	size_t bufsize = 32;
	size_t used = 0;
	char *result = (char *) malloc(bufsize);
	int ch = getchar();
	while (ch != '\n' && ch != EOF) {
		if (used == bufsize) {
			bufsize *= 2;
			result = (char *) realloc(result, bufsize);
		}
		result[used] = ch;
		used++;
		ch = getchar();
	}
	result = (char *) realloc(result, used + 1);
	result[used] = 0;
	return result;
}
