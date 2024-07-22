#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define n 50
#define true 1
#define false 0
int main(int argc,char *argv[])
{
    int nthreads;
    int i;
    int found;
    int *a;

    if(argc>1)
    {
        nthreads=atoi(argv[1]);
        if(omp_get_dynamic())
        {
            omp_set_dynamic(0);
        }
        omp_set_num_threads(nthreads);
    }
    printf("max threads=%d\n",omp_get_max_threads);

    a=(int *)malloc((n+1)*sizeof(int));
int k=2;
for(int i=2;i<=n;i++)
a[i]=1;
while (k*k<=n)
{
    for(i=k*k;i<=n;i+=k)
    a[i]=0;
    found=false;
    for(i=k+1;!found;i++)
    {
        if(a[i])
        {
            k=i;
            found=true;
        }
    }
}
int count=0;
for(i=2;i<=n;i++)
{
    if(a[i])
    count++;

}
printf("total prime numbers between 0 to 50 id %d\n",count);

}