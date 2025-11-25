#!/usr/bin/bash

CFLAGS=(
    "-Wall"
    "-Wextra"
    "-g"
    "-O0"
)
[[ ! -d "obj" ]] && mkdir obj
gcc "${CFLAGS[@]}" -c 42_gcd_module.c -o obj/42_gcd_module.o && \
gcc "${CFLAGS[@]}" -c 42_gcd_test.c -o obj/42_gcd_test.o && \
gcc obj/42_gcd_module.o obj/42_gcd_test.o -o test && \
./test