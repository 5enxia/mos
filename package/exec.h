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

void execPipeline(char ***parsed) {
    int fd[2]; // 0:read, 1:write
    pid_t pid[2];

    if (pipe(fd) < 0) {
        printf("Could not initialized pipe\n");
        return;
    }

    pid[0] = fork();
    if (pid[0] < 0) { // error
        printf("Child:0->Could not fork\n");
        return;
    }

    if (pid[0] == 0) { // child 0
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO); // REPLECATE stdout
        close(fd[1]);
        if (execvp(parsed[0][0], parsed[0]) < 0) {
            printf("Child:0->Could not exec the command\n");
            exit(0);
        }
    } else { // paren
        pid[1] = fork();
        if (pid[1] < 0) { // error
            printf("Child:1->Could not fork\n");
            return;
        }
        if (pid[1] == 0) { // child 1
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO); // REPLECATE stdout
            close(fd[0]);
            if (execvp(parsed[1][0], parsed[1]) < 0) {
                printf("Child:1->Could not exec the command\n");
                exit(0);
            }
        } else {
            wait(NULL);
            wait(NULL);
        }
    }
}
