#include<string.h>
#include<unistd.h>

#include<sys/wait.h>

// exec input command & args
void execLine(char **parsed) {
    pid_t pid;
    int value = 0;
    if (!strcmp(parsed[0], "\n")) value = 0;
    else if (!strcmp(parsed[0], "exit")) value = 1;
    else if (!strcmp(parsed[0], "cd")) value = 2;
    switch (value) {
        case 0:
            break;
        case 1:
            exit(0);
            break;
        case 2:
            chdir(parsed[1]);
            break;
        default:
            pid = fork();
            if (pid == 0) { // child process
                if (execvp(parsed[0], parsed) < 0) {
                    printf("Could not exec the command\n");
                }
                exit(0);
            } else {
                wait(NULL); // wait child process end
            }
            break;
    }
}

void execPipedChild(char ***parsed, int *fd, int i) {
    if (i == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO); // REPLECATE stdout
        close(fd[1]);
    } else {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO); // REPLECATE stdout
        close(fd[0]);
    }
    if (execvp(parsed[i][0], parsed[i]) < 0) {
        printf("Child:%d->Could not exec the command\n", i);
        exit(0);
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
        execPipedChild(parsed, fd, 0);
    } else { // parent
        pid[1] = fork();
        if (pid[1] < 0) { // error
            printf("Child:1->Could not fork\n");
            return;
        }
        if (pid[1] == 0) { // child 1
            execPipedChild(parsed, fd, 1);
        } else {
            wait(NULL);
            wait(NULL);
        }
    }
}
