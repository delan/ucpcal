/**
 * @file list.h
 * @brief Data structures and algorithms for linked lists of events.
 * To improve performance and simplicity, the data of the calendar event struct
 * is stored directly within the list node, avoiding the need to make and free
 * two separate allocations. The linked list is double ended and doubly linked.
 */

#ifndef UCPCAL_LIST_H
#define UCPCAL_LIST_H

#include "event.h"

/**
 * @brief A data structure representing a linked list node for an event.
 */

typedef struct ucpcal_node {
	ucpcal_event event;
	struct ucpcal_node *prev;
	struct ucpcal_node *next;
} ucpcal_node;

/**
 * @brief A data structure representing an entire linked list of events.
 */

typedef struct ucpcal_list {
	size_t length;
	ucpcal_node *head;
	ucpcal_node *tail;
} ucpcal_list;

#endif
