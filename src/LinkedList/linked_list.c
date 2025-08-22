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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIMUM_NAME_LENGTH 4
#define BUFFER_SIZE 255
#define READ_SUCCESS 1

// Definition for a linked list node.
// Contains:
// - Pointer to the next node.
// - Pointer to the previous node.
// - Integer value being stored.
typedef struct IntegerNode
{
    struct IntegerNode *next;
    struct IntegerNode *previous;
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
    // for the file extension plus at least one character for the file name.
    if (!fileName && strlen(fileName) > MINIMUM_NAME_LENGTH)
    {
        fprintf(stderr, "ERROR: Please provide the name of a text (.txt) file.\n");
        fprintf(stderr, "The list has NOT been initialized!\n");

        // Initialization failed, return false.
        return false;
    }

    // Attempt to open file for reading.
    FILE *file = fopen(fileName, "r");

    if (!file)
    {
        fprintf(stderr, "ERROR: Unable to open %s file.\n", fileName);
        fprintf(stderr, "The list has NOT been initialized!\n");

        // Initialization failed, return false.
        return false;
    }

    // Buffer value used to hold data read from file.
    int value = 0;

    // Read text from the file, line by line, converting the text to an integer.
    while (fscanf(file, "%d", &value) == READ_SUCCESS)
    {
        // Add the converted integer to the list.
        linked_list_push_back(list, value);
    }

    // Initialization success, return true.
    return true;
}

// Cleanup
void linked_list_cleanup(IntegerLinkedList *list)
{
    linked_list_clear(list);
}

// Modifiers
void linked_list_clear(IntegerLinkedList *list)
{
    IntegerNode *current = list->head;
    IntegerNode *next = NULL;

    while (current)
    {
        next = current->next;

        free(current);

        current = next;
    }

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

void linked_list_push_back(IntegerLinkedList *list, int const value)
{
    IntegerNode *node = (IntegerNode *)malloc(sizeof(IntegerNode));

    if (!node)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        abort();
    }

    node->next = NULL;
    node->data = value;

    if (list->tail)
    {
        node->previous = list->tail;

        list->tail->next = node;
        list->tail = node;
    }
    else
    {
        node->previous = NULL;
        list->head = node;
        list->tail = node;
    }

    ++list->size;
}

void linked_list_push_front(IntegerLinkedList *list, int const value)
{
    IntegerNode *node = (IntegerNode *)malloc(sizeof(IntegerNode));

    if (!node)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        abort();
    }

    node->previous = NULL;
    node->data = value;

    if (list->head)
    {
        node->next = list->head;

        list->head->previous = node;
        list->head = node;
    }
    else
    {
        node->next = NULL;
        list->head = node;
        list->tail = node;
    }
    
    ++list->size;
}

void linked_list_pop_back(IntegerLinkedList *list)
{
    if (!list->tail)
    {
        return;
    }

    if (list->tail->previous)
    {
        list->tail = list->tail->previous;

        free(list->tail->next);

        list->tail->next = NULL;

        --list->size;
    }
    else
    {
        linked_list_clear(list);
    }
}

void linked_list_pop_front(IntegerLinkedList *list)
{
    if (!list->head)
    {
        return;
    }

    if (list->head->next)
    {
        list->head = list->head->next;

        free(list->head->previous);

        list->head->previous = NULL;

        --list->size;
    }
    else
    {
        linked_list_clear(list);
    }
}

void linked_list_remove_at_index(IntegerLinkedList *list, size_t const index)
{
    if (index >= list->size)
    {
        fprintf(stderr, "Attempt to access index out of range!\n");
        fprintf(stderr, "No elements have been removed.\n");
        return;
    }

    IntegerNode *node = list->head;

    size_t nodeIndex = 0;

    while (nodeIndex < index)
    {
        node = node->next;
        ++nodeIndex;
    }

    if (node == list->head)
    {
        linked_list_pop_front(list);
        return;
    }
    
    if (node == list->tail)
    {
        linked_list_pop_back(list);
        return;
    }

    node->previous->next = node->next;
    node->next->previous = node->previous;
    free(node);
    --list->size;
}

void linked_list_remove_value(IntegerLinkedList *list, int const value)
{
    IntegerNode *node = list->head;

    while (node)
    {
        if (node->data == value)
        {
            if (node == list->head)
            {
                linked_list_pop_front(list);
                return;
            }

            if (node == list->tail)
            {
                linked_list_pop_back(list);
                return;
            }

            node->previous->next = node->next;
            node->next->previous = node->previous;
            free(node);
            --list->size;
            return;
        }

        node = node->next;
    }

    fprintf(stderr, "Value %d was not found in the list.\n", value);
    fprintf(stderr, "No values were removed.\n");
}

// TODO: 
// TODO: // Element Access
// TODO: int linked_list_back(IntegerLinkedList const *list);
// TODO: int linked_list_front(IntegerLinkedList const *list);
// TODO: int linked_list_element_at(IntegerLinkedList const *list, size_t const index);
// TODO: 
// TODO: // Search
// TODO: size_t linked_list_find_index_of(IntegerLinkedList const *list, int const value);

// Print the list.
void linked_list_print_list(IntegerLinkedList const *list)
{
    IntegerNode *node = list->head;

    printf("List contains %zu elements.\n", list->size);
    printf("{");

    while (node)
    {
        printf(" %d", node->data);

        if ((node = node->next))
        {
            printf(",");
        }
    }

    printf(" }\n");
}

