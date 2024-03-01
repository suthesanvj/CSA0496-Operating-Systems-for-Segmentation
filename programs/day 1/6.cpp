#include <stdio.h>
#include <limits.h>

// Structure to represent a process
typedef struct {
    int processId;
    int arrivalTime;
    int burstTime;
    int priority;
} Process;

// Function to perform pre-emptive Priority Scheduling
void priorityScheduling(Process processes[], int n, int waitingTime[], int turnaroundTime[]) {
    int remainingTime[n];
    int currentTime = 0;
    int completedProcesses = 0;

    // Initialize remaining time for all processes
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
    }

    while (completedProcesses < n) {
        int highestPriorityJob = -1;
        int highestPriority = INT_MIN;

        // Find the process with the highest priority that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && remainingTime[i] > 0 && processes[i].priority > highestPriority) {
                highestPriorityJob = i;
                highestPriority = processes[i].priority;
            }
        }

        // If no process is found, increment the current time
        if (highestPriorityJob == -1) {
            currentTime++;
        } else {
            // Process the highest priority job for 1 time unit
            remainingTime[highestPriorityJob]--;
            currentTime++;

            // If the process is completed
            if (remainingTime[highestPriorityJob] == 0) {
                completedProcesses++;

                // Calculate waiting time and turnaround time
                waitingTime[highestPriorityJob] = currentTime - processes[highestPriorityJob].arrivalTime - processes[highestPriorityJob].burstTime;
                turnaroundTime[highestPriorityJob] = waitingTime[highestPriorityJob] + processes[highestPriorityJob].burstTime;
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
    printf("Process\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].priority, waitingTime[i], turnaroundTime[i]);
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

    // Input the arrival time, burst time, and priority for each process
    for (int i = 0; i < n; i++) {
        processes[i].processId = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        printf("Enter priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    // Perform pre-emptive Priority Scheduling
    priorityScheduling(processes, n, waitingTime, turnaroundTime);

    // Calculate average waiting time and average turnaround time
    float averageWaitingTime, averageTurnaroundTime;
    calculateAverages(waitingTime, turnaroundTime, n, &averageWaitingTime, &averageTurnaroundTime);

    // Display the schedule and results
    displaySchedule(processes, n, waitingTime, turnaroundTime, averageWaitingTime, averageTurnaroundTime);

    return 0;
}

