#include <stdio.h>
#include<stdlib.h>
int a[10][10],b[10][10];
int m,n,p,q,i,j,res;

int main()
{
    int c;
   printf("Enter order of matrix 1:");
   scanf("%d",&m);
   scanf("%d",&n);
   printf("Enter order of matrix 2:");
   scanf("%d",&p);
   scanf("%d",&q);
   
   printf("Enter matrix 1 elements:");
   for(i=0;i<m;i++)
   {
       for(j=0;j<n;j++)
           scanf("%d",&a[i][j]);
   }
   
   printf("Enter matrix 2 elements:");
   for(i=0;i<p;i++)
   {
       for(j=0;j<q;j++)
         scanf("%d",&b[i][j]);
       
   }
  
    printf("Matrix 1\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d \t",a[i][j]);
        }
       printf("\n");
    }
   
    printf("Matrix 2\n");
    for(i=0;i<p;i++)
    {
        for(j=0;j<q;j++)
        {
            printf("%d \t",b[i][j]);
        }
       printf("\n");
    }
   
   do{
       printf("\n\nOperations\n");
       printf("1.Add\n2.Multiply\n3.Is symmetric?\n4.Principle diagonal sum\n5.Non principle diagonal sum\n6.row sum\n7.Column sum\n8.transpose");
       printf("\nEnter choice: ");
       scanf("%d\n",&c);
       switch(c)
       {
       case 1 : add(a,b);
       break;
       case 2 : multiply(a,b);
       break;
       case 3 : res = sym(a);
          if(res==1)
           printf("Matrix 1 is not symmetric!" );
          else
           printf("Matrix 1 symmetric Matrix!");
       break;
       case 4 : res = psum(a);
            printf("Principal diagonal sum of Matrix 1: %d",res);
       break;
       case 5 : res = npsum(a);
           printf("Non Principal diagonal sum of Matrix 1: %d ",res); //
       break;
      case 6 : rsum(a);
       break;
      case 7 : csum(a);
       break;
      case 8 : transpose(a);
      break;
      case 9: exit(0);
      default : printf("Invalid choice");
       }
   }while(c!=9);
    
    return 0;
}


void add(int a[10][10],int b[10][10])
{   
     int ad[10][10];
    if(m!=p && n!=q)
    printf("Cannot add!");
   else
   {
        for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        ad[i][j]=a[i][j]+b[i][j];
       
    }
    
   printf("Resultant matrix\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d \t",ad[i][j]);
        }
       printf("\n");
    }
   }
}


void multiply(int a[10][10], int b[10][10])
{
     int mu[10][10];
  if(n!=p)
    printf("cannot be multiplied!");
  else
  {
  
    for (i=0;i<m;i++)
    {
        for (j=0;j<q;j++)
        {
            for (int k=0;k<n;k++)
            {
                mu[i][j] += a[i][k] * b[k][j];
            }
        }
    }
  } 
    printf("Resultant matrix\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<q;j++)
        {
            printf("%d \t",mu[i][j]);
        }
       printf("\n");
    }
    
}

int sym(int a[10][10]) {
    int flag = 0;
 
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (a[i][j] != a[j][i]) {
                flag = 1;
                break;           
            }
        }
    }
    return flag;
}


int psum(int a[10][10])
{
    int sum=0;
    for (i = 0; i < m; i++) 
    {
     for (j = 0; j < n; j++)
     {
      if (i == j) 
        sum += a[i][j];
     }
    }
    return sum;
}


int npsum(int a[10][10])
{
    int sum = 0;
    for (i = 0, j = n - 1; i < m && j >= 0; i++, j--) 
    {
        sum += a[i][j];
    }
    return sum;
}


void rsum(int a[10][10]) {
    int rs; 
    printf("Row sum: \n");
    for (i = 0; i < m; i++)
    {
     rs=0;
       for (j = 0; j < n; j++) 
       {
            rs += a[i][j];
        }
        printf("%d",rs);
        printf("\n");
    }
    
}

void csum(int a[10][10]) {
    int cs;
        printf("Column sum: \n");
    for (i = 0; i < n; i++)
    {
        cs=0;
       for (j = 0; j < m; j++) 
       {
            cs += a[j][i];
        }
        printf("%d",cs);
        printf("\n");
    }
    
}


void transpose(int a[10][10])
{
    int tp[10][10];
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            tp[j][i] = a[i][j];
        }
    }
    
     printf("Resultant matrix\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d \t",tp[i][j]);
        }
       printf("\n");
    }
}



