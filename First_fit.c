#include <stdio.h>

#define MAX 25

int main() {
    int frag[MAX], block[MAX], file[MAX];
    int bf[MAX] = {0}, ff[MAX] = {0}; // block filled and file to block mapping
    int i, j, nb, nf, temp;

    printf("Memory Management Scheme - First Fit\n");

    printf("Enter the number of blocks: ");
    scanf("%d", &nb);

    printf("Enter the number of files: ");
    scanf("%d", &nf);

    printf("\nEnter the size of each block:\n");
    for (i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &block[i]);
    }

    printf("\nEnter the size of each file:\n");
    for (i = 0; i < nf; i++) {
        printf("File %d: ", i + 1);
        scanf("%d", &file[i]);
    }

    // First Fit Allocation
    for (i = 0; i < nf; i++) {
        for (j = 0; j < nb; j++) {
            if (bf[j] == 0 && block[j] >= file[i]) {
                ff[i] = j;                  // File i is allocated to block j
                frag[i] = block[j] - file[i];
                bf[j] = 1;                  // Mark block as filled
                break;
            }
        }
    }

    printf("\nFile_no\tFile_size\tBlock_no\tBlock_size\tFragment\n");
    for (i = 0; i < nf; i++) {
        if (block[ff[i]] >= file[i]) {
            printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, file[i], ff[i] + 1, block[ff[i]], frag[i]);
        } else {
            printf("%d\t%d\t\tNot Allocated\n", i + 1, file[i]);
        }
    }

    return 0;
}
