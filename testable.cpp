#include<iostream>
#include<cstdlib>
#include<cstdio>
#include "testable.h"
using namespace std;


int main()
{
	int n;
	char nm[45],vn[300];
	cout<<"\nEnter filename: ";
	cin>>nm;
	cout<<"\nEnter variables seperated by , :";
	cin>>vn;
	cout<<"\nNo. of times to execute: ";
	cin>>n;
	char execute_str[400];
	sprintf(execute_str,"./linux %s %s > output.txt",nm,vn);		//To create new output.txt in place of appending to the old one
	system(execute_str);
	sprintf(execute_str,"./linux %s %s >> output.txt",nm,vn);		//To append the new values to the file
    	for(int i=0;i<n-1;i++)
	{
    		system(execute_str);
		
    }
    return 0;
}
