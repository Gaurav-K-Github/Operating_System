#include <stdio.h>

int findOptimal(int pages[], int memory[], int n, int index, int frames) {
    int pos = -1, farthest = index;
    for (int i = 0; i < frames; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (memory[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) return i; 
    }
    return (pos == -1) ? 0 : pos;
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 4;
    int memory[4] = {-1, -1, -1, -1};
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < frames; j++) {
            if (memory[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if (!hit) {
            int replace = -1;
            for (int j = 0; j < frames; j++) {
                if (memory[j] == -1) {
                    replace = j;
                    break;
                }
            }
            if (replace == -1)
                replace = findOptimal(pages, memory, n, i + 1, frames);
            memory[replace] = pages[i];
            page_faults++;
        }
    }

    printf("Total Page Faults (Optimal): %d\n", page_faults);
    return 0;
}
