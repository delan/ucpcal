/**
 * @file ucpcal.c
 * @brief The main calendar program source file.
 */

#include "ucpcal.h"

int main(int argc, char **argv) {
	int return_value = 0;
	ucpcal_list *list = NULL;
	switch (argc) {
	case 1:
		break;
	case 2:
		list = ucpcal_load(argv[1]);
		break;
	default:
		fprintf(stderr, "Usage: %s [filename?]\n", argv[0]);
		return_value = 1;
		break;
	}
	ucpcal_gui();
	ucpcal_list_free(list);
	return return_value;
}

void ucpcal_gui(void) {
	Window *win = createWindow("Calendar: Delan Azabani #17065012");
	addButton(win, "Load a calendar from file", &ucpcal_gui_load, NULL);
	addButton(win, "Save this calendar to file", &ucpcal_gui_save, NULL);
	addButton(win, "Add a calendar event", &ucpcal_gui_add, NULL);
	addButton(win, "Edit a calendar event", &ucpcal_gui_edit, NULL);
	addButton(win, "Delete a calendar event", &ucpcal_gui_delete, NULL);
	runGUI(win);
	freeWindow(win);
}

char *ucpcal_gui_build_output(ucpcal_list *list) {
	/**/
}

void ucpcal_gui_load(void *data) {
	/**/
}

void ucpcal_gui_save(void *data) {
	/**/
}

void ucpcal_gui_add(void *data) {
	/**/
}

void ucpcal_gui_edit(void *data) {
	/**/
}

void ucpcal_gui_delete(void *data) {
	/**/
}

char *ucpcal_readline(FILE *f) {
	/* A sane starting buffer size that may minimise reallocations. */
	size_t bufsize = 32;
	size_t used = 0;
	char *result = (char *) malloc(bufsize);
	int ch = getc(f);
	while (ch != '\n' && ch != EOF) {
		if (used == bufsize) {
			bufsize *= 2;
			result = (char *) realloc(result, bufsize);
		}
		result[used] = ch;
		used++;
		ch = getc(f);
	}
	result = (char *) realloc(result, used + 1);
	result[used] = 0;
	return result;
}

ucpcal_list *ucpcal_load(const char *filename) {
	/*
		For consistent behaviour across platforms, binary mode is off.
		Please ensure that input calendar files use LF line endings.
	*/
	FILE *f = fopen(filename, "r");
	ucpcal_list *list = NULL;
	int done = 0;
	if (f) {
		list = ucpcal_list_new();
		do {
			int duration;
			char *name, *location;
			ucpcal_event *event;
			ucpcal_date date = ucpcal_date_scan(f);
			if (date.good) {
				/* Consume whitespace around duration value. */
				fscanf(f, " %d ", &duration);
				name = ucpcal_readline(f);
				location = ucpcal_readline(f);
				if (strlen(location) > 0) {
					/* Discard the following blank line. */
					free(ucpcal_readline(f));
				} else {
					/* Free the empty location string. */
					free(location);
					/* Set the location pointer to NULL. */
					location = NULL;
				}
				event = ucpcal_event_new();
				event->date = date;
				event->duration = duration;
				event->name = name;
				event->location = location;
				ucpcal_list_append(list, event);
			} else {
				done = 1;
			}
		} while (!done);
		fclose(f);
	}
	ucpcal_list_print_debug(list);
	return list;
}
