/*
* File Name: linked_list.c
* Purpose: Contains constants, types, and function definitions for my
*          linked list implementation.
*
* Author: Austin Bachurski
* Date: 08/25/2025
*/

// Include the header for the linked list.
#include "linked_list.h"

// Include required cstdlib headers.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defines a constant which will be used to check the string lenth of the 
// file name passed to load_data_from_file().
#define MINIMUM_NAME_LENGTH 4

// Defines a constant which will be used to indicate that a value was
// successfully read from the input file in load_data_from_file().
#define READ_SUCCESS 1

// Internal function that prints a diagnostic message and aborts the program in
// the unlikely event that memory allocation fails.
static void internal_bad_alloc(void)
{
    fprintf(stderr, "Memory allocation failed!\n");
    abort();
}

// Internal function that prints a diagnostic message and aborts the program if
// the user attempts to access an index which is outside the bounds of the list.
static void internal_out_of_bounds(size_t const size, size_t const index)
{
    fprintf(stderr, "Attempt to access index out of range!\n");
    fprintf(stderr, "Index %zu of list with size %zu.\n", index, size);
    abort();
}

// Definition for a linked list node.
// Contains:
// - Pointer to the `next` node.
// - Pointer to the `previous` node.
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
void linked_list_load_data_from_file(IntegerLinkedList *list, char const *fileName)
{
    // Ensure a file name is provided, and that it contains enough characters
    // for the file extension plus at least one character for the file name.
    // If not, print a diagnostic message and return early.
    if (!fileName || strlen(fileName) < MINIMUM_NAME_LENGTH)
    {
        fprintf(stderr, "ERROR: Please provide the name of a text (.txt) file.\n");
        return;
    }

    // Attempt to open a file of the the provided name file for reading.
    FILE *file = fopen(fileName, "r");

    // If the file failed to open print a diagnostic message and return early.
    if (!file)
    {
        fprintf(stderr, "ERROR: Unable to open %s file.\n", fileName);
        return;
    }

    // Buffer value used to hold data read from a single line in the file.
    int value = 0;

    // Read text from the file, line by line, converting the text to an
    // integer and storing it in the previously defined value buffer.
    while (fscanf(file, "%d", &value) == READ_SUCCESS)
    {
        // Add the previously read integer to the list.
        linked_list_push_back(list, value);
    }

    // Close the file, releasing the resource back to the system.
    fclose(file);
}

// Cleanup function that frees all allocated memory resources.  The
// implementation of cleanup() would've been the same as clear(), so 
// the program simply calls the clear() function.
void linked_list_cleanup(IntegerLinkedList *list)
{
    linked_list_clear(list);
}

