#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) created.\n", getpid());

        // Demonstrating execve
        char *args[] = {"/bin/ls", NULL};  // Command to list directory contents
        execve(args[0], args, NULL);

        // This part will not be reached if execve is successful
        perror("execve failed");
        exit(1);
    } else {
        // Parent process
        printf("Parent process (PID: %d) waiting for child to finish.\n", getpid());

        // Demonstrate wait
        int status;
        wait(&status);  // Wait for the child process to terminate
        printf("Child process completed.\n");

        // Create a zombie process for demonstration
        pid_t zombie_pid = fork();
        if (zombie_pid == 0) {
            printf("Zombie child process (PID: %d) created.\n", getpid());
            exit(0);  // Exit immediately to create a zombie state
        }
        sleep(5);  // Keep the parent running to allow observing the zombie state

        // Orphan process demonstration
        pid_t orphan_pid = fork();
        if (orphan_pid == 0) {
            printf("Orphan child process (PID: %d) created.\n", getpid());
            sleep(5);  // Child continues after the parent has exited
            printf("Orphan child process (PID: %d) completed.\n", getpid());
            exit(0);
        }
        printf("Parent process exiting, creating orphan process.\n");
    }
    return 0;
}