#include <stdio.h>
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int pid[n], arrival[n], burst[n], waiting[n], turnaround[n];
    printf("Enter the process ids:\n");
    for (int i = 0; i < n; i++) {
    scanf("%d", &pid[i]);}
// Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &arrival[i], &burst[i]);
    }
// Sort processes based on arrival time and then burst time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i+1; j < n ; j++) {
           
             if (arrival[j] > arrival[j + 1]) {
                int temp = arrival[j];
                arrival[j] = arrival[j + 1];
                arrival[j + 1] = temp;
                
                temp = burst[j];
                burst[j] = burst[j + 1];
                burst[j + 1] = temp;

                temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp;
            }
        }
    }
    waiting[0] = 0;
    turnaround[0] = burst[0];
    // Calculate waiting and turnaround times
    for (int i = 1; i < n; i++) {
        waiting[i] = turnaround[i - 1] + arrival[i - 1] - arrival[i];
        if (waiting[i] < 0)
            waiting[i] = 0;
        turnaround[i] = waiting[i] + burst[i];
    }
    float totalWaiting = 0, totalTurnaround = 0;
    // Calculate total waiting and turnaround times
    for (int i = 0; i < n; i++) {
        totalWaiting += waiting[i];
        totalTurnaround += turnaround[i];
    }
    float avgWaiting = totalWaiting / n;
    float avgTurnaround = totalTurnaround / n;
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], arrival[i], burst[i], waiting[i], turnaround[i]);
    }
    printf("\nAverage Waiting Time: %.2f\n", avgWaiting);
    printf("Average Turnaround Time: %.2f\n", avgTurnaround);
    return 0;
}
