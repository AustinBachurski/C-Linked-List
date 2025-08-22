/*
* File Name: linked_list.c
* Purpose: Contains type and function definitions for my
*          linked list implementation.
*
* Author: Austin Bachurski
* Date: 08/22/2025
*/

#include "linked_list.h"

#include <stdbool.h>
#include <string.h>

#define FILE_EXTENTION_SIZE 4
#define BUFFER_SIZE 255

// Definition for a linked list node.
// Contains:
// - Pointer to the next node.
// - Integer value being stored.
typedef struct IntegerNode
{
    struct IntegerNode *next;
    int data;
} IntegerNode;


// Initialize the linked list handle.
bool linked_list_initialize(IntegerLinkedList *list)
{
    // Set the head pointer of the list to null.
    list->head = NULL;

    // Set the tail pointer of the list to null.
    list->tail = NULL;

    // Set the element count to zero.
    list->size = 0;

    // Initialization success, return true.
    return true;
}

// Initialize the linked list handle and populate with values from a file.
bool linked_list_initialize_from_file(IntegerLinkedList *list, char const *fileName)
{
    // Ensure a file name is provided, and that it contains enough characters
    // for the file extension + 1 at minimum.
    if (!fileName && strlen(fileName) > FILE_EXTENTION_SIZE)
    {
        printf("ERROR: Please provide the name of a text (.txt) file.\n");
        printf("The list has NOT been initialized!\n");

        // Initialization failed, return false.
        return false;
    }

    // Attempt to open file for reading.
    FILE *file = fopen(fileName, "r");

    if (!file)
    {
        printf("ERROR: Unable to open %s file.\n", fileName);
        printf("The list has NOT been initialized!\n");

        // Initialization failed, return false.
        return false;
    }

    // Buffer value used to hold data read from file.
    //int value = 0;

    // Read text from the file, line by line, converting values to
    // integers and loading them into the list.
    while (fscanf(file, "d"))
    {
        //linked_list_push_back(list, value);
        list->size = 0;
    }

    // Initialization success, return true.
    return true;
}

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
// Print the list.
void linked_list_print_list(IntegerLinkedList const *list)
{
    IntegerNode *node = list->head;

    printf("List contains %zu elements.\n", list->size);
    printf("{");

    while (node)
    {
        printf(" %d", node->data);

        if (node->next)
        {
            printf(",");
        }
    }

    printf(" }\n");
}
