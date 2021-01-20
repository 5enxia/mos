#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<sys/types.h>

#include<readline/readline.h>
#include<readline/history.h>

void init();
void clear();

int main(int argc, const char *argv[])
{
    init();
    return 0;
}

void init() {
    clear();
    printf("my own shell\n");
    char* user = getenv("USER");
    printf("%s\n", user);
    sleep(1);
}

void clear() {
    printf("\033[H\033[J");
}
