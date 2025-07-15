#include <windows.h>
#include <stdio.h>

int main() {
    char buffer[100];
    DWORD read;

    ReadFile(GetStdHandle(STD_INPUT_HANDLE), buffer, sizeof(buffer), &read, NULL);
    buffer[read] = '\0'; // Null-terminate
    printf("[Inter-Process] Child received: %s\n", buffer);
    return 0;
}
