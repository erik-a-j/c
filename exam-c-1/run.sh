#!/usr/bin/bash
CFLAGS=(
    "-g" "-O0" "-Wall" "-Wextra" "-Wpedantic"
)

gcc -std=c11 "${CFLAGS[@]}" main.c && ./a.out