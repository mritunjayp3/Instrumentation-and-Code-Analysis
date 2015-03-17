#include<iostream>

using namespace std;

class programming
{

   public:
      int variable;


      void input_value()
      {
         cout << "Enter an integer\n";
         cin >> variable;
      }
};

main()
{
   programming object;

   object.input_value();
   double value = 10.56;
value+=13;        // Instrumented code
   double gi,hi;
   gi = 20.3;
gi+=12.1;			// Instrumented code 
   object.variable += value;

   hi = 48.2;
hi+=11.2;			// Instrumented code 
   cout<<object.variable;
   //object.variable;  Will produce an error because variable is private

   return 0;
}
