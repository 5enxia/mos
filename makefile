build: main.c package/parser.h package/exec.h
	gcc main.c -o mosh -l readline
