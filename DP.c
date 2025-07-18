#include <stdio.h>
#include <windows.h>

#define N 5 // Number of philosophers

HANDLE forks[N];         // Forks as semaphores
HANDLE roomSemaphore;    // Controls max philosophers trying to eat

DWORD WINAPI philosopher(LPVOID idPtr) {
    int id = *(int*)idPtr;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        Sleep(1000); // Thinking

        WaitForSingleObject(roomSemaphore, INFINITE);     // Enter room
        WaitForSingleObject(forks[left], INFINITE);       // Pick up left fork
        WaitForSingleObject(forks[right], INFINITE);      // Pick up right fork

        printf("Philosopher %d is eating...\n", id);
        Sleep(2000); // Eating

        ReleaseSemaphore(forks[left], 1, NULL);           // Put down left fork
        ReleaseSemaphore(forks[right], 1, NULL);          // Put down right fork
        ReleaseSemaphore(roomSemaphore, 1, NULL);         // Leave room

        printf("Philosopher %d finished eating.\n", id);
    }

    return 0;
}

int main() {
    HANDLE threads[N];
    int ids[N];

    // Initialize roomSemaphore (max N - 1 philosophers can eat at once)
    roomSemaphore = CreateSemaphore(NULL, N - 1, N - 1, NULL);

    // Initialize fork semaphores
    for (int i = 0; i < N; i++) {
        forks[i] = CreateSemaphore(NULL, 1, 1, NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        threads[i] = CreateThread(NULL, 0, philosopher, &ids[i], 0, NULL);
    }

    // Wait for threads (never ends in this case)
    WaitForMultipleObjects(N, threads, TRUE, INFINITE);

    // Cleanup (unreachable in this infinite simulation)
    for (int i = 0; i < N; i++) {
        CloseHandle(forks[i]);
        CloseHandle(threads[i]);
    }
    CloseHandle(roomSemaphore);

    return 0;
}
