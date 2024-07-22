#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>
#define N 10
void bubblesort(int a[],int n)
{
int i,j;
n=N;
#pragma omp critical
for(i=0;i<n-1;i++)
{
	for(j=0;j<n-1-i;j++)
	{
		if(a[j+1]<a[j])
		{
			int temp=a[j];
			a[j]=a[j+1];
			a[j+1]=temp;
		}
	}
	
}
}
int main()
{
	int a[N];
	int i;
	#pragma omp parallel for
	for(i=0;i<N;i++)
	{
		a[i]=rand()%100;
	}
	printf("the array elemnts are\n");
	  for(i=0;i<N;i++)
	  {
		  printf("%d ",a[i]);
	  }
	  printf("\n");

#pragma omp parallel shared(a)
	  bubblesort(a,N);

	     printf("the array elemnts are\n");
	               for(i=0;i<N;i++)
			                 {
						     printf("%d ",a[i]);
						     }
	  










}


