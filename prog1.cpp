
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

main()
{
   programming object;

   object.input_value();
   double value = 10.56;
   double gi,hi;
   gi = 20.3;
   object.variable += value;

   hi = 48.2;
   cout<<"\n-> Value: "<<value<<"\n-> gi: "<<gi<<"\n-> hi: "<<hi<<"\n";
   //object.variable;  Will produce an error because variable is private
    gi= 10.1;
   hi = 11.2;
	cout<<"\n-> Value: "<<value<<"\n-> gi: "<<gi<<"\n-> hi: "<<hi<<"\n";
   return 0;
}