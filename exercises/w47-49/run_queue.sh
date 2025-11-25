#!/usr/bin/bash

CFLAGS=(
    -Wall
    -Wextra
    -g
    -O0
)
[[ ! -d "obj" ]] && mkdir obj
gcc "${CFLAGS[@]}" -c 43_queue_module.c -o obj/43_queue_module.o && \
gcc "${CFLAGS[@]}" -c 43_queue_test.c -o obj/43_queue_test.o && \
gcc obj/43_queue_module.o obj/43_queue_test.o -o test && \
./test