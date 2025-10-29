#!/usr/bin/bash



SRC=./preprocessors
MYLIB=$SRC/lib

if [[ ! -d "$SRC" || ! -d "$MYLIB" ]]; then
  echo "Wrong paths" && exit 1
fi

#gcc -c "$MYLIB/mylib.c" -o ./mylib.o && \
#gcc -I"$MYLIB" -c "$SRC/main.c" -DBUFSIZE=10 -o ./main.o && \
#gcc ./main.o ./mylib.o -o main

gcc -I"$MYLIB" "$SRC/main.c" "$MYLIB/mylib.c" -DBUFSIZE=10
exit $?