#include<stdio.h>
#include<limits.h>
#include<stdbool.h>

struct Process{
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int priority;
};

void fcfs(struct Process[], int);
void sjf(struct Process[], int);
void srtf(struct Process[], int);
void priority(struct Process[], int);
void round_robin(struct Process[], int);
void display(struct Process[], int);

int main(){
    int n , algo , quantum;
    struct Process process[10];

    printf("\nEnter the number of process: ");
    scanf("%d",&n);
    printf("\nEnter the Process Details\n");
    for(int i = 0 ; i < n ; i++){
        printf("\nProcess %d\n",i+1);
        printf("\nEnter the Arrival Time: ");
        scanf("%d",&process[i].arrivalTime);
        printf("\nEnter the Burst Time: ");
        scanf("%d",&process[i].burstTime);
    }

    printf("\n1.FCFS\n2.SJF\n3.SRTF\n4.Priority\n5.RR\nSelect an algorithm: ");
    scanf("%d",&algo);

    switch(algo){
        case 1: fcfs(process, n);
                break;
        case 2: sjf(process, n);
                break;
        case 3: srtf(process, n);
                break;
        case 4: priority(process, n);
                break;
        case 5: round_robin(process, n);
                break;
        default: printf("\nInvalid Choice!");
    }
    return 0;
}

void display(struct Process process[], int n){
    printf("\nProcess Number\tArrival Time\t Burst Time\tWaiting Time\tTurnAround Time\t Completion Time\n");
    for(int i = 0 ; i < n; i++){
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i+1,process[i].arrivalTime,process[i].burstTime,process[i].waitingTime,process[i].turnAroundTime,process[i].completionTime);
    }
}

void fcfs(struct Process process[], int n){
    for(int i = 0 ; i < n-1 ; i++){
        for(int j = i+1 ; j < n ; j++){
            if(process[i].arrivalTime > process[j].arrivalTime){
                struct Process temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    int currentTime = 0;
    int k = 0;
    while(k<n){
        if(currentTime < process[k].arrivalTime){
            currentTime = process[k].arrivalTime;
        }
        process[k].completionTime = process[k].burstTime + currentTime;
        process[k].turnAroundTime = process[k].completionTime - process[k].arrivalTime;
        process[k].waitingTime = process[k].turnAroundTime - process[k].burstTime;
        currentTime = process[k].completionTime;
        k++; 
    }
    display(process,n);
}

void sjf(struct Process process[], int n){
    bool completed[n];
    for(int i = 0 ; i < n; i++){
        completed[i] = false;
    }
    int completedProcess = 0;
    int currentTime = 0;

    while(completedProcess < n){
        int shortestJob = -1;
        int shortestTime = INT_MAX;

        for(int i = 0 ; i < n ; i++){
            if(!completed[i] && process[i].arrivalTime <= currentTime && process[i].burstTime < shortestTime){
                shortestJob = i;
                shortestTime = process[i].burstTime;
            }
        }

        if(shortestJob == -1){
            currentTime++;
            continue;
        }
        else{
            process[shortestJob].completionTime = currentTime + process[shortestJob].burstTime;
            process[shortestJob].turnAroundTime = process[shortestJob].completionTime - process[shortestJob].arrivalTime;
            process[shortestJob].waitingTime = process[shortestJob].turnAroundTime - process[shortestJob].burstTime;
            currentTime = process[shortestJob].completionTime;
            completedProcess++;
            completed[shortestJob] = true;
        }
    }
    display(process,n);
}

void srtf(struct Process process[], int n){
    int currenntTime = 0;
    int completedProcess = 0;
    bool completed[n];
    int remainingTime[n];

    for(int i = 0 ; i < n ; i++){
        remainingTime[i] = process[i].burstTime;
        completed[i] = false;
    }

    while(completedProcess < n){
        int index = -1;
        int shortestRemainingTime = INT_MAX;
        for(int i = 0 ; i < n ; i++){
            if(!completed[i] && process[i].arrivalTime <= currenntTime && remainingTime[i] < shortestRemainingTime){
                index = i;
                shortestRemainingTime = remainingTime[i];
            }
        }
        if(index == -1){
            currenntTime++;
            continue;
        }
        else{
            remainingTime[index]--;

            if(remainingTime[index] == 0){
                process[index].completionTime = currenntTime+1;
                process[index].turnAroundTime = process[index].completionTime - process[index].arrivalTime;
                process[index].waitingTime = process[index].turnAroundTime - process[index].burstTime;
                completedProcess++;
                completed[index] = true;
            }
            currenntTime++;
        }
    }
    display(process,n);
}

void priority(struct Process process[], int n){
    int completedProcess = 0;
    bool completed[n];
    int currentTime = 0;

    for(int i = 0 ; i < n; i++){
        printf("\nEnter the Priority of Process %d: ",i+1);
        scanf("%d",&process[i].priority);
        completed[i] = false;
    }

    while(completedProcess < n){
        int index = -1;
        int lowestPriority = INT_MAX;
        for(int i = 0 ; i < n ; i++){
            if(!completed[i] && process[i].arrivalTime <= currentTime && process[i].priority < lowestPriority){
                index = i;
                lowestPriority = process[i].priority;
            }
        }

        if(index == -1){
            currentTime++;
            continue;
        }
        else{
            process[index].completionTime = currentTime + process[index].burstTime ;
            process[index].turnAroundTime = process[index].completionTime - process[index].arrivalTime;
            process[index].waitingTime = process[index].turnAroundTime - process[index].burstTime;
            currentTime = process[index].completionTime;
            completedProcess++;
            completed[index] = true;
        }
    }
    display(process, n);
}


void round_robin(struct Process process[], int n) {
    int qt;
    printf("\nEnter Time Quantum: ");
    scanf("%d", &qt);
    int a[n], rem[n];
    int completedProcess = 0, currentTime = 0;
    bool completed[n];

    for(int i = 0; i < n; i++) {
        completed[i] = false;
        a[i] = process[i].arrivalTime;
        rem[i] = process[i].burstTime;
    }

    while(completedProcess < n) {
        int index = -1;
        int small_time = INT_MAX;

        for(int i = 0; i < n; i++) {
            if(!completed[i] && a[i] <= currentTime && a[i] <= small_time) { //very imp <=
                index = i;
                small_time = a[i];
            }
        }

        if(index == -1) {
            currentTime++;
        } else {
            if(rem[index] > qt) {
                rem[index] -= qt;
                currentTime += qt;
                a[index] = currentTime + 0.1;  // Preemption
            } else {
                currentTime += rem[index];
                a[index] = -1;
                process[index].completionTime = currentTime;
                process[index].turnAroundTime = process[index].completionTime - process[index].arrivalTime;
                process[index].waitingTime = process[index].turnAroundTime - process[index].burstTime;
                completedProcess++;
                completed[index] = true; 
            }
        }
    }

    display(process, n);
}