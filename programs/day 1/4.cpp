#include <stdio.h>

// Structure to represent a process
typedef struct {
    int processId;
    int arrivalTime;
    int burstTime;
} Process;

// Function to perform SJF scheduling
void sjfScheduling(Process processes[], int n, int waitingTime[], int turnaroundTime[]) {
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int shortestJob = -1;
        int shortestTime = __INT_MAX__;

        // Find the process with the smallest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].burstTime < shortestTime && processes[i].burstTime > 0) {
                shortestJob = i;
                shortestTime = processes[i].burstTime;
            }
        }

        // If no process is found, increment the current time
        if (shortestJob == -1) {
            currentTime++;
        } else {
            // Execute the shortest job
            processes[shortestJob].burstTime--;
            currentTime++;

            // If the process is completed
            if (processes[shortestJob].burstTime == 0) {
                completedProcesses++;

                // Calculate waiting time and turnaround time
                waitingTime[shortestJob] = currentTime - processes[shortestJob].arrivalTime - processes[shortestJob].burstTime;
                turnaroundTime[shortestJob] = waitingTime[shortestJob] + processes[shortestJob].burstTime;
            }
        }
    }
}

// Function to calculate average waiting time and average turnaround time
void calculateAverages(int waitingTime[], int turnaroundTime[], int n, float *averageWaitingTime, float *averageTurnaroundTime) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    *averageWaitingTime = (float)totalWaitingTime / n;
    *averageTurnaroundTime = (float)totalTurnaroundTime / n;
}

// Function to display the schedule and results
void displaySchedule(Process processes[], int n, int waitingTime[], int turnaroundTime[], float averageWaitingTime, float averageTurnaroundTime) {
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].arrivalTime,
               processes[i].burstTime, waitingTime[i], turnaroundTime[i]);
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

    // Arrays to store waiting time and turnaround time for each process
    int waitingTime[n], turnaroundTime[n];

    // Input the arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].processId = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    // Perform SJF scheduling
    sjfScheduling(processes, n, waitingTime, turnaroundTime);

    // Calculate average waiting time and average turnaround time
    float averageWaitingTime, averageTurnaroundTime;
    calculateAverages(waitingTime, turnaroundTime, n, &averageWaitingTime, &averageTurnaroundTime);

    // Display the schedule and results
    displaySchedule(processes, n, waitingTime, turnaroundTime, averageWaitingTime, averageTurnaroundTime);

    return 0;
}

