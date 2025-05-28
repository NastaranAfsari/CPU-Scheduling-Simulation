#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 // حداکثر تعداد فرآیندها

struct Process {
    int pid;  
    int ArrivalT;   
    int BurstT;   
    int RemainingT;   
    int WaitingT;   
    int TurnarroundT;  
    int ResponseT_first; 
};

// چاپ معیارهای ارزیابی
void printMetrics(struct Process proc[], int n) {
    float avg_WaitingT = 0, avg_TurnarroundT = 0, avg_ResponseT = 0;
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\tResponse\n");
    for (int i = 0; i < n; i++) {
        avg_WaitingT += proc[i].WaitingT;
        avg_TurnarroundT += proc[i].TurnarroundT;
        avg_ResponseT += proc[i].ResponseT_first - proc[i].ArrivalT;
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", 
               proc[i].pid, proc[i].ArrivalT, proc[i].BurstT, 
               proc[i].WaitingT, proc[i].TurnarroundT, proc[i].ResponseT_first - proc[i].ArrivalT);
    }
    printf("Average Waiting Time: %.2f\n", avg_WaitingT / n);
    printf("Average Turnaround Time: %.2f\n", avg_TurnarroundT / n);
    printf("Average Response Time: %.2f\n", avg_ResponseT / n);
}

// الگوریتم FCFS
void fcfs(struct Process proc[], int n) {
    printf("\n=== FCFS ===\n");
    int systemtime = 0;
    for (int i = 0; i < n; i++) {
        if (systemtime < proc[i].ArrivalT) systemtime = proc[i].ArrivalT;
        proc[i].ResponseT_first = systemtime;
        systemtime += proc[i].BurstT;
        proc[i].TurnarroundT = systemtime - proc[i].ArrivalT;
        proc[i].WaitingT = proc[i].TurnarroundT - proc[i].BurstT;
    }
    printMetrics(proc, n);
}

// الگوریتم SJF
void sjf(struct Process proc[], int n) {
    printf("\n=== SJF ===\n");
    int done[MAX] = {0}; 
    int systemtime = 0, completed = 0;
    while (completed < n) {
        int shortestjob = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i] && proc[i].ArrivalT <= systemtime && 
                (shortestjob == -1 || proc[i].BurstT < proc[shortestjob].BurstT)) {
                shortestjob = i;
            }
        }
        if (shortestjob == -1) {
            systemtime++;
            continue;
        }
        if (proc[shortestjob].ResponseT_first == -1) proc[shortestjob].ResponseT_first = systemtime;
        systemtime += proc[shortestjob].BurstT;
        proc[shortestjob].TurnarroundT = systemtime - proc[shortestjob].ArrivalT;
        proc[shortestjob].WaitingT = proc[shortestjob].TurnarroundT - proc[shortestjob].BurstT;
        done[shortestjob] = 1;
        completed++;
    }
    printMetrics(proc, n);
}

// الگوریتم Round Robin 
void roundRobin(struct Process proc[], int n, int quantum) {
    printf("\n=== Round Robin (Quantum: %d) ===\n", quantum);
    int queue[MAX], front = 0, rear = 0;
    int systemtime = 0, completed = 0;
    int in_queue[MAX] = {0};
    
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (!in_queue[i] && proc[i].ArrivalT <= systemtime && proc[i].RemainingT > 0) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }
        //بررسی خالی بودن صف
        if (front == rear) { 
            systemtime++;
            continue;
        }
        int i = queue[front++];
        if (proc[i].ResponseT_first == -1) proc[i].ResponseT_first = systemtime;
        int sliceT = proc[i].RemainingT < quantum ? proc[i].RemainingT : quantum;
        systemtime += sliceT;
        proc[i].RemainingT -= sliceT;
        for (int j = 0; j < n; j++) {
            if (!in_queue[j] && proc[j].ArrivalT <= systemtime && proc[j].RemainingT > 0) {
                queue[rear++] = j;
                in_queue[j] = 1;
            }
        }
        if (proc[i].RemainingT == 0) {
            proc[i].TurnarroundT = systemtime - proc[i].ArrivalT;
            proc[i].WaitingT = proc[i].TurnarroundT - proc[i].BurstT;
            completed++;
        } else {
            queue[rear++] = i;
        }
    }
    printMetrics(proc, n);
}

int main() {
    int n, quantum;
    struct Process proc[MAX], proc_copy[MAX];
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", proc[i].pid);
        scanf("%d %d", &proc[i].ArrivalT, &proc[i].BurstT);
        proc[i].RemainingT = proc[i].BurstT;
        proc[i].ResponseT_first = -1;
    }
    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    memcpy(proc_copy, proc, n * sizeof(struct Process));
    fcfs(proc_copy, n);
    memcpy(proc_copy, proc, n * sizeof(struct Process));
    sjf(proc_copy, n);
    memcpy(proc_copy, proc, n * sizeof(struct Process));
    roundRobin(proc_copy, n, quantum);

    return 0;
}