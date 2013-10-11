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
