#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define NRA 6
#define NCA 6
#define NCB 6
int main(int argc, char * argv[])
{
int chunk=2;
double a[NRA][NCA];
double b[NCA][NCB];
 double c[NRA][NCB];
int tid,nthreads,i,j,k;
#pragma omp parallel shared(a,b,c,nthreads) private(tid,i,j,k)
{
    tid=omp_get_thread_num();
    if(tid==0)
    {
        nthreads=omp_get_num_threads();
        printf("total number of threads is %d\n",nthreads);
    }
    printf("starting matrix mul\n");
    #pragma omp parallel for schedule(static,chunk)
    for(i=0;i<NRA;i++)
        for(j=0;j<NCA;j++)
        a[i][j]=i+j;

    #pragma omp parallel for schedule(static,chunk)
    for(i=0;i<NCA;i++)
        for(j=0;j<NCB;j++)
        b[i][j]=i+j;
     #pragma omp parallel for schedule(static,chunk)
    for(i=0;i<NRA;i++)
        for(j=0;j<NCB;j++)
        c[i][j]=0;
printf("THREAD %d is starting matrix multiplication\n",tid);
#pragma omp parallel for schedule(static,chunk)
    for(i=0;i<NRA;i++)
    {
        printf("thread %d is doing row %d\n", tid, i);
        for(j=0;j<NCB;j++)
        for(k=0;k<NCA;k++)
        c[i][j]=a[i][k]+b[k][j];
}
}
printf("\n\n result\n\n");
 for(i=0;i<NRA;i++){
        for(j=0;j<NCB;j++){
     printf("%6f    ", c[i][j]);
        }
        printf("\n");
 }
return 0;
}



