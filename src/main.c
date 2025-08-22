/*
* TODO:
* MINIMUM REQUIREMENTS:
*   - Add or delete items at the beginning of the list.
*   - Remove items from the end of the list.
*   - Remove a specific item by index OR by value.
*
*   THE PROGRAM WILL BE INTERACTIVE: At a minimum, the end-user will be able to print the list to the screen and add and delete values using the methods above.
*   - The user will be able to search the list for a particular value.
*   - The user will be able to input values USING A TEXT FILE AND OUTPUT THE LIST TO A TEXT FILE.
*
*   FUNCTION DEFINITIONS SHOULD BE CONTAINED IN A SINGLE SECTION AT THE BEGINNING OF THE PROGRAM - ???
*
*
*   Add a comment block at the beginning to indicate the purpose of the program.
*   - EXAMPLE TEMPLATE:
*
* File Name: linked_list.h
* Purpose: Contains type and function definitions for my
*          linked list implementation.
*
* Author: Austin Bachurski
* Date: 08/22/2025
*
*
*   Add comments before each structure, function definition, loop and update statement.
*   - COMMENT EACH:
*       - Structure
*       - Function Definition
*       - Loop
*       - Update to a variable, yes even this has to be commented...
*/






#include "LinkedList/linked_list.h"
#include <stdio.h>


int main(void)
{
    IntegerLinkedList list;

    if (!linked_list_initialize_from_file(&list, "test_input.txt"))
    {
        printf("Failed to initialize list!\n");
        return 1;
    }

    linked_list_print_list(&list);




    linked_list_pop_front(&list);
    linked_list_print_list(&list);
    linked_list_pop_front(&list);
    linked_list_print_list(&list);
    linked_list_pop_front(&list);




    linked_list_print_list(&list);
    linked_list_cleanup(&list);

    return 0;
}

