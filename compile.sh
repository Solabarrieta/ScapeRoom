#!/bin/bash
gcc -std=c99 -o bin/cat commands/cat_cmd/cat.c
gcc -std=c99 -o bin/cp commands/cp_cmd/cp.c
gcc -std=c99 -o bin/ls commands/ls_cmd/ls.c
gcc -std=c99 -o bin/man commands/man_cmd/man.c
gcc -std=c99 -o bin/mv commands/mv_cmd/mv.c
gcc -std=c99 -o bin/touch commands/touch_cmd/touch.c
gcc -std=c99 -o shell shell.c
