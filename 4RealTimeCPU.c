#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_PROCESS 10

typedef struct {
    int id;
    int burst_time;
    float priority;
} Task;

int num_of_process;
int execution_time[MAX_PROCESS], period[MAX_PROCESS], remain_time[MAX_PROCESS], deadline[MAX_PROCESS], remain_deadline[MAX_PROCESS];

void get_process_info(int selected_algo)
{
    printf("Enter total number of processes (maximum %d): ", MAX_PROCESS);
    scanf("%d", &num_of_process);
    if (num_of_process < 1)
    {
        exit(0);
    }

    for (int i = 0; i < num_of_process; i++)
    {
        printf("\nProcess %d:\n", i + 1);
        printf("==> Execution time: ");
        scanf("%d", &execution_time[i]);
        remain_time[i] = execution_time[i];
        if (selected_algo == 2)
        {
            printf("==> Deadline: ");
            scanf("%d", &deadline[i]);
        }
        else
        {
            printf("==> Period: ");
            scanf("%d", &period[i]);
        }
    }
}

int max(int a, int b, int c)
{
    int max;
    if (a >= b && a >= c)
        max = a;
    else if (b >= a && b >= c)
        max = b;
    else if (c >= a && c >= b)
        max = c;
    return max;
}

int get_observation_time(int selected_algo)
{
    if (selected_algo == 1)
    {
        return max(period[0], period[1], period[2]);
    }
    else if (selected_algo == 2)
    {
        return max(deadline[0], deadline[1], deadline[2]);
    }
}

void print_schedule(int process_list[], int cycles)
{
    printf("\nScheduling:\n\n");
    printf("Time: ");
    for (int i = 0; i < cycles; i++)
    {
        if (i < 10)
            printf("| 0%d ", i);
        else
            printf("| %d ", i);
    }
    printf("|\n");
    for (int i = 0; i < num_of_process; i++)
    {
        printf("P[%d]: ", i + 1);
        for (int j = 0; j < cycles; j++)
        {
            if (process_list[j] == i + 1)
                printf("|RUN ");
            else
                printf("|    ");
        }
        printf("|\n");
    }
}

void rate_monotonic(int time)
{
    int process_list[100] = {0}, min = 999, next_process = 0;
    float utilization = 0;
    for (int i = 0; i < num_of_process; i++)
    {
        utilization += (1.0 * execution_time[i]) / period[i];
    }
    int n = num_of_process;
    int m = (float) (n * (pow(2, 1.0 / n) - 1));
    if (utilization > m)
    {
        printf("\nGiven problem is not schedulable under the said scheduling algorithm.\n");
    }
    for (int i = 0; i < time; i++)
    {
        min = 1000;
        for (int j = 0; j < num_of_process; j++)
        {
            if (remain_time[j] > 0)
            {
                if (min > period[j])
                {
                    min = period[j];
                    next_process = j;
                }
            }
        }
        if (remain_time[next_process] > 0)
        {
            process_list[i] = next_process + 1;
            remain_time[next_process] -= 1;
        }
        for (int k = 0; k < num_of_process; k++)
        {
            if ((i + 1) % period[k] == 0)
            {
                remain_time[k] = execution_time[k];
                next_process = k;
            }
        }
    }
    print_schedule(process_list, time);
}

void earliest_deadline_first(int time){
    float utilization = 0;
    for (int i = 0; i < num_of_process; i++){
        utilization += (1.0*execution_time[i])/deadline[i];
    }
    int n = num_of_process;
    if (utilization > 1){
        printf("\nGiven problem is not schedulable under said scheduling algorithm.\n");
    }

    int process[num_of_process];
    int max_deadline, current_process=0, min_deadline,process_list[time];
    bool is_ready[num_of_process];

    for(int i=0; i<num_of_process; i++){
        is_ready[i] = true;
        process[i] = i+1; 
    }

    max_deadline=deadline[0];
    for(int i=1; i<num_of_process; i++){
        if(deadline[i] > max_deadline)
            max_deadline = deadline[i];
    }

    for(int i=0; i<num_of_process; i++){
        for(int j=i+1; j<num_of_process; j++){  
            if(deadline[j] < deadline[i]){
                int temp = execution_time[j];
                execution_time[j] = execution_time[i];
                execution_time[i] = temp;
                temp = deadline[j];
                deadline[j] = deadline[i];
                deadline[i] = temp;
                temp = process[j];
                process[j] = process[i];
                process[i] = temp;
            }
        }
    }

    for(int i=0; i<num_of_process; i++){
        remain_time[i] = execution_time[i];
        remain_deadline[i] = deadline[i];
    }

    for (int t = 0; t < time; t++){
        if(current_process != -1){      
            --execution_time[current_process];
            process_list[t] = process[current_process];
        }   
        else
            process_list[t] = 0;
    
        for(int i=0;i<num_of_process;i++){
            --deadline[i];
            if((execution_time[i] == 0) && is_ready[i]){
                deadline[i] += remain_deadline[i];
                is_ready[i] = false;
            }
            if((deadline[i] <= remain_deadline[i]) && (is_ready[i] == false)){
                execution_time[i] = remain_time[i];
                is_ready[i] = true;
            }
        }
    
        min_deadline = max_deadline;        
        current_process = -1;
        for(int i=0;i<num_of_process;i++){
            if((deadline[i] <= min_deadline) && (execution_time[i] > 0)){               
                current_process = i;
                min_deadline = deadline[i];
            }
        }
    }   
    print_schedule(process_list, time);
}

void proportionalScheduling() {
    int n;
    printf("Enter the number of tasks: ");
    scanf("%d", &n);

    Task tasks[n];
    printf("Enter burst time and priority for each task:\n");
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Task %d - Burst Time: ", tasks[i].id);
        scanf("%d", &tasks[i].burst_time);
        printf("Task %d - Priority: ", tasks[i].id);
        scanf("%f", &tasks[i].priority);
    }

    // Sort tasks based on priority (ascending order)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tasks[j].priority > tasks[j + 1].priority) {
                // Swap tasks
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    printf("\nProportional Scheduling:\n");

    int total_burst_time = 0;
    float total_priority = 0.0;

    for (int i = 0; i < n; i++) {
        total_burst_time += tasks[i].burst_time;
        total_priority += tasks[i].priority;
    }

    for (int i = 0; i < n; i++) {
        float time_slice = (tasks[i].priority / total_priority) * total_burst_time;
        printf("Task %d executes for %.2f units of time\n", tasks[i].id, time_slice);
    }
}


int main()
{
    int option;
    int observation_time;
    printf("\n1. Rate Monotonic\n2. Earliest Deadline first\n3. Proportional Scheduling\nEnter your choice: ");
    scanf("%d", &option);
    switch(option){
        case 1: get_process_info(option);
                observation_time = get_observation_time(option);
                rate_monotonic(observation_time);
                break;
        case 2: get_process_info(option);
                observation_time = get_observation_time(option);
                earliest_deadline_first(observation_time);
                break;
        case 3: proportionalScheduling();
                break;
        default: printf("\nInvalid Statement");
    }
    return 0;
}
