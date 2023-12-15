#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void timeout_handler(int signum) {
    // kill the child process
    kill(getpid(), SIGTERM);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <timeout_seconds> <command> [args...]\n", argv[0]);
        return 1;
    }

    int timeout_seconds = atoi(argv[1]);
    if (timeout_seconds <= 0) {
        fprintf(stderr, "Timeout must be a positive integer.\n");
        return 1;
    }

    // register the timeout handler (SIGALRM)
    struct sigaction sa;
    sa.sa_handler = timeout_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);

    // set the alarm
    alarm(timeout_seconds);

    // fork a child process for executing command
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("fork");
        return 1;
    } else if (child_pid == 0) { // child process
        execvp(argv[2], &argv[2]);        // if execvp returns, an error occurred
        perror("execvp");
        exit(1);
    } else { // parent process
        int status;
        pid_t terminated_pid = waitpid(child_pid, &status, 0);

        alarm(0); // turn alarm off

        if (terminated_pid == -1) {
            perror("waitpid");
            return 1;
        }

        if (WIFEXITED(status)) { // normal exit process
            return WEXITSTATUS(status);
        } else if (WIFSIGNALED(status)) { // child process was terminated by a signal
            fprintf(stderr, "Child process terminated by signal: %d\n", WTERMSIG(status));
            return 1;
        }
    }

    return 0;
}