/*
* File Name: linked_list.c
* Purpose: Contains type and function definitions for my
*          linked list implementation.
*
* Author: Austin Bachurski
* Date: 08/22/2025
*/

#include "linked_list.h"

typedef struct IntegerNode
{
    struct IntegerNode *next;
    int data;
} IntegerNode;


// TODO: // Initialization
// TODO: void linked_list_initialize(IntegerLinkedList *list);
// TODO: void linked_list_initialize_from_file(IntegerLinkedList *list, char const *fileName);
// TODO: 
// TODO: // Cleanup
// TODO: void linked_list_cleanup(IntegerLinkedList *list);
// TODO: 
// TODO: // Modifiers
// TODO: void linked_list_clear(IntegerLinkedList *list);
// TODO: void linked_list_push_back(IntegerLinkedList *list, int const value);
// TODO: void linked_list_push_front(IntegerLinkedList *list, int const value);
// TODO: void linked_list_pop_back(IntegerLinkedList *list);
// TODO: void linked_list_pop_front(IntegerLinkedList *list);
// TODO: void linked_list_remove_at_index(IntegerLinkedList *list, size_t const index);
// TODO: void linked_list_remove_value(IntegerLinkedList *list, int const value);
// TODO: 
// TODO: // Element Access
// TODO: int linked_list_back(IntegerLinkedList const *list);
// TODO: int linked_list_front(IntegerLinkedList const *list);
// TODO: int linked_list_element_at(IntegerLinkedList const *list, size_t const index);
// TODO: 
// TODO: // Search
// TODO: size_t linked_list_find_index_of(IntegerLinkedList const *list, int const value);
// TODO: 
// TODO: // Display
// TODO: void linked_list_print_list(IntegerLinkedList const *list);
