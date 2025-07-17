#include <stdio.h>

#define MAX 25

int main() {
    int frag[MAX], b[MAX], f[MAX];
    int bf[MAX] = {0}, ff[MAX] = {0};  // bf = block allocated flag, ff = file assigned block
    int i, j, nb, nf, temp, lowest;

    printf("Enter the number of blocks: ");
    scanf("%d", &nb);

    printf("Enter the number of files: ");
    scanf("%d", &nf);

    printf("Enter the size of the blocks:\n");
    for (i = 1; i <= nb; i++) {
        printf("Block %d: ", i);
        scanf("%d", &b[i]);
    }

    printf("Enter the size of the files:\n");
    for (i = 1; i <= nf; i++) {
        printf("File %d: ", i);
        scanf("%d", &f[i]);
    }

    for (i = 1; i <= nf; i++) {
        lowest = 100000;  // reset lowest for each file
        for (j = 1; j <= nb; j++) {
            if (bf[j] == 0) {  // block not allocated
                temp = b[j] - f[i];
                if (temp >= 0 && temp < lowest) {
                    ff[i] = j;
                    lowest = temp;
                }
            }
        }
        frag[i] = lowest;
        if (lowest != 100000)
            bf[ff[i]] = 1;  // mark block as allocated
        else
            ff[i] = 0;  // no block assigned
    }

    printf("\nFile No\tFile Size\tBlock No\tBlock Size\tFragment\n");
    for (i = 1; i <= nf; i++) {
        if (ff[i] != 0)
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i, f[i], ff[i], b[ff[i]], frag[i]);
        else
            printf("%d\t\t%d\t\tNot Allocated\n", i, f[i]);
    }

    return 0;
}
