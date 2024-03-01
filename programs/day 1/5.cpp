#include <stdio.h>

// Structure to represent a process
typedef struct {
    int processId;
    int priority;
    int burstTime;
} Process;

// Function to perform Priority scheduling
void priorityScheduling(Process processes[], int n, int waitingTime[], int turnaroundTime[]) {
    int remainingTime[n];
    int completedProcesses = 0;
    int currentTime = 0;

    // Initialize remaining time for all processes
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
    }

    while (completedProcesses < n) {
        int highestPriorityJob = -1;
        int highestPriority = -1;

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].priority > highestPriority && processes[i].burstTime > 0 && processes[i].priority > 0) {
                highestPriorityJob = i;
                highestPriority = processes[i].priority;
            }
        }

        // If no process is found, increment the current time
        if (highestPriorityJob == -1) {
            currentTime++;
        } else {
            // Process the highest priority job
            remainingTime[highestPriorityJob]--;
            currentTime++;

            // If the process is completed
            if (remainingTime[highestPriorityJob] == 0) {
                completedProcesses++;

                // Calculate waiting time and turnaround time
                waitingTime[highestPriorityJob] = currentTime - processes[highestPriorityJob].burstTime;
                turnaroundTime[highestPriorityJob] = waitingTime[highestPriorityJob] + processes[highestPriorityJob].burstTime;

                // Mark the process as completed by setting its priority to a negative value
                processes[highestPriorityJob].priority = -1;
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
    printf("Process\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].priority,
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

    // Input the priority and burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].processId = i + 1;
        printf("Enter priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    // Perform Priority scheduling
    priorityScheduling(processes, n, waitingTime, turnaroundTime);

    // Calculate average waiting time and average turnaround time
    float averageWaitingTime, averageTurnaroundTime;
    calculateAverages(waitingTime, turnaroundTime, n, &averageWaitingTime, &averageTurnaroundTime);

    // Display the schedule and results
    displaySchedule(processes, n, waitingTime, turnaroundTime, averageWaitingTime, averageTurnaroundTime);

    return 0;
}