// Clears the linked list by iterating over every node and freeing that node
// before finally setting the head and tail pointers of the list handle
// to null.
void linked_list_clear(IntegerLinkedList *list)
{
    // Store two pointers, the current pointer and the next pointer in the
    // list.  Store `next` because if `current` is freed without a handle to the
    // next node, the chain is broken and a memory leak will result.
    IntegerNode *current = list->head;
    IntegerNode *next = NULL;

    // Starting at the head, loop through every node in the list, stopping
    // once current is null.
    while (current)
    {
        // Store the pointer for the next node in the list.
        next = current->next;

        // Free the current node.
        free(current);

        // Assign the `next` pointer to `current` so that the loop will continue.
        current = next;
    }

    // Once every node in the loop has been cleared, set the element count to 
    // zero, and set both the head and tail pointers of the list handle to null.
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

// Appends a node to the end of the list that stores the value passed as an
// argument.
void linked_list_push_back(IntegerLinkedList *list, int const value)
{
    // Alocate memory for the new node.
    IntegerNode *node = (IntegerNode *)malloc(sizeof(IntegerNode));

    // If allocation fails, print a diagnostic message and abort the program.
    if (!node) { internal_bad_alloc(); }

    // Since the node will be at the end of the list, the `next` pointer  will
    // be null.
    node->next = NULL;

    // Assign the value of the argument to the node.
    node->data = value;

    // If the `tail` pointer is not null a node exists at the end of the list.
    if (list->tail)
    {
        // Set the local node's `previous` pointer to point to the last node
        // currently in the list.
        node->previous = list->tail;

        // Set the `next` pointer of the last node currently in the list to 
        // the local node, inserting the node into the list.
        list->tail->next = node;

        // Set the `tail` pointer of the list handle to the local node, which
        // was previously inserted into the end of the list.
        list->tail = node;
    }
    else
    {
        // If tail is null there are no nodes in the list, so set the `previous`
        // pointer to null, and point both `head` and `tail` to the local node,
        // interting it into the list.
        node->previous = NULL;
        list->head = node;
        list->tail = node;
    }

    // Increment the list size following node insertion.
    ++list->size;
}

// Appends a node to the front of the list that stores the value passed as an
// argument.
void linked_list_push_front(IntegerLinkedList *list, int const value)
{
    // Alocate memory for the new node.
    IntegerNode *node = (IntegerNode *)malloc(sizeof(IntegerNode));

    // If allocation fails, print a diagnostic message and abort the program.
    if (!node) { internal_bad_alloc(); }

    // Since the node will be at the front of the list, the `previous` pointer
    // will be null.
    node->previous = NULL;

    // Assign the value of the argument to the node.
    node->data = value;

    // If the `head` pointer is not null a node exists at the front of the list.
    if (list->head)
    {
        // Set the local node's `next` pointer to point to the first node
        // currently in the list.
        node->next = list->head;

        // Set the `previous` pointer of the first node currently in the list to 
        // the local node, inserting the node into the list.
        list->head->previous = node;

        // Set the `head` pointer of the list handle to the local node, which
        // was previously inserted into the front of the list.
        list->head = node;
    }
    else
    {
        // If head is null there are no nodes in the list, so set the `next`
        // pointer to null, and point both `head` and `tail` to the local node,
        // interting it into the list.
        node->next = NULL;
        list->head = node;
        list->tail = node;
    }
    
    // Increment the list size following node insertion.
    ++list->size;
}

// Removes the last node in the list.
void linked_list_pop_back(IntegerLinkedList *list)
{
    // If the `tail` pointer of the handle is null, the list is empty.
    if (!list->tail) { return; }

    // Check that the node pointed too by tail also points to a previous node.
    if (list->tail->previous)
    {
        // Set the `tail` pointer of the handle to point to the second to
        // last node in the list.
        list->tail = list->tail->previous;

        // Use the `next` pointer of the second to last node in the list to
        // free the last node in the list, removing the item from the list
        // and relinquishing it's memory resource.
        free(list->tail->next);

        // After freeing, set the `next` pointer of the last node in the list 
        // to null.
        list->tail->next = NULL;

        // Decrement the number of elements in the list.
        --list->size;
    }
    else
    {
        // If the tail node does not point to another node, there is only
        // one element in the list, so simply call clear().
        linked_list_clear(list);
    }
}

// Removes the first node in the list.
void linked_list_pop_front(IntegerLinkedList *list)
{
    // If the `head` pointer of the handle is null, the list is empty.
    if (!list->head) { return; }

    // Check that the node pointed too by head also points to a next node.
    if (list->head->next)
    {
        // Set the `head` pointer of the handle to point to the second node
        // in the list.
        list->head = list->head->next;

        // Use the `previous` pointer of the second node in the list to
        // free the first node in the list, removing the item from the list
        // and relinquishing it's memory resource.
        free(list->head->previous);

        // After freeing, set the `previous` pointer of the first node in the
        // list to null.
        list->head->previous = NULL;

        // Decrement the number of elements in the list.
        --list->size;
    }
    else
    {
        // If the head node does not point to another node, there is only
        // one element in the list, so simply call clear().
        linked_list_clear(list);
    }
}

// Removes a the node at the specified index.
void linked_list_remove_at_index(IntegerLinkedList *list, size_t const index)
{
    // If the index passed as an argument is greater than the number of
    // elements in the list, print a diagnostic message and abort.
    if (index >= list->size) { internal_out_of_bounds(list->size, index); }

    // Store a pointer to the first node in the list.
    IntegerNode *node = list->head;

    // Declare and zero out an accumulator variable to track the current index.
    size_t nodeIndex = 0;

    // Iterate through the list until the node at the desired index is found, 
    // or the end of the list is reached.
    while (nodeIndex < index)
    {
        // Each iteration of the loop, store the pointer to the next node,
        // and increment the accumulator.
        node = node->next;
        ++nodeIndex;
    }

    if (node == list->head)
    {
        // If after iteration is finished, the desired node is at the front of the
        // list, simply call pop_front() and return.
        linked_list_pop_front(list);
        return;
    }
    
    if (node == list->tail)
    {
        // If after iteration is finished, the desired node is at the back of the
        // list, simply call pop_back() and return.
        linked_list_pop_back(list);
        return;
    }

    // Otherwise, set the `next` pointer of the previous node to point to the
    // next node in the list.
    node->previous->next = node->next;

    // Then set the `previous` pointer of the next node to point to the previous
    // node in the list, removing the node from the list.
    node->next->previous = node->previous;

    // The local node points to the removed node, free said node, relinquishing
    // it's memory resource.
    free(node);

    // Decrement the number of elements in the list.
    --list->size;
}

// Removes all nodes from the list that contain the specified value.
void linked_list_remove_value(IntegerLinkedList *list, int const value)
{
    // Store a pointer to the first node in the list.
    IntegerNode *node = list->head;

    // Iterate through the list until a node with the desired value if found,
    // or the end of the list is reached.
    while (node)
    {
        if (node->data == value)
        {
            // When a node containing the desired value is found, check if the
            // node is at the beginning of the list, if so, set the local node
            // to point to the next node, call pop_front() and continue iteration.
            if (node == list->head)
            {
                node = node->next;
                linked_list_pop_front(list);
                continue;
            }

            // When a node containing the desired value is found, check if the
            // node is at the end of the list, if so, simply call
            // pop_back() and since that's the last element in the list, return.
            if (node == list->tail)
            {
                linked_list_pop_back(list);
                return;
            }

            // Otherwise, set the `next` pointer of the previous node to point
            // to the next item in the list.
            node->previous->next = node->next;

            // Then set the `previous` pointer of the next node to point to the
            // previous node in the list.
            node->next->previous = node->previous;

            // Store a pointer to the node after the one about to be freed.
            // This must be done because after freeing the node, the pointer to
            // the next link in the chain is lost.
            IntegerNode *temp = node->next;

            // The local node points to the removed node, free said node,
            // relinquishing it's memory resource.
            free(node);

            // Decrement the number of elements in the list.
            --list->size;

            // Set the local node to be the temporary node previously stored,
            // allowing the next iteration to continue where it left off.
            node = temp;

            // Finally `continue` is called to avoid skipping over the next node.
            continue;
        }
        // Update the local node to point to the next node in the list,
        // continuing iteration.
        node = node->next;
    }
}

// Returns the value stored by the last node in the list.
int linked_list_back(IntegerLinkedList const *list)
{
    return list->tail->data;
}

// Returns the value stored by the first node in the list.
int linked_list_front(IntegerLinkedList const *list)
{
    return list->head->data;
}

// Returns the value stored at the specified node.
int linked_list_element_at(IntegerLinkedList const *list, size_t const index)
{
    // If the index passed as an argument is greater than the number of
    // elements in the list, print a diagnostic message and abort.
    if (index >= list->size) { internal_out_of_bounds(list->size, index); }

    // Store a pointer to the first node in the list.
    IntegerNode *node = list->head;

    // Declare and zero out an accumulator variable to track the current index.
    size_t nodeIndex = 0;

    // Iterate through the list until the node at the desired index is found. 
    while (nodeIndex < index)
    {
        // Each iteration of the loop, store the pointer to the next node,
        // and increment the accumulator.
        node = node->next;
        ++nodeIndex;
    }

    // After the desired node is found, return the value it contains.
    return node->data;
}

// TODO: Incessent comments...
void linked_list_output_to_file(IntegerLinkedList *list, char const *fileName)
{
    // Ensure a file name is provided, and that it contains enough characters
    // for the file extension plus at least one character for the file name.
    // If not, print a diagnostic message and return early.
    if (!fileName || strlen(fileName) < MINIMUM_NAME_LENGTH)
    {
        fprintf(stderr, "ERROR: Please provide the name of a text (.txt) file.\n");
        return;
    }

    // Attempt to open a file of the the provided name file for writing.
    FILE *file = fopen(fileName, "w");

    // If the file failed to open print a diagnostic message and return early.
    if (!file)
    {
        fprintf(stderr, "ERROR: Unable to open %s file.\n", fileName);
        return;
    }

    // Store a pointer to the first node in the list.
    IntegerNode *node = list->head;

    // Log the number of elements in the list with appropriate grammar.
    if (list->size == 1)
    {
        fprintf(file, "List contains %zu element.\n", list->size);
    }
    else
    {
        fprintf(file, "List contains %zu elements.\n", list->size);
    }

    // Log an opening brace, indicating the start of the list elements.
    fprintf(file, "{");

    // Iterate through every node in the list.
    while (node)
    {
        // Log the value stored in the current node, preceded by a space.
        fprintf(file, " %d", node->data);

        // If there is another node in the list, log a comma to communicate
        // separate elements of the list.
        if ((node = node->next)) { fprintf(file, ","); }
    }

    // Finally, log the closing brace padded by one space and followed by a 
    // newline to the console to communicate the end of the list..
    fprintf(file, " }\n\n");
    
    // Close the file, releasing the resource back to the system.
    fclose(file);
}

// Returns the index of the first node that contains the desired value if the 
// value exists in the list, otherwise the size of the list is returned.
size_t linked_list_find_first_index_containing(IntegerLinkedList const *list, int const value)
{
    // Store a pointer to the first node in the list.
    IntegerNode *node = list->head;

    // Declare and zero out an accumulator variable to track the current index.
    size_t index = 0;

    // Iterate through the list until the node at the desired index is found. 
    while (node)
    {
        // If the current node contains the desired value, return the value
        // stored in the accumulator.
        if (node->data == value) { return index; }

        // Each iteration of the loop, store the pointer to the next node,
        // and increment the accumulator.
        node = node->next;
        ++index;
    }

    // If the end of the list is reached without finding the specified value,
    // return the value stored in the accumulator.  This value will be equal
    // to the size of the list, allowing the caller an easy way to check for 
    // value not found.  i.e. `if (return_value == list.size) { //not found }`
    return index;
}

// Print the size of the list as well as each element in the list to stdout.
void linked_list_print_list(IntegerLinkedList const *list)
{
    // Store a pointer to the first node in the list.
    IntegerNode *node = list->head;

    // Print the number of elements in the list with appropriate grammar.
    if (list->size == 1)
    {
        printf("List contains %zu element.\n", list->size);
    }
    else
    {
        printf("List contains %zu elements.\n", list->size);
    }

    // Print an opening brace, indicating the start of the list elements.
    printf("{");

    // Iterate through every node in the list.
    while (node)
    {
        // Print the value stored in the current node, preceded by a space.
        printf(" %d", node->data);

        // If there is another node in the list, print a comma to communicate
        // separate elements of the list.
        if ((node = node->next)) { printf(","); }
    }

    // Finally, print the closing brace padded by one space and followed by a 
    // newline to the console to communicate the end of the list..
    printf(" }\n\n");
}

