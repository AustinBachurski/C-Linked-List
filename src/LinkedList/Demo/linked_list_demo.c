/*
* File Name: linked_list_demo.c
* Purpose: Contains the constants and function definitions for my
*          linked list demo.
*
* Author: Austin Bachurski
* Date: 08/25/2025
*/

// Include the header for the demo and linked list.
#include "linked_list_demo.h"
#include "../linked_list.h"

// Include required cstdlib headers.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defines a constant used to set the size of the buffer for storing user input.
#define INPUT_BUFFER_LEN 255

// Defines a constant used to set the size of the format string buffer used
// to limit the length of user input read to prevent input buffer overflow.
#define FORMATTER_SIZE 16

// Defines a constant which will be used to indicate that a value was
// successfully read from the input file in load_data_from_file().
#define READ_SUCCESS 1

// Issue platform depended calls to clear the console.
static void clear_screen(void )
{
// Terminal command to clear the screen is different between Windows and Unix.
// Conditional compilation for Windows environment.
#if defined(_WIN32) || defined(_WIN64)
    // Windows command to clear the console, print a diagnostic message if the 
    // system call returns an error.
    if (system("cls"))
    {
        fprintf(stderr, "\nClear screen failed!\n");
    }
// Conditional compilation for Unix environment.
#else
    // Unix command to clear the console, print a diagnostic message if the 
    // system call returns an error.
    if (system("clear"))
    {
        fprintf(stderr, "\nClear screen failed!\n");
    }
// End conditional compilation.
#endif
}

// Prints the size and contents of the list following a user requested operation.
static void print_list_after(IntegerLinkedList *list)
{
    printf("List after requested operation:\n");
    linked_list_print_list(list);
}

// Prints the size and contents of the list following a user requested operation.
static void print_list_before(IntegerLinkedList *list)
{
    printf("List before requested operation:\n");
    linked_list_print_list(list);
}

// Prints an informational message and returns true if the list is empty.
// Returns false if the list is not empty.
static bool is_empty(IntegerLinkedList *list)
{
    if (list->size == 0)
    {
        printf("List contains no elements to remove, add a value first.\n");
        return true;
    }
    return false;
}

// Reads a valid integer from the user.
static int read_number_from_console(char const *message)
{
    // Print the passed message to the terminal.
    printf("%s", message);

    // Initialize a buffer variable.
    int choice = -1;

    // Loop until the user provides an integer value, invalid characters will
    // continue the loop and prompt the user to enter a valid number.
    while(scanf("%d", &choice) != 1)
    {
        printf("Only integers please, enter a number: ");

        // Depending on what the user entered, there may be data left in the 
        // input buffer.  This loop clears that data from the input buffer so
        // that the next read is clean of stale input.
        while (getchar() != '\n') { }
    }

    // Return the entered number.
    return choice;
}

// Reads a string from the user.
static void read_string_from_console(char *buffer, char const *message)
{
    // Print the passed message to the terminal.
    printf("%s", message);

    // Defines the format string which is then passed to scanf.
    // The constant for the buffer size defined at the start of this file is 
    // used to limit the number of characters read into the buffer, minus one
    // for the null termination character.
    char format_string[FORMATTER_SIZE] = { 0 };
    sprintf(format_string, "%%%ds", INPUT_BUFFER_LEN - 1);

    // Loop until the user provides a valid string.
    while (scanf(format_string, buffer) != READ_SUCCESS) { }

    // Depending on what the user entered, there may be data left in the 
    // input buffer.  This loop clears that data from the input buffer so
    // that the next read is clean of stale input.
    while (getchar() != '\n') { }
}

