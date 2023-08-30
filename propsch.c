#include<stdio.h>
void main ()
{
  
int n, temp1, temp2,temp3;
  
printf ("Enter the number of tasks: ");
  
scanf ("%d", &n);
  
int bt[n], prior[n], task[n];
  
 
printf ("Enter burst time and priority for each task:\n");
  
for (int i = 0; i < n; i++)
    {
      task[i] = i+1;
printf ("Burst Time of %d : ", i + 1);
      
scanf ("%d", &bt[i]);
      
printf ("Priority of %d : ", i + 1);
      
scanf ("%f", &prior[i]);
    
} 
 
    // Sort tasks based on priority (ascending order)
    for (int i = 0; i < n - 1; i++)
    {
      
for (int j = 0; j < n - i - 1; j++)
	{
	  
if (prior[j] > prior[j + 1])
	    {
	      
		// Swap tasks
		temp1 = prior[j];
	      
temp2 = bt[j];
temp3 = task[j];
	      
prior[j] = prior[j + 1];
	      
bt[j] = bt[j + 1];
task[j] = task[j + 1];
	      
prior[j + 1] = temp1;
	      
bt[j + 1] = temp2;
task[j + 1] = temp3;
	    
}
	
}
    
}
  
 
printf ("\nProportional Scheduling:\n");
  
 
int total_burst_time = 0;
  
float total_priority = 0.0;
  
 
for (int i = 0; i < n; i++)
    {
      
total_burst_time += bt[i];
      
total_priority += prior[i];
  
} 
 
for (int i = 0; i < n; i++)
    {
      
float time_slice = (prior[i] / total_priority) * total_burst_time;
      
printf ("Task %d executes for %.2f units of time\n", task[i],
	       time_slice);

} 
}
