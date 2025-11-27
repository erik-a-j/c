#!/usr/bin/bash

CFLAGS=(
    -Wall
    -Wextra
    -Wno-unused
    -g
    -O0
)
[[ ! -d "obj" ]] && mkdir obj
gcc "${CFLAGS[@]}" -c 46_mullist_module.c -o obj/46_mullist_module.o && \
gcc "${CFLAGS[@]}" -c 46_mullist_test.c -o obj/46_mullist_test.o && \
gcc obj/46_mullist_module.o obj/46_mullist_test.o -o test && \
./test