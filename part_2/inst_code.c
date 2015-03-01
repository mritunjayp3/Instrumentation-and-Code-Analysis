int cntr0=0,cntr1=0,cntr2=0;
int i=0,j=9,k=3;
#include<stdio.h>


int main()
{
	

	if(i==0)
	{
cntr0++;	// Instrumented code
		printf("\nBlock A !!!");
	}
	if(j==9)
	{
cntr1++;	// Instrumented code
		printf("\nBlock B !!!");
	}
	else if(k==3)
	{
cntr2++;	// Instrumented code
		printf("\nBlock C !!!");
	}
 return 0;
}

