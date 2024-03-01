#include <stdio.h>

// Structure to represent a process
typedef struct {
    int processId;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
} Process;

// Function to perform FCFS scheduling
void fcfsScheduling(Process processes[], int n) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        // Execute the process
        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        // Update current time
        currentTime = processes[i].completionTime;
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

    // Input the burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].processId = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    // Perform FCFS Scheduling
    fcfsScheduling(processes, n);

    // Calculate average waiting time and average turnaround time
    float averageWaitingTime, averageTurnaroundTime;
    calculateAverages(processes, n, &averageWaitingTime, &averageTurnaroundTime);

    // Display the schedule and results
    displaySchedule(processes, n, averageWaitingTime, averageTurnaroundTime);

    return 0;
}

