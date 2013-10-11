/**
 * @file list.h
 * @brief Data structures and algorithms for linked lists of events.
 */

#ifndef UCPCAL_LIST_H
#define UCPCAL_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"

/**
 * @brief A data structure representing a linked list node for an event.
 */

typedef struct ucpcal_node {
	ucpcal_event *event;
	struct ucpcal_node *next;
} ucpcal_node;

/**
 * @brief A data structure representing an entire linked list of events.
 */

typedef struct ucpcal_list {
	ucpcal_node *head;
	ucpcal_node *tail;
} ucpcal_list;

/**
 * @brief Creates a new linked list node on the heap.
 * Be sure to use ucpcal_node_free() when finished.
 * @return pointer to new ucpcal_node struct
 */

ucpcal_node *ucpcal_node_new(void);

/**
 * @brief Frees the memory used for a linked list node struct.
 * Also frees the event pointed to by the node.
 * @param node the node to be freed
 */

void ucpcal_node_free(ucpcal_node *node);

/**
 * @brief Creates a new linked list on the heap.
 * Be sure to use ucpcal_list_free() when finished.
 * @return pointer to new ucpcal_list struct
 */

ucpcal_list *ucpcal_list_new(void);

/**
 * @brief Frees the memory used for a linked list struct.
 * Also frees memory for all contained nodes and their events.
 * @param list the linked list to be freed
 */

void ucpcal_list_free(ucpcal_list *list);

/**
 * @brief Appends an event to a linked list.
 * A new linked list node is automatically created to wrap the event. The
 * linked list is walked to guarantee that there can only be one event in a
 * list with a particular name.
 * @param list the linked list to append to
 * @param event the event to append
 */

void ucpcal_list_append(ucpcal_list *list, ucpcal_event *event);

/**
 * @brief Deletes an event by name from a linked list.
 * @param list the linked list to delete from
 * @param name the name of the event that should be deleted
 */

void ucpcal_list_delete(ucpcal_list *list, const char *name);

/**
 * @brief Finds an event by name in a linked list.
 * @param list the linked list to search through
 * @param name the name of events that should be deleted
 * @return the matching event, or NULL if there is no such event
 */

ucpcal_event *ucpcal_list_find(ucpcal_list *list, const char *name);

#endif
