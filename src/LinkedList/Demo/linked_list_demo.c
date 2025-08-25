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

static int read_number_from_console(char const *message)
{
    printf("%s", message);

    int choice = -1;

    while(scanf("%d", &choice) != 1)
    {
        printf("Only integers please, enter a number: ");
        while (getchar() != '\n') { }
    }

    return choice;
}

static void print_menu(void)
{
    printf("What would you like to do?\n"
           "Required Operations:\n"
           "\t0. Exit the demo.\n"
           "\t1. Add a number to the beginning of the list.\n"
           "\t2. Remove a number from the beginning of the list.\n"
           "\t3. Add a number to the end of the list.\n"
           "\t4. Remove a number from the end of the list.\n"
           "\t5. Remove the number at a specific index from the list.\n"
           "\t6. Print the list.\n"
           "\t7. Search the list for a specific number.\n"
           "\t8. Add numbers from a text file.\n"
           "\t9. Output the list to a text file.\n"
           "Additional Operations:\n"
           "\t10. Read the number at the front of the list.\n"
           "\t11. Read the number at the end of the list.\n"
           "\t12. Read the element at a specific index in the list.\n"
           "\t13. Clear the contents of the list.\n\n");
}

static void push_front(IntegerLinkedList *list)
{
    clear_screen();

    int value = read_number_from_console("Enter the number you wish to add: ");

    linked_list_push_front(list, value);
    linked_list_print_list(list);
}

static void pop_front(IntegerLinkedList *list)
{
    clear_screen();

    linked_list_pop_front(list);
    linked_list_print_list(list);
}

static void push_back(IntegerLinkedList *list)
{
    clear_screen();

    int value = read_number_from_console("Enter the number you wish to add: ");

    linked_list_push_back(list, value);
    linked_list_print_list(list);
}

static void pop_back(IntegerLinkedList *list)
{
    clear_screen();
    linked_list_pop_back(list);
    linked_list_print_list(list);
}

static void print_list(IntegerLinkedList *list)
{
    clear_screen();
    linked_list_print_list(list);
}

static void search_list(IntegerLinkedList *list)
{
    clear_screen();
    int value = read_number_from_console("Enter the number you wish to find: ");
    size_t index = linked_list_find_first_index_containing(list, value);
    
    if (index == list->size)
    {
        printf("The value %d was not found in the list.\n\n", value);
    }
    else
    {
        printf("The value %d was found at index %zu.\n\n", value, index);
    }
}

// Begins the interactive demo of the linked list implementation.
void demo_begin(IntegerLinkedList *list)
{
    // Print a welcome message.
    printf("Welcome to the interactive demo for my integer linked list implementation.\n"
           "Details of the linked list will be printed to the console after each operation.\n"
           "An empty linked list has been created and initialized for use.\n\n");

    print_menu();
    char const *prompt = "Please make a numeric selection: ";

    // Loop until the user is satisfied that the implementation meets requirements.
    while (true)
    {
        switch (read_number_from_console(prompt))
        {
            case 0:
                return;

            case 1:
                push_front(list);
                break;

            case 2:
                pop_front(list);
                break;

            case 3:
                push_back(list);
                break;

            case 4:
                pop_back(list);
                break;

            case 5:
                break;

            case 6:
                print_list(list);
                break;

            case 7:
                search_list(list);
                break;

            case 8:
                break;

            case 9:
                break;

            case 10:
                break;

            case 11:
                break;

            case 12:
                break;

            case 13:
                break;

            default:
                printf("** Invalid Selection Received, please try again. **\n");
                continue;
        }
        print_menu();
    }
}
