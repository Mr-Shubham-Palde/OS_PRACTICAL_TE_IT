#include <stdio.h>

#define MAX_PROCESSES 10  // Define a constant for the maximum number of processes

int main() {
    int i, limit, total_time = 0, time_quantum;
    int wait_time = 0, turnaround_time = 0;
    int arrival_time[MAX_PROCESSES], burst_time[MAX_PROCESSES], temp_burst_time[MAX_PROCESSES];
    int remaining_processes = 0, counter = 0;
    int completion_time[MAX_PROCESSES], response_time[MAX_PROCESSES];
    float average_wait_time, average_turnaround_time, average_response_time;
    int first_execution_time[MAX_PROCESSES];  // To record first execution time

    // Input number of processes
    printf("Enter Total Number of Processes (max %d):\n\t", MAX_PROCESSES);
    scanf("%d", &limit);

    // Input arrival and burst times for each process
    for (i = 0; i < limit; i++) {
        printf("Enter Details of Process[%d]\n", i + 1);

        printf("Arrival Time:\t");
        scanf("%d", &arrival_time[i]);

        printf("Burst Time:\t");
        scanf("%d", &burst_time[i]);

        temp_burst_time[i] = burst_time[i];  // Copy burst times for processing
        first_execution_time[i] = -1;  // Initialize as -1 to check first execution
    }

    // Input time quantum
    printf("Enter Time Quantum:\n\t");
    scanf("%d", &time_quantum);

    printf("\nProcess ID\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n");

    // Main Round Robin scheduling loop
    for (i = 0, remaining_processes = limit; remaining_processes != 0;) {
        if (temp_burst_time[i] > 0) {
            if (first_execution_time[i] == -1) {
                // Set response time
                first_execution_time[i] = total_time - arrival_time[i];
            }
            if (temp_burst_time[i] <= time_quantum) {
                total_time += temp_burst_time[i];
                completion_time[i] = total_time;
                temp_burst_time[i] = 0;
                counter = 1;
            } else {
                temp_burst_time[i] -= time_quantum;
                total_time += time_quantum;
            }

            // Check if the process is complete
            if (temp_burst_time[i] == 0 && counter == 1) {
                remaining_processes--;

                // Calculate turnaround time and waiting time
                int turnaround = completion_time[i] - arrival_time[i];
                int wait = turnaround - burst_time[i];
                wait_time += wait;
                turnaround_time += turnaround;

                // Print process details
                printf("Process[%d]\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                       i + 1, burst_time[i], completion_time[i], turnaround, wait, first_execution_time[i]);

                counter = 0;
            }
        }

        // Move to the next process
        if (i == limit - 1) {
            i = 0;
        } else if (arrival_time[i + 1] <= total_time) {
            i++;
        } else {
            i = 0;
        }
    }

    // Calculate average waiting time, turnaround time, and response time
    average_wait_time = (float)wait_time / limit;
    average_turnaround_time = (float)turnaround_time / limit;
    average_response_time = 0;
    for (i = 0; i < limit; i++) {
        average_response_time += first_execution_time[i];
    }
    average_response_time /= limit;

    // Print average times
    printf("\nAverage Waiting Time:\t%f", average_wait_time);
    printf("\nAverage Turnaround Time:\t%f", average_turnaround_time);
    printf("\nAverage Response Time:\t%f", average_response_time);

    return 0;
}

