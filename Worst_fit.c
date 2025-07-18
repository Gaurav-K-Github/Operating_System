#include <stdio.h>

#define MAX 25

int main() {
    int frag[MAX], block[MAX], file[MAX];
    int blockFlag[MAX] = {0}, fileBlock[MAX] = {0};
    int i, j, nb, nf;

    printf("\n\tMemory Management Scheme - Worst Fit");

    // Input
    printf("\nEnter the number of blocks: ");
    scanf("%d", &nb);
    printf("Enter the number of files: ");
    scanf("%d", &nf);

    printf("\nEnter the size of the blocks:\n");
    for (i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &block[i]);
    }

    printf("Enter the size of the files:\n");
    for (i = 0; i < nf; i++) {
        printf("File %d: ", i + 1);
        scanf("%d", &file[i]);
    }

    // Worst Fit Allocation
    for (i = 0; i < nf; i++) {
        int highest = -1;
        for (j = 0; j < nb; j++) {
            if (!blockFlag[j]) {
                int temp = block[j] - file[i];
                if (temp >= 0 && (highest == -1 || temp > block[highest] - file[i])) {
                    highest = j;
                }
            }
        }

        if (highest != -1) {
            fileBlock[i] = highest;
            blockFlag[highest] = 1;
            frag[i] = block[highest] - file[i];
        } else {
            fileBlock[i] = -1; // No suitable block found
            frag[i] = -1;
        }
    }

    // Output
    printf("\nFile_No\tFile_Size\tBlock_No\tBlock_Size\tFragment");
    for (i = 0; i < nf; i++) {
        if (fileBlock[i] != -1)
            printf("\n%d\t%d\t\t%d\t\t%d\t\t%d", i + 1, file[i], fileBlock[i] + 1, block[fileBlock[i]], frag[i]);
        else
            printf("\n%d\t%d\t\tNot Allocated", i + 1, file[i]);
    }

    return 0;
}
