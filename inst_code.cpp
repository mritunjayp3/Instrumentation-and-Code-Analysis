int cntr0=0;

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
value+=1.23;			// Instrumented code 
   double gi,hi;
   gi = 20.3;
gi+=1.33;			// Instrumented code 
   object.variable += value;
    
    if(gi<20)
    {
cntr0++;	// Instrumented code
        cout<<"\nGi is less than 20.";
    }
    
   hi = 48.2;
hi+=4.21;			// Instrumented code 
   cout<<"\n-> Value: "<<value<<"\n-> gi: "<<gi<<"\n-> hi: "<<hi<<"\n";
   //object.variable;  Will produce an error because variable is private
    gi= 10.1;
gi+=1.33;			// Instrumented code 
   hi = 11.2;
hi+=4.21;			// Instrumented code 
	cout<<"\n-> Value: "<<value<<"\n-> gi: "<<gi<<"\n-> hi: "<<hi<<"\n";
   return 0;
}
