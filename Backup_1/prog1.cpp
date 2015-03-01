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
   double gi,hi;
   gi = 20.3;
   object.variable += value;

   hi = 48.2;
   cout<<object.variable;
   //object.variable;  Will produce an error because variable is private

   return 0;
}
