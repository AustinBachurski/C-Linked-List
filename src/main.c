/*
* File Name: main.c
* Purpose: Contains the main function with a demo of an implementation
*          of a linked list for storing integers.
*
* Author: Austin Bachurski
* Date: 08/23/2025
*/

#include "LinkedList/linked_list.h"
#include "LinkedList/Demo/linked_list_demo.h"

#include <stdio.h>


int main(void)
{
    IntegerLinkedList list;

    if (!linked_list_initialize(&list))
    {
        printf("Failed to initialize the list!\n");
        return 1;
    }

    demo_begin(&list);

    linked_list_cleanup(&list);

    return 0;
}

