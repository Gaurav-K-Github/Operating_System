#include <windows.h>
#include <stdio.h>
#include <string.h>

// ---------------- Intra-Process Communication ----------------
char sharedMemory[100];

DWORD WINAPI ThreadFunc(LPVOID lpParam) {
    printf("[Intra-Thread] Reading from shared memory: %s\n", sharedMemory);
    return 0;
}

// ---------------- Inter-Process Communication ----------------
void InterProcessCommunication() {
    HANDLE hReadPipe, hWritePipe;
    SECURITY_ATTRIBUTES saAttr;
    PROCESS_INFORMATION piProcInfo;
    STARTUPINFOA siStartInfo;
    BOOL bSuccess;
    CHAR message[] = "Hello from Parent to Child via Pipe\n";
    DWORD written;

    // Set the bInheritHandle flag so pipe handles are inherited
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    // Create a pipe for the child process
    if (!CreatePipe(&hReadPipe, &hWritePipe, &saAttr, 0)) {
        printf("Pipe creation failed.\n");
        return;
    }

    // Ensure the write handle is not inherited
    SetHandleInformation(hWritePipe, HANDLE_FLAG_INHERIT, 0);

    // Set up members of the STARTUPINFO structure
    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFOA));
    siStartInfo.cb = sizeof(STARTUPINFOA);
    siStartInfo.hStdInput = hReadPipe;
    siStartInfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    siStartInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    // Dynamically get the path to the current executable
    CHAR exePath[MAX_PATH] = {0};
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    CHAR cmdLine[MAX_PATH + 10];
    sprintf(cmdLine, "\"%s\" child", exePath);

    // Create the child process
    bSuccess = CreateProcessA(
        NULL,
        cmdLine,
        NULL,
        NULL,
        TRUE,        // Inherit handles
        0,
        NULL,
        NULL,
        &siStartInfo,
        &piProcInfo);

    if (!bSuccess) {
        printf("Failed to create child process. Error: %lu\n", GetLastError());
        return;
    } else {
        // Parent writes to pipe
        WriteFile(hWritePipe, message, strlen(message), &written, NULL);
        CloseHandle(hWritePipe);
        WaitForSingleObject(piProcInfo.hProcess, INFINITE);
        CloseHandle(piProcInfo.hProcess);
        CloseHandle(piProcInfo.hThread);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "child") == 0) {
        char buffer[100];
        DWORD bytesRead;
        ReadFile(GetStdHandle(STD_INPUT_HANDLE), buffer, sizeof(buffer) - 1, &bytesRead, NULL);
        buffer[bytesRead] = '\0';  
        printf("[Inter-Process] Child received: %s", buffer);
        return 0;
    }

    printf("=== Intra-Process Communication Using Threads ===\n");
    strcpy(sharedMemory, "Hello from Main Thread");
    HANDLE hThread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    printf("\n=== Inter-Process Communication Using Anonymous Pipe ===\n");
    InterProcessCommunication();

    return 0;
}
