#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>

#include <readline/readline.h>

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
    init();
    while (1) {
        printLine();
        readLine(input);
        int isPiped = parseLine(input, parsed);
        if (isPiped) {
            execPipeline(parsed);
        } else {
            execLine(parsed[0]);
        }
    }
    return 0;
}

void init() {
    clear(); // init screen
    printf("%s", INITIAL_MESSAGE);
    char* home = getenv("HOME");
    chdir(home); // change dir home
}

void clear() {
    printf("\033[H\033[J"); // Refresh Control Code
}


void printLine() {
    char* user = getenv("USER"); // username
    char hostname[64];
    gethostname(hostname, sizeof(hostname));
    char cwd[1024];
    getcwd(cwd, sizeof(cwd)); // cwd
    // printf("%s>%s>%s>$>", user, hostname, cwd);
    printf("%s>%s>%s>", user, hostname, cwd);
}


void readLine(char *input) {
    char* buf;
    buf = readline("$>");
    strcpy(input, buf);
    // fgets(input, sizeof(input), stdin); // input
    // char *ln = strchr(input, '\n');
    // if (ln) *ln = '\0';
}