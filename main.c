#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>

#include<readline/readline.h>

#include"package/parser.h"

const int MAXLENGTH = 1024;

void init();
void clear();
void printLine();
void readLine(char *input);

int main()
{
    char input[MAXLENGTH];
    char** parsed[2];
    for (int i = 0; i < 2; i++) {
        parsed[i] = malloc(MAXARGS * sizeof(char*));
    }
    int isPiped = 0;
    init();
    while (true) {
        printLine();
        readLine(input);
        // printf("%s\n", input);
        isPiped = parseLine(input, parsed);
        printf("%d\n", isPiped);
    }
    return 0;
}

// init screen
// change dir home
void init() {
    clear();
    printf("mos: my own shell\n");
    char* home = getenv("HOME");
    chdir(home);
}

// init screen
void clear() {
    printf("\033[H\033[J");
}

// print username. hostname, cwd
void printLine() {
    char* user = getenv("USER");
    char* hostname = getenv("HOSTNAME");
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s>%s>%s>", user, hostname, cwd);
}

// user input
void readLine(char *input) {
    char *buf = readline("$>");
    strcpy(input, buf);
}