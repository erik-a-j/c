#!/usr/bin/bash
CFLAGS=(
    #-g
    #-O0
    -Wall
    #-Wextra
    #-Wpedantic
)

gcc -std=c11 "${CFLAGS[@]}" exam.c && ./a.out