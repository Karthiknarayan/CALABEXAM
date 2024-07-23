#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define noi 6 
#define nfu 2
typedef struct  {
  char type;
  int src1; 
  int src2;
  int target;
}Instructions;

typedef struct {
  char type;
  int OP1; 
  int OP2;
  int result;
  int status;
}FU;

 Instructions ins[noi]={
    {'A', 2, 3, 1}, // Add R1 = R2 + R3
    {'M', 4, 5, 2}, // Multiply R2 = R4 * R5
    {'A', 1, 2, 3}, // Add R3 = R1 + R2
    {'M', 3, 3, 4}, // Multiply R4 = R3 * R3
    {'A', 5, 4, 5}, // Add R5 = R5 + R4
    {'M', 2, 2, 6}  // Multiply R6 = R2 * R2

};

 FU units[nfu];
void execution (int sid, Instructions ins)
{
  int i;
  for(i=0;i<10000000;i++);
  if(ins.type=='A')
  {
    units[sid].result=ins.src1+ins.src2;
    
  }
 else  if(ins.type=='M')

  {

    units[sid].result=ins.src1*ins.src2;
    
  }
  units[sid].status=0;
}
int main () 
{
int nthreads, tid;
int i,j;
for(i=0;i<nfu;i++)
units[i].status=0;
#pragma omp parallel for num_threads(noi)
for(i=0;i<noi;i++)
{
  
  int uid=-1;
  #pragma omp critical
  {
  for(j=0;j<nfu;j++)
    if(units[j].status==0)
    {
      uid=j;
     units[j].status=1;
     break;
    }
  }
  if(uid!=-1)
  {
    execution(uid,ins[i]);
    printf("execution instructions=%d\nresult=%d\n",i+1,units[uid].result);
  }
  
  else
    printf("no free fu for instructions%d\n",i+1);
  

}
return 0;
}