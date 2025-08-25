#include "linked_list_demo.h"
#include "../linked_list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_BUFFER_LEN 255
#define FORMATTER_SIZE 16

// Issue platform depended calls to clear the console.
static void clear_screen(void )
{
#ifdef __CYGWIN__
    // Windows command to clear the console.
    system("cls");
#else
    // Unix command to clear the console.
    if (system("clear"))
    {
        fprintf(stderr, "\nClear screen failed!\n");
    }
#endif
}

static void print_list_after(IntegerLinkedList *list)
{
    printf("List after requested operation:\n");
    linked_list_print_list(list);
}

static void print_list_before(IntegerLinkedList *list)
{
    printf("List before requested operation:\n");
    linked_list_print_list(list);
}

static bool is_empty(IntegerLinkedList *list)
{
    if (list->size == 0)
    {
        printf("List contains no elements to remove, add a value first.\n");
        return true;
    }
    return false;
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

static void read_string_from_console(char *buffer, char const *message)
{
    printf("%s", message);

    char format_string[FORMATTER_SIZE] = { 0 };
    sprintf(format_string, "%%%ds", INPUT_BUFFER_LEN - 1);

    while (scanf(format_string, buffer) != 1) { }
    while (getchar() != '\n') { }
}

static size_t read_valid_index_from_console(IntegerLinkedList *list,
                                            char const *message)
{
    printf("%s", message);

    size_t choice = list->size + 1;

    if (choice == 0)
    {
        while(scanf("%zu", &choice) != 1)
        {
            printf("Only positive integers please, enter a number: ");
            while (getchar() != '\n') { }
        }

        return choice;
    }

    while (choice >= list->size)
    {
        while(scanf("%zu", &choice) != 1)
        {
            printf("Only positive integers please, enter a number: ");
            while (getchar() != '\n') { }
        }

        if (choice >= list->size)
        {
            printf("That index it out of the bounds of the list and cannot be used.\n");
            linked_list_print_list(list);
            printf("Please enter a valid index: ");
        }
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

    print_list_before(list);
    linked_list_push_front(list, value);
    print_list_after(list);
}

static void pop_front(IntegerLinkedList *list)
{
    clear_screen();

    print_list_before(list);
    linked_list_pop_front(list);
    print_list_after(list);
}

static void push_back(IntegerLinkedList *list)
{
    clear_screen();

    int value = read_number_from_console("Enter the number you wish to add: ");

    print_list_before(list);
    linked_list_push_back(list, value);
    print_list_after(list);
}

static void pop_back(IntegerLinkedList *list)
{
    clear_screen();
    print_list_before(list);
    linked_list_pop_back(list);
    print_list_after(list);
}

static void remove_at_index(IntegerLinkedList *list)
{
    clear_screen();

    linked_list_print_list(list);

    size_t index = read_valid_index_from_console(list, 
        "Enter the index for the value you with to remove: ");

    print_list_before(list);

    linked_list_remove_at_index(list, index);

    print_list_after(list);
}

static void print_list(IntegerLinkedList *list)
{
    clear_screen();

    linked_list_print_list(list);
}

static void search_list(IntegerLinkedList *list)
{
    clear_screen();

    linked_list_print_list(list);

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

static void add_from_file(IntegerLinkedList *list)
{
    clear_screen();

    char buffer[INPUT_BUFFER_LEN] = { 0 };

    read_string_from_console(buffer, "Enter the file name: ");

    print_list_before(list);

    linked_list_load_data_from_file(list, buffer);

    print_list_after(list);
}

static void output_to_file(IntegerLinkedList *list)
{
    clear_screen();

    char buffer[INPUT_BUFFER_LEN] = { 0 };

    read_string_from_console(buffer, "Enter the file name: ");

    linked_list_output_to_file(list, buffer);

    printf("List contents written to '%s'\n", buffer);

    linked_list_print_list(list);
}

static void read_front(IntegerLinkedList *list)
{
    clear_screen();

    linked_list_print_list(list);

    printf("Value at the beginning of the list: %d\n\n", linked_list_front(list));
}

static void read_back(IntegerLinkedList *list)
{
    clear_screen();

    linked_list_print_list(list);

    printf("Value at the end of the list: %d\n\n", linked_list_back(list));
}

static void read_at_index(IntegerLinkedList *list)
{
    clear_screen();

    linked_list_print_list(list);

    size_t index = read_valid_index_from_console(list, 
        "Enter the index for the value you with to view: ");

    printf("Value at index %zu: %d\n\n", index, linked_list_element_at(list, index));
}

static void clear_list(IntegerLinkedList *list)
{
    clear_screen();

    print_list_before(list);

    linked_list_clear(list);

    print_list_after(list);
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
                if (is_empty(list)) { continue; }

                pop_front(list);
                break;

            case 3:
                push_back(list);
                break;

            case 4:
                if (is_empty(list)) { continue; }

                pop_back(list);
                break;

            case 5:
                if (is_empty(list)) { continue; }

                remove_at_index(list);
                break;

            case 6:
                print_list(list);
                break;

            case 7:
                search_list(list);
                break;

            case 8:
                add_from_file(list);
                break;

            case 9:
                output_to_file(list);
                break;

            case 10:
                if (is_empty(list)) { continue; }

                read_front(list);
                break;

            case 11:
                if (is_empty(list)) { continue; }

                read_back(list);
                break;

            case 12:
                if (is_empty(list)) { continue; }

                read_at_index(list);
                break;

            case 13:
                clear_list(list);
                break;

            default:
                printf("** Invalid Selection Received, please try again. **\n");
                continue;
        }
        print_menu();
    }
}
