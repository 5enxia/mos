#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>

#include<sys/types.h>

#include<readline/readline.h>
#include<readline/history.h>

void init();
void clear();
void printLine();
void input();

int main(int argc, const char *argv[])
{
    init();
    while (1) {
        printLine();
        input();
    }
    printLine();
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
void input() {
    char *buf;
    buf = readline("$>");
}