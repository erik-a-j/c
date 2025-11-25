#!/usr/bin/bash

CFLAGS=(
    -Wall
    -Wextra
    -g
    -O0
)
[[ ! -d "obj" ]] && mkdir obj
gcc "${CFLAGS[@]}" -c 44_stack_module.c -o obj/44_stack_module.o && \
gcc "${CFLAGS[@]}" -c 44_stack_test.c -o obj/44_stack_test.o && \
gcc obj/44_stack_module.o obj/44_stack_test.o -o test && \
./test