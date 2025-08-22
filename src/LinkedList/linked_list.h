/*
* File Name: linked_list.h
* Purpose: Contains the public type and function declarations for my
*          linked list implementation.
*
* Author: Austin Bachurski
* Date: 08/22/2025
*/

#ifndef BACHURSKI_LINKED_LIST
#define BACHURSKI_LINKED_LIST

#include <stdbool.h>
#include <stdio.h>


// Linked List Handle
// Contains:
// - Pointer to the beginning of the list.
// - Pointer to the end of the list.
// - Number of elements in the list.
typedef struct IntegerLinkedList
{
    struct IntegerNode *head;
    struct IntegerNode *tail;
    size_t size;
} IntegerLinkedList;

// Initialization
bool linked_list_initialize(IntegerLinkedList *list);
bool linked_list_initialize_from_file(IntegerLinkedList *list, char const *fileName);

// Cleanup
void linked_list_cleanup(IntegerLinkedList *list);

// Modifiers
void linked_list_clear(IntegerLinkedList *list);
void linked_list_push_back(IntegerLinkedList *list, int const value);
void linked_list_push_front(IntegerLinkedList *list, int const value);
void linked_list_pop_back(IntegerLinkedList *list);
//void linked_list_pop_front(IntegerLinkedList *list);
//void linked_list_remove_at_index(IntegerLinkedList *list, size_t const index);
//void linked_list_remove_value(IntegerLinkedList *list, int const value);

// Element Access
//int linked_list_back(IntegerLinkedList const *list);
//int linked_list_front(IntegerLinkedList const *list);
//int linked_list_element_at(IntegerLinkedList const *list, size_t const index);

// Search
//size_t linked_list_find_index_of(IntegerLinkedList const *list, int const value);

// Display
void linked_list_print_list(IntegerLinkedList const *list);

#endif

