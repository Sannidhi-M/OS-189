#include<stdio.h>
#include<limits.h>
void swap(int *a, int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
void main()
{
    int n,bt[10],at[10],pid[10],tat[10],wt[10],comp[10],rem[10];
    printf("Enter the number of processes:\n");
    scanf("%d",&n);
    printf("Enter the process id:\n");
   for (int i = 0; i < n; i++)
   {
      scanf("%d", &pid[i]);
   }
   printf("Enter the arrival time of the processes:\n");
   for (int i = 0; i < n; i++)
   {
      scanf("%d", &at[i]);
   }
   printf("Enter the burst time of the processes:\n");
   for (int i = 0; i < n; i++)
   {
      scanf("%d", &bt[i]);
   }

//sort based on arrival time
for(int i=0;i<n-1;i++)
{
    for(int j=0;j<n-i-1;j++)
    {
        if(at[j]>at[j+1])
        {
            swap(&at[j],&at[j+1]);
            swap(&bt[j],&bt[j+1]);
            swap(&pid[j],&pid[j+1]);
        }
    }
}
for(int i=0;i<n;i++)
{
    rem[i]=bt[i];
    comp[i]=0;
}
int curr_time=0;
int comp_processes=0;
while(comp_processes<n)
{
    int short_rem_time=INT_MAX;
    int selected=-1;
    for(int i=0;i<n;i++)
    {
        if(at[i]<=curr_time && rem[i]>0 && rem[i]<short_rem_time)
        {
            short_rem_time=rem[i];
            selected=i;
        }
    }
    if(selected==-1)
    {
        curr_time++;
        continue;
    }
    rem[selected]--;
    curr_time++;

    if(rem[selected]==0)
    {
        comp[selected]=curr_time;
        comp_processes++;
    }
}
for(int i=0;i<n;i++)
{
    tat[i]=comp[i]-at[i];
    wt[i]=tat[i]-bt[i];
}
printf("Process\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", pid[i], comp[i], tat[i], wt[i]);

}
}