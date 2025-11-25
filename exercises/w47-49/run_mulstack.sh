#!/usr/bin/bash

CFLAGS=(
    -Wall
    -Wextra
    -g
    -O0
)
[[ ! -d "obj" ]] && mkdir obj
gcc "${CFLAGS[@]}" -c 45_mulstack_module.c -o obj/45_mulstack_module.o && \
gcc "${CFLAGS[@]}" -c 45_mulstack_test.c -o obj/45_mulstack_test.o && \
gcc obj/45_mulstack_module.o obj/45_mulstack_test.o -o test && \
./test