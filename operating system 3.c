#include <stdio.h>


struct Process {
    int processID;     
    int arrivalTime;    
    int burstTime;      
};


void calculateTimes(struct Process processes[], int n, int waitingTime[], int turnaroundTime[]) {
    
    waitingTime[0] = 0;

    
    turnaroundTime[0] = processes[0].burstTime;

    
    for (int i = 1; i < n; i++) {
        
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;

       
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
    }
}

void calculateAverages(int waitingTime[], int turnaroundTime[], int n, float *avgWaitingTime, float *avgTurnaroundTime) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

   
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    
    *avgWaitingTime = (float)totalWaitingTime / n;
    *avgTurnaroundTime = (float)totalTurnaroundTime / n;
}


void displayGanttChart(struct Process processes[], int n) {
    printf("\nGantt Chart:\n");

   
    for (int i = 0; i < n; i++) {
        printf("| P%d ", processes[i].processID);
    }
    printf("|\n");

   
    for (int i = 0; i < n; i++) {
        printf("%d     ", i == 0 ? 0 : (i - 1) + processes[i - 1].burstTime);
    }
    printf("%d\n", n - 1 + processes[n - 1].burstTime);
}

int main() {
  
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    
    struct Process processes[n];

   
    int waitingTime[n], turnaroundTime[n];


    float avgWaitingTime, avgTurnaroundTime;

   
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    calculateTimes(processes, n, waitingTime, turnaroundTime);
    calculateAverages(waitingTime, turnaroundTime, n, &avgWaitingTime, &avgTurnaroundTime);
    displayGanttChart(processes, n);
    printf("\nProcess\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", processes[i].processID, waitingTime[i], turnaroundTime[i]);
    }

   
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);

    return 0;
}

