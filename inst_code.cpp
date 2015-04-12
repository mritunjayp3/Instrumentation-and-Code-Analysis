int cntr0=0,cntr1=0;

#include<iostream>

using namespace std;

class programming
{

   public:
      int variable;


      void input_value()
      {
      }
};

int main()
{
   programming object;

   object.input_value();
   double value = 10.56;
   double gi,hi;
   gi = 20.3;
gi+=1.93; 			 // Instrumented code 
   object.variable += value;
    
    if(gi<20)
    {
cntr0++;	// Instrumented code
        //cout<<"\nGi is less than 20.";
    }
    
   hi = 48.2;
hi+=2.02; 			 // Instrumented code 

	if(hi>50)
	{
cntr1++;	// Instrumented code
		//hi block
	}
   //cout<<"\n-> Value: "<<value<<"\n-> gi: "<<gi<<"\n-> hi: "<<hi<<"\n";
   //object.variable;  Will produce an error because variable is private
    gi= 10.1;
gi+=2.02; 			 // Instrumented code 
   hi = 11.2;
hi+=2.02; 			 // Instrumented code 
	//cout<<"\n-> Value: "<<value<<"\n-> gi: "<<gi<<"\n-> hi: "<<hi<<"\n";
cout<<"cntr0\t"<<cntr0<<"\n"<<"cntr1\t"<<cntr1<<"\n";
   return 0;
}
