#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 3) {
        // Child process: perform multiplication
        int a = atoi(argv[1]);
        int b = atoi(argv[2]);
        printf("Child Process (PID: %lu): Multiplication = %d * %d = %d\n", GetCurrentProcessId(), a, b, a * b);
        return 0;
    }

    // Parent process: get input and create child
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    // Convert integers to strings
    char num1_str[10], num2_str[10];
    sprintf(num1_str, "%d", num1);
    sprintf(num2_str, "%d", num2);

    // Build command line for child process
    char commandLine[100];
    sprintf(commandLine, "%s %s %s", argv[0], num1_str, num2_str);

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create the child process
    if (!CreateProcess(
            NULL,           // Application name
            commandLine,    // Command line (including program name and args)
            NULL, NULL,     // Process and thread security
            FALSE,          // Inherit handles
            0,              // Creation flags
            NULL, NULL,     // Environment, current directory
            &si, &pi)) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    // Parent process: addition
    printf("Parent Process (PID: %lu): Addition = %d + %d = %d\n", GetCurrentProcessId(), num1, num2, num1 + num2);

    // Wait for child to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
