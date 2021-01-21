#include<unistd.h>

#include<sys/wait.h>

// exec input command & args
void execLine(char **parsed) {
    pid_t pid = fork();
    if (pid == 0) { // child process
        if (execvp(parsed[0], parsed) < 0) {
            printf("Could not exec the command\n");
        }
        exit(0);
    } else {
        wait(NULL); // wait child process end
    }
}
