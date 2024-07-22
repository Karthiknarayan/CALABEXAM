#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
int a,b,i,tid;
int threads;
float x;
#pragma omp threadprivate(a,x)
int main()
{
    omp_set_dynamic(0);
    printf("first parallel region\n");
    #pragma omp parallel private(b,tid)
    {
a=1.1;
b=1.1;
x=a+b;
tid=omp_get_thread_num();
// threads=omp_get_max_threads();
// printf("max threads=%d\n\n",threads);


printf("tid=%d\n x=%4f\n",tid,x);
    }
    printf("master thread also doing work here\n");
    printf("******\n");
     printf("second parallel region\n");
    #pragma omp parallel private(tid)
    
    {
tid=omp_get_thread_num();
x=tid+6;
printf("tid=%d\n x=%4f\n",tid,x);
    }
}