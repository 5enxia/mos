#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>

#include"package/parser.h"
#include"package/exec.h"

const int MAXLENGTH = 1024;
const char* INITIAL_MESSAGE = "mosh: my own shell\n";

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
    while (1) {
        printLine();
        readLine(input);
        // printf("%s\n", input);
        isPiped = parseLine(input, parsed);
        // printf("%d\n", isPiped);
        if (isPiped) {
            execLine(parsed[0]);
        } else {
            execLine(parsed[0]);
        }
    }
    return 0;
}

// init screen
// change dir home
void init() {
    clear();
    printf("%s", INITIAL_MESSAGE);
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
    printf("%s>%s>%s>$>", user, hostname, cwd);
}

// user input
void readLine(char *input) {
    fgets(input, sizeof(input), stdin);
    char *ln = strchr(input, '\n');
    if (ln) *ln = '\0';
}