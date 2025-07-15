#include <stdio.h>

int main() {
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 4;
    int memory[4] = {-1, -1, -1, -1};
    int front = 0, page_faults = 0;

    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < frames; j++) {
            if (memory[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if (!hit) {
            memory[front] = pages[i];
            front = (front + 1) % frames;
            page_faults++;
        }
    }

    printf("Total Page Faults (FIFO): %d\n", page_faults);
    return 0;
}
