build: main.c package/parser.h
	gcc main.c -o mosh -l readline
