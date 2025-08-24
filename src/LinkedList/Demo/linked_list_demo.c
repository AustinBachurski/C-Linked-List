#include "linked_list_demo.h"
#include "../linked_list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Issue platform depended calls to clear the console.
static void clear_screen(void )
{
#ifdef __CYGWIN__
    // Windows command to clear the console.
    system("cls");
#else
    // Unix command to clear the console.
    system("clear");
#endif
}

// Begins the interactive demo of the linked list implementation.
void demo_begin(IntegerLinkedList *list)
{
    // Print a welcome message.
    printf("Welcome to the interactive demo for my integer linked list implementation.\n"
           "Details of the linked list will be printed to the console after each operation.\n"
           "An empty linked list has been created and initialized for use.\n\n");

    //char buffer[8];

    return;
    // Loop until the user is satisfied that the implementation meets requirements.
    while (true)
    {
        printf("What would you like to do?\n"
               "1. \n"
               "2. \n"
               "3. \n"
               "4. \n"
               "5. \n"
               "6. \n"
               "7. \n"
               "8. \n"
               "9. \n"
               "10. \n"
               "11. \n"
               "12. \n"
               "13. \n"
               "14. \n"
               "15. \n"
               "16. \n"
               "17. \n"
               "18. \n"
               "19. \n"
               );
    }
}
