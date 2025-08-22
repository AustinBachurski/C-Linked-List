cmake_minimum_required(VERSION 4.0)

add_executable(linked_list)

target_compile_options(linked_list PRIVATE -O0 -g3)

target_include_directories(linked_list PRIVATE LinkedList)

target_sources(linked_list PRIVATE
    main.c
    LinkedList/linked_list.c
)

