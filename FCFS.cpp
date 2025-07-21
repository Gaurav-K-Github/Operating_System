#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], ct[n], tat[n], wt[n];
    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> at[i] >> bt[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
            }
        }
    }

    int currentTime = 0;
    cout << "\nID\tAT\tBT\tCT\tTAT\tWT\n";
    
    for (int i = 0; i < n; i++) {
        if (currentTime < at[i]) currentTime = at[i];
        ct[i] = currentTime + bt[i]; // Completion time
        tat[i] = ct[i] - at[i];      // Turnaround time
        wt[i] = tat[i] - bt[i];      // Waiting time
        currentTime = ct[i];

        totalWT += wt[i];
        totalTAT += tat[i];

        cout << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" 
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    cout << "\nAvg Waiting Time: " << totalWT / n << "\n";
    cout << "Avg Turnaround Time: " << totalTAT / n << "\n";
    
    return 0;
}
