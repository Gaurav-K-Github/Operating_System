#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// Entry point
int main(int argc, char *argv[]) {
    if (argc == 3) {
        // This branch runs only if exec() was called with two numbers
        int a = atoi(argv[1]);
        int b = atoi(argv[2]);
        printf("Child Process (PID: %d): Multiplication = %d * %d = %d\n", getpid(), a, b, a * b);
        return 0;
    }

    // Regular execution path (no arguments): parent forks child
    int num1, num2;
    pid_t pid;

    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process: run same program with args using exec
        char num1_str[10], num2_str[10];
        sprintf(num1_str, "%d", num1);
        sprintf(num2_str, "%d", num2);

        execl("./a.out", "./a.out", num1_str, num2_str, NULL);
        // If exec fails:
        perror("Exec failed");
        exit(1);
    }
    else {
        // Parent process: do addition
        printf("Parent Process (PID: %d): Addition = %d + %d = %d\n", getpid(), num1, num2, num1 + num2);
    }

    return 0;
}
