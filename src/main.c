/*
* File Name: main.c
* Purpose: Contains the main function with a demo of an implementation
*          of a linked list for storing integers.
*
* Author: Austin Bachurski
* Date: 08/25/2025
*/

// Include the header for the demo and linked list.
#include "LinkedList/linked_list.h"
#include "LinkedList/Demo/linked_list_demo.h"

// Include required cstdlib header.
#include <stdio.h>


// Program entry point.
int main(void)
{
    // Instantiate the linked list.
    IntegerLinkedList list;

    // Initialize the linked list, if initialization fails, exit the program.
    if (!linked_list_initialize(&list))
    {
        printf("Failed to initialize the list!\n");
        return 1;
    }

    // Begin the demo of the implementation.
    demo_begin(&list);

    // Clean up any allocated resources.
    linked_list_cleanup(&list);

    // Exit normally.
    return 0;
}

