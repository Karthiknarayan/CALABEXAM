#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define n 10
int main(int argc, char *argv[])
{
    int fib[n];
    int i;
    fib[0]=0;
    fib[1]=1;
    for(int i=2;i<n+1;i++)
    {
    fib[i]=fib[i-1]+fib[i-2];
    }
    printf("fibonacci  series without loop unrolling\n\n");
    for(i=0;i<n+1;i++)
    {
        printf("%d   ",fib[i]);
    }
    printf("\n");
    #pragma omp unroll partial(4)
      for(int i=2;i<n+1;i++)
    {
    fib[i]=fib[i-1]+fib[i-2];
    }
     printf("\nfibonacci  series with loop unrolling\n\n");
    for(i=0;i<n+1;i++)
    {
        printf("%d   ",fib[i]);
    }
    printf("\n");
}