int cntr0=0,cntr1=0,cntr2=0,cntr3=0;
int i=0,j=9,k=3;
#include<stdio.h>


int main()
{
	

	if(i==0)
	{
cntr0++;	// Instrumented code
		printf("\nBlock A !!!");
	}
    if(i==2)
    {
cntr1++;	// Instrumented code
        
    }
	if(j==9)
	{
cntr2++;	// Instrumented code
		printf("\nBlock B !!!");
	}
	else if(k==3)
	{
cntr3++;	// Instrumented code
		printf("\nBlock C !!!");
	}
 return 0;
}

