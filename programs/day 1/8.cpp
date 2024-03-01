#include <stdio.h>

// Structure to represent a process
typedef struct {
    int processId;
    int burstTime;
    int remainingTime;
} Process;

// Function to perform Round Robin scheduling
void roundRobinScheduling(Process processes[], int n, int timeQuantum) {
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                // Execute the process for the time quantum or until it finishes
                int executionTime = (processes[i].remainingTime > timeQuantum) ? timeQuantum : processes[i].remainingTime;

                currentTime += executionTime;
                processes[i].remainingTime -= executionTime;

                printf("Process %d executed for %d units.\n", processes[i].processId, executionTime);

                if (processes[i].remainingTime == 0) {
                    completedProcesses++;
                }
            }
        }
    }
}

int main() {
    // Number of processes
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Time quantum
    int timeQuantum;
    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    // Array to store processes
    Process processes[n];

    // Input the burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].processId = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Perform Round Robin Scheduling
    roundRobinScheduling(processes, n, timeQuantum);

    return 0;
}

