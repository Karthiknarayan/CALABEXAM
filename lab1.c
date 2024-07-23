#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define n 1000
int main(int argc,  char *argv[])
{
    int a[n],b[n],c[n],d[n];
    int i,tid,nthread;
    for(i=0;i<n;i++)
    {
        a[i]=i*2;
        b[i]=1+1;
        c[i]=0;
        d[i]=0;

    }

tid=omp_get_thread_num();
#pragma omp parallel shared (a,b,c,d,nthread) private(i,tid)
{

    if(tid==0)
    {
    nthread=omp_get_num_threads();
        printf("total number of threas=%d\n",nthread);
    }
    // printf("total number of threas=%d",nthreads)
    printf("thread %d is starting\n",tid);
    #pragma omp sections nowait
    {
        #pragma omp section
        {
            printf("inside section 1\n\n");
            for(i=0;i<n;i++)
            {
                printf("thread %d :",tid);
                c[i]=a[i]+b[i];
                printf("c[%d]=%d\n",i,c[i]);
            }
            
        }


        #pragma omp section
        {
            printf("inside section 2\n\n");
            for(i=0;i<n;i++)
            {
                printf("thread %d :",tid);
                d[i]=a[i]-b[i];
                printf("d[%d]=%d\n",i,d[i]);
            }
    }
    }
}

return 0;
}