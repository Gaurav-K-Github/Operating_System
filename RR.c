#include <stdio.h>

int main() {
    int n, bt[10], rt[10], wt[10], tat[10];
    int time = 0, tq, remain, flag = 0;
    float totalWT = 0, totalTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    remain = n;

    for (int i = 0; i < n; i++) {
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // remaining time initially = burst time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    while (remain != 0) {
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0) {
                if (rt[i] <= tq) {
                    // Process can finish in this quantum
                    time += rt[i];
                    rt[i] = 0;
                    flag = 1;
                } else {
                    // Process needs more time
                    time += tq;
                    rt[i] -= tq;
                }

                if (rt[i] == 0 && flag == 1) {
                    remain--;
                    tat[i] = time;
                    wt[i] = tat[i] - bt[i];
                    totalWT += wt[i];
                    totalTAT += tat[i];
                    flag = 0;
                }
            }
        }
    }

    // Output results
    printf("\nP\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
