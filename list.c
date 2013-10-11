/**
 * @file list.c
 * @brief Data structures and algorithms for linked lists of events.
 */

#include "list.h"

ucpcal_node *ucpcal_node_new(void) {
	ucpcal_node *node = (ucpcal_node *) malloc(sizeof(ucpcal_node));
	node->event = NULL;
	node->next = NULL;
	return node;
}

void ucpcal_node_free(ucpcal_node *node) {
	/* Free the event pointed to by the node. */
	ucpcal_event_free(node->event);
	/* Free the actual node. */
	free(node);
}

ucpcal_list *ucpcal_list_new(void) {
	ucpcal_list *list = (ucpcal_list *) malloc(sizeof(ucpcal_list));
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void ucpcal_list_free(ucpcal_list *list) {
	ucpcal_node *cur = list->head, *next;
	while (cur) {
		/* Free each node. */
		next = cur->next;
		ucpcal_node_free(cur);
		cur = next;
	}
	/* Free the list. */
	free(list);
}

void ucpcal_list_append(ucpcal_list *list, ucpcal_event *event) {
	ucpcal_node *node = ucpcal_node_new();
	node->event = event;
	if (list->tail)
		/* If there is a last element, add the node after it. */
		list->tail->next = node;
	else
		/* The list is empty; the appended node is the new head. */
		list->head = node;
	/* Regardless of what happens, the appended node is the new tail. */
	list->tail = node;
}

void ucpcal_list_delete(ucpcal_list *list, const char *name) {
	ucpcal_node *cur = list->head, *prev = NULL;
	int done = 0;
	while (cur && !done) {
		if (!strcmp(cur->event->name, name)) {
			if (prev)
				/* The node to be deleted is not the first. */
				prev->next = cur->next;
			else
				/* The node to be deleted is the first. */
				list->head = cur->next;
			if (cur == list->tail)
				/* The node to be deleted is the last. */
				list->tail = prev;
			ucpcal_node_free(cur);
			done = 1;
		}
		prev = cur;
		cur = cur->next;
	}
}

ucpcal_event *ucpcal_list_find(ucpcal_list *list, const char *name) {
	ucpcal_node *cur = list->head;
	ucpcal_event *result = NULL;
	int done = 0;
	while (cur && !done) {
		if (!strcmp(cur->event->name, name)) {
			result = cur->event;
			done = 1;
		}
		cur = cur->next;
	}
	return result;
}
