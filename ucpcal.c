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
	Window *win = createWindow("Calendar: Delan Azabani #17065012");
	ucpcal_state state;
	state.win = win;
	state.list = list;
	addButton(win, "Load a calendar from file", &ucpcal_gui_load, &state);
	addButton(win, "Save this calendar to file", &ucpcal_gui_save, &state);
	addButton(win, "Add a calendar event", &ucpcal_gui_add, &state);
	addButton(win, "Edit a calendar event", &ucpcal_gui_edit, &state);
	addButton(win, "Delete a calendar event", &ucpcal_gui_delete, &state);
	ucpcal_gui_update(&state);
	runGUI(win);
	freeWindow(win);
}

void ucpcal_gui_update(ucpcal_state *state) {
	char *output = ucpcal_gui_build_output(state->list);
	setText(state->win, output);
	free(output);
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
	*result_cursor = 0;
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
	if (dialogBox(s->win, "Open file", 1, props, &filename)) {
		ucpcal_load(s->list, filename);
		ucpcal_gui_update(s);
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
	ucpcal_state *s = (ucpcal_state *) state;
	InputProperties props[] = {
		{ "Year", 24, 0 },
		{ "Month", 2, 0 },
		{ "Day", 2, 0 },
		{ "Hour", 2, 0 },
		{ "Minute", 2, 0 },
		{ "Duration in minutes", 24, 0 },
		{ "Name of event", 255, 0 },
		{ "Optional location", 255, 0 }
	};
	int i;
	char *inputs[8];
	inputs[0] = (char *) calloc(25, sizeof(char));
	inputs[1] = (char *) calloc(3, sizeof(char));
	inputs[2] = (char *) calloc(3, sizeof(char));
	inputs[3] = (char *) calloc(3, sizeof(char));
	inputs[4] = (char *) calloc(3, sizeof(char));
	inputs[5] = (char *) calloc(25, sizeof(char));
	inputs[6] = (char *) calloc(256, sizeof(char));
	inputs[7] = (char *) calloc(256, sizeof(char));
	if (dialogBox(s->win, "Add calendar event", 8, props, inputs)) {
		ucpcal_event *event = ucpcal_event_new();
		event->date.year = atoi(inputs[0]);
		event->date.month = atoi(inputs[1]);
		event->date.day = atoi(inputs[2]);
		event->date.hour = atoi(inputs[3]);
		event->date.minute = atoi(inputs[4]);
		event->date.good = 1;
		event->duration = atoi(inputs[5]);
		event->name = inputs[6];
		if (strlen(inputs[7]) > 0) {
			event->location = inputs[7];
		} else {
			event->location = NULL;
			free(inputs[7]);
		}
		ucpcal_list_append(s->list, event);
		ucpcal_gui_update(s);
	} else {
		free(inputs[6]);
		free(inputs[7]);
	}
	for (i = 0; i < 6; i++)
		free(inputs[i]);
}

void ucpcal_gui_edit(void *state) {
	ucpcal_state *s = (ucpcal_state *) state;
	InputProperties props[] = {{ "Name of event", 255, 0 }};
	char *name = (char *) calloc(256, sizeof(char));
	ucpcal_event *event;
	if (dialogBox(s->win, "Edit calendar event", 1, props, &name))
		if ((event = ucpcal_list_find(s->list, name)))
			ucpcal_gui_edit_more(s, event);
	free(name);
}

void ucpcal_gui_edit_more(void *state, ucpcal_event *event) {
	ucpcal_state *s = (ucpcal_state *) state;
	InputProperties props[] = {
		{ "Year", 24, 0 },
		{ "Month", 2, 0 },
		{ "Day", 2, 0 },
		{ "Hour", 2, 0 },
		{ "Minute", 2, 0 },
		{ "Duration in minutes", 24, 0 },
		{ "Name of event", 255, 0 },
		{ "Optional location", 255, 0 }
	};
	int i;
	char *inputs[8];
	inputs[0] = (char *) calloc(25, sizeof(char));
	sprintf(inputs[0], "%d", event->date.year);
	inputs[1] = (char *) calloc(3, sizeof(char));
	sprintf(inputs[1], "%d", event->date.month);
	inputs[2] = (char *) calloc(3, sizeof(char));
	sprintf(inputs[2], "%d", event->date.day);
	inputs[3] = (char *) calloc(3, sizeof(char));
	sprintf(inputs[3], "%d", event->date.hour);
	inputs[4] = (char *) calloc(3, sizeof(char));
	sprintf(inputs[4], "%d", event->date.minute);
	inputs[5] = (char *) calloc(25, sizeof(char));
	sprintf(inputs[5], "%d", event->duration);
	inputs[6] = (char *) calloc(256, sizeof(char));
	strncpy(inputs[6], event->name, 255);
	inputs[7] = (char *) calloc(256, sizeof(char));
	if (event->location)
		strncpy(inputs[7], event->location, 255);
	if (dialogBox(s->win, "Edit calendar event", 8, props, inputs)) {
		free(event->name);
		free(event->location);
		event->date.year = atoi(inputs[0]);
		event->date.month = atoi(inputs[1]);
		event->date.day = atoi(inputs[2]);
		event->date.hour = atoi(inputs[3]);
		event->date.minute = atoi(inputs[4]);
		event->date.good = 1;
		event->duration = atoi(inputs[5]);
		event->name = inputs[6];
		if (strlen(inputs[7]) > 0) {
			event->location = inputs[7];
		} else {
			event->location = NULL;
			free(inputs[7]);
		}
		ucpcal_gui_update(s);
	} else {
		free(inputs[6]);
		free(inputs[7]);
	}
	for (i = 0; i < 6; i++)
		free(inputs[i]);
}

void ucpcal_gui_delete(void *state) {
	ucpcal_state *s = (ucpcal_state *) state;
	InputProperties props[] = {{ "Name of event", 255, 0 }};
	char *name = (char *) calloc(256, sizeof(char));
	if (dialogBox(s->win, "Delete calendar event", 1, props, &name)) {
		ucpcal_list_delete(s->list, name);
		ucpcal_gui_update(s);
	}
	free(name);
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
		Postel's law: be conservative in what you do, be liberal in
		what you accept from others.

		Binary mode is OFF here so that files with CR+LF line endings
		can be read properly, at least on Windows, though hopefully
		users of other platforms won't use CR+LF delimited input.
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
	/*
		Postel's law: be conservative in what you do, be liberal in
		what you accept from others.

		Binary mode is ON here so that regardless of platform, we
		standardise on outputting files with LF line endings.
	*/
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
