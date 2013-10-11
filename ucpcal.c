/**
 * @file ucpcal.c
 * @brief The main calendar program source file.
 */

#include "ucpcal.h"

int main(int argc, char **argv) {
	int return_value = 0;
	ucpcal_list *list = ucpcal_list_new();
	switch (argc) {
	case 1:
		break;
	case 2:
		ucpcal_load(list, argv[1]);
		break;
	default:
		fprintf(stderr, "Usage: %s [filename?]\n", argv[0]);
		return_value = 1;
		break;
	}
	ucpcal_gui(list);
	ucpcal_list_free(list);
	return return_value;
}

void ucpcal_gui(ucpcal_list *list) {
	char *output;
	Window *win = createWindow("Calendar: Delan Azabani #17065012");
	ucpcal_state state;
	state.win = win;
	state.list = list;
	addButton(win, "Load a calendar from file", &ucpcal_gui_load, &state);
	addButton(win, "Save this calendar to file", &ucpcal_gui_save, &state);
	addButton(win, "Add a calendar event", &ucpcal_gui_add, &state);
	addButton(win, "Edit a calendar event", &ucpcal_gui_edit, &state);
	addButton(win, "Delete a calendar event", &ucpcal_gui_delete, &state);
	output = ucpcal_gui_build_output(list);
	setText(win, output);
	free(output);
	runGUI(win);
	freeWindow(win);
}

char *ucpcal_gui_build_output(ucpcal_list *list) {
	/* result_cursor is used for appending with sprintf() */
	char *result, *result_cursor;
	/* First, let's calculate how much to allocate for the string. */
	/* Start with enough to hold a null terminator. */
	size_t size = 1;
	ucpcal_node *cur = list->head;
	while (cur) {
		/*
			This would be a lot easier with the snprintf(0) trick
			that does nothing but returns the buffer size required,
			but alas we do not have ISO C99 available in this unit.
		*/
		/* Add enough for the event name. */
		size += strlen(cur->event->name);
		/* Add enough for " @ ". */
		size += 3;
		/* Add enough for the event location. */
		size += cur->event->location ?
			strlen(cur->event->location) : 0;
		/* Add enough for " (". */
		size += 2;
		/* Add enough for the worst case friendly duration. */
		size += 64;
		/* Add enough for ")\n". */
		size += 2;
		/* Add enough for the worst case friendly date and time. */
		size += 64;
		/* Add enough for "\n---\n\n". */
		size += 6;
		cur = cur->next;
	}
	/* Now, let's allocate. */
	result = (char *) malloc(size);
	result_cursor = result;
	/* Terminate the string correctly first in case there are no nodes. */
	sprintf(result_cursor, "");
	/* For each event, let's append to the string. */
	cur = list->head;
	while (cur) {
		/*
			Print to result_cursor, then advancing result_cursor
			by the number of bytes printed excluding the null
			terminator afterwards.
		*/
		result_cursor += sprintf(
			result_cursor,
			"%s%s%s (%s)\n%s\n---\n\n",
			cur->event->name,
			cur->event->location ? " @ " : "",
			cur->event->location ? cur->event->location : "",
			ucpcal_duration_friendly(cur->event->duration),
			ucpcal_date_friendly(cur->event->date)
		);
		cur = cur->next;
	}
	return result;
}

void ucpcal_gui_load(void *state) {
	ucpcal_state *s = (ucpcal_state *) state;
	InputProperties props[] = {{ "Input filename", 255, 0 }};
	char *filename = (char *) calloc(256, sizeof(char));
	char *output;
	if (dialogBox(s->win, "Open file", 1, props, &filename)) {
		ucpcal_load(s->list, filename);
		output = ucpcal_gui_build_output(s->list);
		setText(s->win, output);
		free(output);
	}
	free(filename);
}

void ucpcal_gui_save(void *state) {
	ucpcal_state *s = (ucpcal_state *) state;
	InputProperties props[] = {{ "Output filename", 255, 0 }};
	char *filename = (char *) calloc(256, sizeof(char));
	if (dialogBox(s->win, "Save file", 1, props, &filename))
		ucpcal_save(s->list, filename);
	free(filename);
}

void ucpcal_gui_add(void *state) {
	/**/
}

void ucpcal_gui_edit(void *state) {
	/**/
}

void ucpcal_gui_delete(void *state) {
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

void ucpcal_load(ucpcal_list *list, const char *filename) {
	/*
		For consistent behaviour across platforms, binary mode is off.
		Please ensure that input calendar files use LF line endings.
	*/
	FILE *f = fopen(filename, "r");
	int done = 0;
	if (f) {
		ucpcal_list_empty(list);
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
}

void ucpcal_save(ucpcal_list *list, const char *filename) {
	/* For consistent behaviour across platforms, binary mode is on. */
	FILE *f = fopen(filename, "wb");
	if (f) {
		ucpcal_node *cur = list->head;
		while (cur) {
			fprintf(f,
				"%d-%02d-%02d %02d:%02d %d %s%s%s\n\n",
				cur->event->date.year,
				cur->event->date.month,
				cur->event->date.day,
				cur->event->date.hour,
				cur->event->date.minute,
				cur->event->duration,
				cur->event->name,
				cur->event->location ? "\n" : "",
				cur->event->location ?
					cur->event->location : ""
			);
			cur = cur->next;
		}
		fclose(f);
	}
}
