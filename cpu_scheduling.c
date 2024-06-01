#include <stdio.h>
#include <string.h>
#include <limits.h>

// Define a struct for a process
typedef struct
{
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
} Process;

// Function to implement First Come First Serve (FCFS) scheduling algorithm
void FCFS(Process processes[], int n)
{
    // Initialize current time and total waiting time
    int currentTime = 0;
    int totalWaitingTime = 0;

    // Loop through all processes
    for (int i = 0; i < n; i++)
    {
        // If current time is less than arrival time of current process,
        // update current time to arrival time of current process
        if (currentTime < processes[i].arrivalTime)
        {
            currentTime = processes[i].arrivalTime;
        }

        // Calculate waiting time for current process
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;

        // Update current time by adding burst time of current process
        currentTime += processes[i].burstTime;

        // Add waiting time of current process to total waiting time
        totalWaitingTime += processes[i].waitingTime;
    }

    // Calculate average waiting time
    double averageWaitingTime = (double)totalWaitingTime / n;

    // Print average waiting time for FCFS scheduling
    printf("FCFS Average Waiting Time: %f\n", averageWaitingTime);
}

// Function to implement Shortest Job First (SJF) scheduling algorithm
void SJF(Process processes[], int n)
{
    // Initialize current time, total waiting time, completed count, and array to track completion status of processes
    int currentTime = 0;
    int totalWaitingTime = 0;
    int completed = 0;
    int isCompleted[n];

    // Initialize array to track completion status of processes
    memset(isCompleted, 0, sizeof(isCompleted));

    // Loop until all processes are completed
    while (completed != n)
    {
        // Initialize index of shortest job and minimum burst time
        int idx = -1;
        int minBurstTime = INT_MAX;

        // Loop through all processes
        for (int i = 0; i < n; i++)
        {
            // Check if process has arrived and not completed yet
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i])
            {
                // Update index of shortest job if current process has shorter burst time
                if (processes[i].burstTime < minBurstTime)
                {
                    minBurstTime = processes[i].burstTime;
                    idx = i;
                }
            }
        }

        // If a process is found
        if (idx != -1)
        {
            // Update current time, waiting time, completion status, and completed count for the selected process
            currentTime += processes[idx].burstTime;
            processes[idx].waitingTime = currentTime - processes[idx].arrivalTime - processes[idx].burstTime;
            totalWaitingTime += processes[idx].waitingTime;
            isCompleted[idx] = 1;
            completed++;
        }
        else
        {
            // If no process is found, increment current time
            currentTime++;
        }
    }

    // Calculate average waiting time
    double averageWaitingTime = (double)totalWaitingTime / n;

    // Print average waiting time for SJF scheduling
    printf("SJF Average Waiting Time: %f\n", averageWaitingTime);
}

// Function to implement Round Robin (RR) scheduling algorithm
void RR(Process processes[], int n, int quantum)
{
    // Initialize current time, total waiting time, and arrays to track remaining burst time and waiting time of processes
    int currentTime = 0;
    int totalWaitingTime = 0;
    int remainingBurstTime[n];
    int waitingTime[n];

    // Initialize arrays to track remaining burst time and waiting time of processes
    for (int i = 0; i < n; i++)
    {
        remainingBurstTime[i] = processes[i].burstTime;
        waitingTime[i] = 0;
    }

    // Loop until all processes are completed
    while (1)
    {
        // Flag to check if all processes are completed
        int done = 1;

        // Loop through all processes
        for (int i = 0; i < n; i++)
        {
            // Check if process has remaining burst time
            if (remainingBurstTime[i] > 0)
            {
                // Set done flag to 0 as there are still processes remaining
                done = 0;

                // If remaining burst time is greater than quantum, execute for quantum time
                if (remainingBurstTime[i] > quantum)
                {
                    currentTime += quantum;
                    remainingBurstTime[i] -= quantum;
                }
                else
                {
                    // If remaining burst time is less than or equal to quantum, execute for remaining burst time
                    currentTime += remainingBurstTime[i];
                    waitingTime[i] = currentTime - processes[i].arrivalTime - processes[i].burstTime;
                    totalWaitingTime += waitingTime[i];
                    remainingBurstTime[i] = 0;
                }
            }
        }

        // If all processes are completed, break the loop
        if (done == 1)
        {
            break;
        }
    }

    // Calculate average waiting time
    double averageWaitingTime = (double)totalWaitingTime / n;

    // Print average waiting time for RR scheduling
    printf("RR Average Waiting Time: %f\n", averageWaitingTime);
}

// Main function
int main()
{
    // Array of processes
    Process processes[] = {
        {0, 0, 10},
        {1, 6, 8},
        {2, 7, 4},
        {3, 9, 5}};
    int n = sizeof(processes) / sizeof(processes[0]); // Number of processes
    int quantum = 2; // Quantum for Round Robin scheduling

    // Print FCFS scheduling
    printf("FCFS Scheduling:\n");
    FCFS(processes, n);

    // Print SJF scheduling
    printf("\nSJF Scheduling:\n");
    SJF(processes, n);

    // Print RR scheduling with given quantum
    printf("\nRR Scheduling (Quantum = %d):\n", quantum);
    RR(processes, n, quantum);

    return 0;
}
