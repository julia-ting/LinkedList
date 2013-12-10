/**
 * CS 2110 - Summer 2012 - Homework #10
 * Edited by: Brandon Whitehead, Andrew Wilder
 *
 * list.c: Complete the functions!
 */

// Author: Julia Ting

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* The node struct.  Has a prev pointer, next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO*/
/* Design consideration only this file should know about nodes */
/* Only this file should be manipulating nodes */
/* DO NOT TOUCH THIS DECLARATION DO NOT PUT IT IN OTHER FILES */
typedef struct lnode
{
  struct lnode* prev; /* Pointer to previous node */
  struct lnode* next; /* Pointer to next node */
  void* data; /* User data */
} node;


/* Do not create any global variables here. Your linked list library should obviously work for multiple linked lists */
// This function is declared as static since you should only be calling this inside this file.
static node* create_node(void* data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void* data)
{
	node *newNode = malloc(sizeof(node));
	// Check if Malloc fails
	if (newNode == NULL) {
		printf("MALLOC FAIL IN CREATE_NODE");
		return NULL;
	}
	newNode->data = data;
	newNode->prev = NULL;
	newNode->next = NULL;
    return newNode;
}

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head/tail to NULL.
  *
  * @return an empty linked list
  */
list* create_list(void)
{
	list *linkedList = malloc(sizeof(list));
	// Check if Malloc fails
	if (linkedList == NULL) {
		printf("MALLOC FAIL IN CREATE_LIST");
		return NULL;
	}
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->size = 0;
    return linkedList;
}

/** push_front
  *
  * Adds the data to the front of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_front(list* llist, void* data)
{
	node *newNode = create_node(data);

	if (llist->size==0) {
		llist->head = newNode;
		llist->tail = newNode;
	} else {
		node *oldHead = llist->head;
		oldHead->prev = newNode;
		llist->head = newNode;
		newNode->next = oldHead;
	}
	llist->size = llist->size + 1;
	
}

/** push_back
  *
  * Adds the data to the back/end of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_back(list* llist, void* data)
{
	node *newNode = create_node(data);
	if (llist->size==0) {
		llist->head = newNode;
		llist->tail = newNode;
	} else {
		node *oldTail = llist->tail;
		oldTail->next = newNode;
		newNode->prev = oldTail;
		llist->tail = newNode;
	}
	llist->size = llist->size +1;
}

/** remove_front
  *
  * Removes the node at the front of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed (which is only there are no elements) 0 if the remove succeeded.
  */
int remove_front(list* llist, list_op free_func)
{
    if (llist->size==0) {
    	return -1;
    }
    node *removed = llist->head;
    if (llist->size==1) {	
    	llist->head = NULL;
    	llist->tail = NULL;
	} else {
		node *newHead = removed->next;
		newHead->prev = NULL;
		llist->head = newHead;
		removed->next = NULL;
	}
    free_func(removed->data);
    free(removed);
    llist->size = llist->size - 1;
    return 0;
}

/** remove_back
  *
  * Removes the node at the back of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_back(list* llist, list_op free_func)
{
	if (llist->size==0) {
		return -1;
	}
	node *removed = llist->tail;
	if (llist->size==1) {
		llist->head = NULL;
		llist->tail = NULL;
	} else {
		node *newTail = removed->prev;
		removed->prev = NULL;
		llist->tail = newTail;
		newTail->next = NULL;
	}
	free_func(removed->data);
	free(removed);
	llist->size = llist->size - 1;
    return 0;
}

/** copy_list
  *
  * Create a new list structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any test structure must copy
  * EVERYTHING!
  *
  * @param llist A pointer to the linked list to make a copy of
  * @param copy_func A function pointer to a function that makes a copy of the
  *        data that's being used in this linked list, allocating space for
  *        every part of that data on the heap
  * @return The linked list created by copying the old one
  */
list* copy_list(list* llist, list_cpy copy_func)
{
	list *cpyList = create_list();
	if (llist->size != 0) {
		node *current = llist->head;
		void* data = copy_func(current->data);
		push_back(cpyList, data);
		while (current->next != NULL) {
			current = current->next;
			data = copy_func(current->data);
			push_back(cpyList, data);
		}
	}
	return cpyList;
}

/** front
  *
  * Gets the data at the front of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the first node in the linked list or NULL.
  */
void* front(list* llist)
{
    return (llist->head==NULL) ? NULL : llist->head->data;
}

/** back
  *
  * Gets the data at the "end" of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the last node in the linked list or NULL.
  */
void* back(list* llist)
{
    return (llist->tail==NULL) ? NULL : llist->tail->data;
}

/** size
  *
  * Gets the size of the linked list
  *
  * @param llist a pointer to the list
  * @return The size of the linked list
  */
int size(list* llist)
{
    return llist->size;
}

/** traverse
  *
  * Traverses the linked list calling a function on each node's data.
  *
  * @param llist a pointer to a linked list.
  * @param do_func a function that does something to each node's data.
  */
void traverse(list* llist, list_op do_func)
{
	if (llist->size != 0) {
		node *current = llist->head;
		do_func(current->data);
		while (current->next != NULL) {
			current = current->next;
			do_func(current->data);
		}
	}
}

/** remove_if
  *
  * Removes all nodes whose data when passed into the predicate function returns true
  *
  * @param llist a pointer to the list
  * @param pred_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise @see list_pred.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_if(list* llist, list_pred pred_func, list_op free_func)
{
	int numNodes = 0;
	if (llist->size == 0) {
		return 0;
	}
	// If remove first node
	while (pred_func(llist->head->data)) {
		numNodes = numNodes+1;
		remove_front(llist, free_func);
	}
	node *prev = llist->head;
	node *removed;
	if (prev->next == NULL) {
		llist->tail = prev;
		return numNodes;
	}
	node *current = prev->next;
	while (current != NULL) {
		if (pred_func(current->data)) {
			prev->next = current->next;
			removed = current;
			current = prev->next;
			removed->prev = NULL;
			removed->next = NULL;
			llist->size = llist->size-1;
			numNodes = numNodes+1;
			free_func(removed->data);
			free(removed);
		} else {
			prev = current;
			current = current->next;
		}
	}
	llist->tail = prev;
    return numNodes;
}

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list
  * @return 1 if the list is indeed empty 0 otherwise.
  */
int is_empty(list* llist)
{
    return (llist->size == 0 && llist->head == NULL);
}

/** empty_list
  *
  * Empties the list after this is called the list should be empty.
  *
  * @param llist a pointer to a linked list.
  * @param free_func function used to free the node's data.
  *
  */
void empty_list(list* llist, list_op free_func)
{
	if (llist->size == 1) {
		free_func(llist->head->data);
		node *removed = llist->head;
		llist->head = NULL;
		llist->tail = NULL;
		free(removed);
	} else if (llist->size != 0) {
		node *current = llist->head;
		free_func(current->data);
		node *removed = current;
		while (current->next != NULL) {
			current = current->next;
			free(removed);
			removed = current;
			free_func(current->data);
		}
		if (removed != NULL) {
			free(removed);
		}
		llist->head = NULL;
		llist->tail = NULL;
		llist->size = 0;
	}
}
