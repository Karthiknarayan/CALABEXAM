#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define num_instructions 6
#define num_functional_units 2
typedef struct 
{
   char type;   
   int src1;
   int src2;
   int target;
}Instructions;
typedef struct 
{
   char type;   
   int op1;
   int op2;
   int result;
   int status;
}Functional_units;


Instructions inst[num_instructions]={
     {'A', 2, 3, 1}, // Add R1 = R2 + R3
    {'M', 4, 5, 2}, // Multiply R2 = R4 * R5
    {'A', 1, 2, 3}, // Add R3 = R1 + R2
    {'M', 3, 3, 4}, // Multiply R4 = R3 * R3
    {'A', 5, 4, 5}, // Add R5 = R5 + R4
    {'M', 2, 2, 6}  // Multiply R6 = R2 * R2
};
Functional_units units[num_functional_units];

void execution(int statusid,Instructions inst)
{
   for (int i = 0; i < 100000000; ++i); 
if(inst.type=='A')
units[statusid].result=inst.src1+inst.src2;
else if(inst.type=='M')
units[statusid].result=inst.src1*inst.src2;

units[statusid].status=0;
}
int main()
{
    int i,j,unitid;

    for(i=0;i<num_functional_units;i++)
    units[i].status=0;

    #pragma omp parallel for num_threads(num_instructions)
    for(i=0;i<num_instructions;i++)
    {
        unitid=-1;
    

    #pragma omp critical
    {

        for(j=0;j<num_functional_units;j++)
                if(units[j].status==0)
                     {
                         unitid=j;
                        units[j].status=1;
                         break;
                     }
    }
    if(unitid!=-1)
    {
        execution(unitid,inst[i]);
        printf("executed instruction %d\n result is stoted in %d\n\n",i+1, units[unitid].result);

    }
else{
printf("no free functional unit\n");
    }
    }
return 0;
    
}