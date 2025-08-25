cmake_minimum_required(VERSION 4.0)

add_executable(linked_list)

target_compile_options(linked_list PRIVATE)

target_include_directories(linked_list PRIVATE
    LinkedList
    LinkedList/Demo
)

target_sources(linked_list PRIVATE
    main.c
    LinkedList/linked_list.c
    LinkedList/Demo/linked_list_demo.c
)

