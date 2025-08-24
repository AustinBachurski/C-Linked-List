/*
* File Name: main.c
* Purpose: Contains the main function with a demo of an implementation
*          of a linked list for storing integers.
*
* Author: Austin Bachurski
* Date: 08/22/2025
*/

#include "LinkedList/linked_list.h"
#include <stdio.h>


int main(void)
{
    IntegerLinkedList list;

    if (!linked_list_initialize(&list))
    {
        printf("Failed to initialize the list!\n");
        return 1;
    }

    linked_list_load_data_from_file(&list, "test_input.txt");

    linked_list_print_list(&list);

    linked_list_remove_value(&list, 1);




    linked_list_print_list(&list);
    linked_list_cleanup(&list);

    return 0;
}

