#!/usr/bin/bash

CFLAGS=(
    "-Wall"
    "-Wextra"
    "-g"
    "-O0"
)
[[ ! -d "obj" ]] && mkdir obj
gcc "${CFLAGS[@]}" -c 42_module.c -o obj/42_module.o && \
gcc "${CFLAGS[@]}" -c 42_test.c -o obj/42_test.o && \
gcc obj/42_module.o obj/42_test.o -o test && \
./test