// Reads a valid index from the user, index being of the size_t type.
static size_t read_valid_index_from_console(IntegerLinkedList *list,
                                            char const *message)
{
    // Print the passed message to the terminal.
    printf("%s", message);

    // Initialize a buffer variable with the list size + 1.
    size_t choice = list->size + 1;

    // If the +1 causes the list size to wrap, the list is of size SIZE_MAX and
    // any value in that range is valid.
    if (choice == 0)
    {
        // Loop until the user provides a valid index.
        while(scanf("%zu", &choice) != READ_SUCCESS)
        {
            printf("Only positive integers please, enter a index: ");

            // Depending on what the user entered, there may be data left in the 
            // input buffer.  This loop clears that data from the input buffer so
            // that the next read is clean of stale input.
            while (getchar() != '\n') { }
        }

        // Return the entered index.
        return choice;
    }

    // Loop until the user provides a valid index that is within the bounds
    // of the list.
    while (choice >= list->size)
    {
        // Loop until the user provides a valid index.
        while(scanf("%zu", &choice) != 1)
        {
            printf("Only positive integers please, enter a number: ");
            //
            // Depending on what the user entered, there may be data left in the 
            // input buffer.  This loop clears that data from the input buffer so
            // that the next read is clean of stale input.
            while (getchar() != '\n') { }
        }

        // If the entered index is outside the bounds of the list, print a 
        // diagnostic message, display the list, and request a valid index
        // before continuing the loop.
        if (choice >= list->size)
        {
            printf("That index it out of the bounds of the list and cannot be used.\n");
            linked_list_print_list(list);
            printf("Please enter a valid index: ");
        }
    }

    // Return the valid index.
    return choice;
}

// Displays the available options for the demo.
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
           "\t6. Remove a specific number from the list.\n"
           "\t7. Print the list.\n"
           "\t8. Search the list for a specific number.\n"
           "\t9. Add numbers from a text file.\n"
           "\t10. Output the list to a text file.\n"
           "Additional Operations:\n"
           "\t11. Read the number at the front of the list.\n"
           "\t12. Read the number at the end of the list.\n"
           "\t13. Read the element at a specific index in the list.\n"
           "\t14. Clear the contents of the list.\n\n");
}

// Adds a value to the front of the list and displays the results to the user.
static void push_front(IntegerLinkedList *list)
{
    clear_screen();

    int value = read_number_from_console("Enter the number you wish to add: ");

    print_list_before(list);
    linked_list_push_front(list, value);
    print_list_after(list);
}

// Removes a value from the front of the list and displays the results to the user.
static void pop_front(IntegerLinkedList *list)
{
    clear_screen();
    print_list_before(list);
    linked_list_pop_front(list);
    print_list_after(list);
}

// Adds a value to the end of the list and displays the results to the user.
static void push_back(IntegerLinkedList *list)
{
    clear_screen();

    int value = read_number_from_console("Enter the number you wish to add: ");

    print_list_before(list);
    linked_list_push_back(list, value);
    print_list_after(list);
}

// Removes a value from the end of the list and displays the results to the user.
static void pop_back(IntegerLinkedList *list)
{
    clear_screen();
    print_list_before(list);
    linked_list_pop_back(list);
    print_list_after(list);
}

// Removes a value from the specified index and displays the results to the user,
// displays the list before requesting the index for ease of selection.
static void remove_at_index(IntegerLinkedList *list)
{
    clear_screen();
    linked_list_print_list(list);

    // Retrieve an index from the user.
    size_t index = read_valid_index_from_console(list, 
        "Enter the index for the value you with to remove: ");

    print_list_before(list);
    linked_list_remove_at_index(list, index);
    print_list_after(list);
}

// Removes all occurances of a value from the list.
static void remove_number(IntegerLinkedList *list)
{
    clear_screen();
    linked_list_print_list(list);

    // Retrieve a number from the user.
    int value = read_number_from_console("Enter the number you with to remove: ");

    // Store the size before the removal.
    size_t before = list->size;

    print_list_before(list);
    linked_list_remove_value(list, value);

    // If the list is the same size before an after the operation, the number
    // didn't exist in the list.
    if (before == list->size)
    {
        printf("No occurances of %d to remove.\n\n", value);
    }
    // If the list is smaller after the operation, report how many elements 
    // were removed from the list.
    else
    {
        printf("Removed %zu occurances of %d.\n\n", before - list->size, value);
    }

    print_list_after(list);
}

// Clears the screen and displays the list.
static void print_list(IntegerLinkedList *list)
{
    clear_screen();
    linked_list_print_list(list);
}

