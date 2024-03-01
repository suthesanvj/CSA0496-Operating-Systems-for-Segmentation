#include <stdio.h>

// Structure to represent a process
typedef struct {
    int processId;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int executed;
} Process;

// Function to perform Non-Preemptive Shortest Job First (SJF) scheduling
void sjfScheduling(Process processes[], int n) {
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int shortestJob = -1;
        int shortestTime = __INT_MAX__;

        // Find the shortest job that has arrived and not yet executed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !processes[i].executed && processes[i].burstTime < shortestTime) {
                shortestJob = i;
                shortestTime = processes[i].burstTime;
            }
        }

        // If no job is found, move to the next time unit
        if (shortestJob == -1) {
            currentTime++;
        } else {
            // Execute the shortest job
            processes[shortestJob].completionTime = currentTime + processes[shortestJob].burstTime;
            processes[shortestJob].turnaroundTime = processes[shortestJob].completionTime - processes[shortestJob].arrivalTime;
            processes[shortestJob].waitingTime = processes[shortestJob].turnaroundTime - processes[shortestJob].burstTime;
            processes[shortestJob].executed = 1;
            currentTime += processes[shortestJob].burstTime;
            completedProcesses++;
        }
    }
}

// Function to calculate average waiting time and average turnaround time
void calculateAverages(Process processes[], int n, float *averageWaitingTime, float *averageTurnaroundTime) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    *averageWaitingTime = (float)totalWaitingTime / n;
    *averageTurnaroundTime = (float)totalTurnaroundTime / n;
}

// Function to display the schedule and results
void displaySchedule(Process processes[], int n, float averageWaitingTime, float averageTurnaroundTime) {
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].completionTime, processes[i].turnaroundTime, processes[i].waitingTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", averageWaitingTime);
    printf("Average Turnaround Time: %.2f\n", averageTurnaroundTime);
}

int main() {
    // Number of processes
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Array to store processes
    Process processes[n];

    // Input the arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].processId = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].executed = 0;
    }

    // Perform Non-Preemptive SJF Scheduling
    sjfScheduling(processes, n);

    // Calculate average waiting time and average turnaround time
    float averageWaitingTime, averageTurnaroundTime;
    calculateAverages(processes, n, &averageWaitingTime, &averageTurnaroundTime);

    // Display the schedule and results
    displaySchedule(processes, n, averageWaitingTime, averageTurnaroundTime);

    return 0;
}

