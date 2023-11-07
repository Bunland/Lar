#!/bin/bash

# Script to compile main.c and functions.c
# gcc -o programa -I~/Desktop/Lar/src/includes ~/Desktop/Lar/main.c ~/Desktop/Lar/src/fn/functions.c
gcc -o lar -Iincludes main.c src/*/*.c -I/usr/include/webkitgtk-4.0 -ljavascriptcoregtk-4.0


./lar run ./index.js