// Searches the list for a specified value, displays the index if found, displays
// a 'not found' message if not.
static void search_list(IntegerLinkedList *list)
{
    clear_screen();
    linked_list_print_list(list);

    // Retrieve a value to search for from the user.
    int value = read_number_from_console("Enter the number you wish to find: ");

    // Retrieve the index of the stored value.  If the value was not found then
    // `index` will be equal to `list->size`.
    size_t index = linked_list_find_first_index_containing(list, value);
    
    // If the value was not found, inform the user.
    if (index == list->size)
    {
        printf("The value %d was not found in the list.\n\n", value);
    }
    // If the value was found, display the index of the first matching value.
    else
    {
        printf("The value %d was first found at index %zu.\n\n", value, index);
    }
}

// Add values to the list by reading a user provided file.
static void add_from_file(IntegerLinkedList *list)
{
    clear_screen();

    // Initialize a buffer for the file name.
    char buffer[INPUT_BUFFER_LEN] = { 0 };

    // Read a file name from the user.
    read_string_from_console(buffer, "Enter the file name: ");

    print_list_before(list);
    linked_list_load_data_from_file(list, buffer);
    print_list_after(list);
}

// Write the contents of the list to a file.
static void output_to_file(IntegerLinkedList *list)
{
    clear_screen();

    // Initialize a buffer for the file name.
    char buffer[INPUT_BUFFER_LEN] = { 0 };

    // Read a file name from the user.
    read_string_from_console(buffer, "Enter the file name: ");

    linked_list_output_to_file(list, buffer);
    printf("List contents written to '%s'\n", buffer);
    linked_list_print_list(list);
}

// Display the value at the beginning of the list.
static void read_front(IntegerLinkedList *list)
{
    clear_screen();
    linked_list_print_list(list);
    printf("Value at the beginning of the list: %d\n\n", linked_list_front(list));
}

// Display the value at the end of the list.
static void read_back(IntegerLinkedList *list)
{
    clear_screen();
    linked_list_print_list(list);
    printf("Value at the end of the list: %d\n\n", linked_list_back(list));
}

// Display the value at the specified index.
static void read_at_index(IntegerLinkedList *list)
{
    clear_screen();
    linked_list_print_list(list);

    // Read a valid index from the user.
    size_t index = read_valid_index_from_console(list, 
        "Enter the index for the value you with to view: ");

    // Since the value is confirmed valid above, simply display the value.
    printf("Value at index %zu: %d\n\n", index, linked_list_element_at(list, index));
}

// Empties the contents of the list.
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

    // Display the available options to the user.
    print_menu();

    // Define the prompt for the user to select what they want to do.
    char const *prompt = "Please make a numeric selection: ";

    // Loop until the user is satisfied that the implementation meets requirements.
    while (true)
    {
        // Perform the appropriate action based on user input.
        switch (read_number_from_console(prompt))
        {
            case 0:  // Exit the application.
                return;

            case 1:  // Add a number to the beginning of the list.
                push_front(list);
                break;

            case 2:  // Remove a number from the beginning of the list.
                if (is_empty(list)) { continue; }

                pop_front(list);
                break;

            case 3:  // Add a number to the end of the list.
                push_back(list);
                break;

            case 4:  // Remove a number from the end of the list.
                if (is_empty(list)) { continue; }

                pop_back(list);
                break;

            case 5:  // Remove the number at a specific index from the list.
                if (is_empty(list)) { continue; }

                remove_at_index(list);
                break;

            case 6:  // Remove a specific number from the list.
                if (is_empty(list)) { continue; }

                remove_number(list);
                break;

            case 7:  // Print the list.
                print_list(list);
                break;

            case 8:  // Search the list for a specific number.
                search_list(list);
                break;

            case 9:  // Add numbers from a text file.
                add_from_file(list);
                break;

            case 10:  // Output the list to a text file.
                output_to_file(list);
                break;

            case 11:  // Read the number at the front of the list.
                if (is_empty(list)) { continue; }

                read_front(list);
                break;

            case 12:  // Read the number at the end of the list.
                if (is_empty(list)) { continue; }

                read_back(list);
                break;

            case 13:  // Read the element at a specific index in the list.
                if (is_empty(list)) { continue; }

                read_at_index(list);
                break;

            case 14:  // Clear the contents of the list.
                clear_list(list);
                break;

            default:  // If the user enters an invalid selection, prompt and loop again.
                printf("** Invalid Selection Received, please try again. **\n");
                continue;
        }
        
        // Display the available options once again before looping.
        print_menu();
    }
}

