#include <stdio.h>

int max[100][100], alloc[100][100], need[100][100], avail[100];
int n, r;

void input() {
    printf("Enter number of Processes: ");
    scanf("%d", &n);
    printf("Enter number of Resource Instances: ");
    scanf("%d", &r);

    printf("Enter Max Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Available Resources:\n");
    for (int j = 0; j < r; j++)
        scanf("%d", &avail[j]);
}

void show() {
    printf("\nProcess\tAllocation\tMax\t\tAvailable\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < r; j++) printf("%d ", alloc[i][j]);
        printf("\t");
        for (int j = 0; j < r; j++) printf("%d ", max[i][j]);
        if (i == 0) {
            printf("\t");
            for (int j = 0; j < r; j++) printf("%d ", avail[j]);
        }
        printf("\n");
    }
}

void calculate() {
    int finish[100] = {0}, safeSeq[100], count = 0;
    
    // Calculate need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < r; j++)
                    if (need[i][j] > avail[j]) break;

                if (j == r) {
                    for (int k = 0; k < r; k++)
                        avail[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) break;
    }

    if (count == n) {
        printf("\nSystem is in a Safe State.\nSafe Sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
    } else {
        printf("\nSystem is in an Unsafe State (Deadlock may occur).\n");
    }
}

int main() {
    printf("********** Banker's Algorithm **********\n");
    input();
    show();
    calculate();
    return 0;
}
