#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
long long factorial(long long n)
{
    long long out=1;
    for(int i=1;i<n+1;i++)
    out*=i;
return out;
}
int main(int argc, char *argv[])
{
  long long *x;
  long long n=12;
    int i,j, nthreads;
    if(argc>1)
    {
        nthreads=atoi(argv[1]);
        if(omp_get_dynamic())
        {
            omp_set_dynamic(0);
            printf("called   omp_set_dynamic(0)\n ");
        }
    }
    printf("%d threads\n",omp_get_max_threads());
    x=( long long *)malloc(n*sizeof(long));
    for(i=0;i<n;i++)
    x[i]=factorial(i);
    j=0;
    #pragma omp parallel for firstprivate(x,j)
        for(i=1;i<n;i++)
        {
            j+=i;
           x[i]=j*x[i-1];
        }

    

    for(i=0;i<n;i++)
    printf("factorial[%d]= %10lld\t\tx[%d]=%10lld\n",i,factorial(i),i,x[i]);


}