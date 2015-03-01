#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include "scanner.h"
using namespace std;

// Declaration of global variables

int mod_flag = 0,random_flag=NOT_SET;			/*mod_flag to show if the file is modified
							 random_flag -> default value is 0
							0 -> not set
							1 -> randomize values
							2 -> instrument with given values
							*/
					
char *v_name[30],*v_val[30],f_name[FN_SZ],vr_n[VR_SZ],vr_v[VV_SZ];	//"f_name" for storing file name from the menu &  "str" for storing the list of variables to be instrumented

char value[30];   // Variable for function d_rand

// Declaration of external variables

extern int yylex();
extern FILE *yyin;
extern int yylineno;
extern char* yytext;


// Function to tokenize the first argument

void tokenize_name(char *str)
{
     v_name[0]=strtok(str,",");
     int i=1;
     while((v_name[i] = strtok(NULL,","))!=NULL)
     {
       // printf("\n%s",v_name[i]);
         ++i;
     }
}


// Function to tokenize the second argument


void tokenize_val(char *str)
{
     v_val[0]=strtok(str,",");
     int i=1;
     while((v_val[i] = strtok(NULL,","))!=NULL)
     {
       // printf("\n%s",v_val[i]);
         ++i;
     }
}


// Double Randomize

char * d_rand()
{
    int f_rv  =  random()%20 - 10;                // First Random Value
    srand(time(NULL));				//Seeding Random number generator
    int s_rv  =  random()%20 - 10;                // Second Random Value
    srand(time(NULL));				//Seeding Random number generator
    double val = (double)s_rv + (f_rv/100.0);
    sprintf(value,"%2.2f",val);
    return value;

}


inline void func1(char *ident,char *value,char *f_name)              // Function 1 to take input from file and save the instrumented data in temp.cpp
{
    FILE *f1,*f2;
    printf("\n\nModifying file!!!\n\n");
					f1= fopen(f_name,"r");
                    f2=fopen("temp.cpp","w");
                    char line[128];
                    int cnt=0;
                    while(fgets ( line, sizeof line, f1 )!=NULL)
                    {   ++cnt;
                        fputs(line,f2);
                        if(cnt==yylineno)
                        {
                            char ch[50];
                            strcpy(ch,ident);
                            strcat(ch,"+=");
                            strcat(ch,value);
                            strcat(ch,";        // Instrumented code\n");
                            fputs(ch,f2);
                        }
                    }
                    fclose(f2);
                    fclose(f1);

                    ++mod_flag;    // No. of lines instrumented
}


inline void func2(char *ident,char *value)                 // Function 2 to instrument temp.cpp file
{
    FILE *f1,*f2;
    printf("\n\nModifying file!!!\n\n");
					f1= fopen("temp.cpp","r");
                    f2=fopen("temp1.cpp","w");
                    char line[128];
                    int cnt=0;
                    while(fgets ( line, sizeof line, f1 )!=NULL)
                    {   ++cnt;
                        fputs(line,f2);
                        if(cnt==(yylineno+mod_flag))
                        {
                            char ch[50];
                            strcpy(ch,ident);
                            strcat(ch,"+=");
                            strcat(ch,value);
                            strcat(ch,";\t\t\t// Instrumented code \n");
                            fputs(ch,f2);
                        }
                    }
                    fclose(f2);
                    fclose(f1);
                    remove("temp.cpp");
                    rename("temp1.cpp","temp.cpp");
                    ++mod_flag;
}

//Function to instrument the file
void instrument_file()
{  
	int n_return,v_return;
	char ident[38] = DEFAULT;
	yyin = fopen(f_name,"r");
	 n_return = yylex();
	 while(n_return)
	 {    
		if(n_return==IDENTIFIER)
		   strcpy(ident,yytext);
		if(n_return==ASSIGN)
		{
			if(strcmp(ident,DEFAULT)!=0)
			{
			    n_return = yylex();
				if(n_return==INTEGER||n_return==DOUBLE)   // To instrument both Integer and Double value
				{
					char *temp_val = yytext;
				   if(yylex()==END)
				   {
					printf("\nLine no: %d",yylineno);
					printf("\n-> Variable \"%s\" is set to %s\n",ident,temp_val);

					//printf("%s %s %s",argv[0],argv[1],argv[2]);

					int k=0;
		for(k=0;k<4&&v_name[k]!=NULL;k++)   // modify the value 4 to exact NULL condition
                    {
                    if(strcmp(ident,v_name[k])==0)
                    {
                           if(mod_flag == 0)
                           {
                             func1(v_name[k],d_rand(),f_name);
                             //v_name[k]="*";                     // So that variable is instrumented only once
                           }
                           else
                           {
                             func2(v_name[k],d_rand());
                             //v_name[k]="*";                    //  So that variable is instrumented only once
                           }
                    }
                    }
					}
				}
				else
				{
					strcpy(ident,DEFAULT);
				}
			}

		}
		n_return = yylex();
	 }


			if(mod_flag == 0)
				printf("\nVariable assignment(s) not found!!!!!\n");
			else
			{
					printf("\nSuccessfully Instrumented given file!!!! \n \nExecuting the code.....\n\n");
                             // Renaming output file to Inst_code.cpp
                             remove("inst_code.cpp");
                             rename("temp.cpp","inst_code.cpp");


                             // Compiling and executing the instrumented code
                             system("g++ inst_code.cpp -o test");
                             system("./test");
			}
}

// Main Function

int main(int argc,char *argv[])
{

   if(argc < 3)
   {
       //printf("\nArguments Required!!!!!  \n\n Command format:  scanner < file_name.cpp file_name.cpp var_name1,var_name2,var_name3,...");
	/* Menu for the scanner program 
  	   It will have three options for the user
		1. Instrument File
		2. Set Options
		3. Help
		0. Exit
	Menu is optional, User can skip this menu by entering the details in the command line in the given format:
		scanner < file_name.cpp file_name.cpp var_name1,var_name2,var_name3,...    */
	int ch=0,inst=0;
	while(1)
	{
	cout<<"\n\33[4mScanner menu:\33[0m \n\n1. Instrument File \n2. Set Options \n3. Help \n0. Exit\n--> Enter your choice: ";
	cin>>ch;
	switch(ch)
	{
	 case 0:	return 0;
	 case 1:	if(random_flag==NOT_SET)
			{
			cout<<"\n\nFirst set the variable names!!\n";
			ch=0;
			}
			else
			{
			cout<<"\n\nEnter file name(with extension): ";
			cin>>f_name;
			inst=1;
			}
			break;
	 case 2:	cout<<"\n\n1. Randomize values\n2. Set Values\n0. Main Menu \n--> Enter your choice:";
			int ch2;
			cin>>ch2;
			switch(ch2)
			{
			   case 0: break;
			   case 1: char vr[VR_SZ];
				   cout<<"\nEnter the variable names one by one (0 to exit):";
					cin>>vr;
					strcat(vr_n,vr);
				   while(vr[0]!='0')
					{cout<<"--";
						strcat(vr_n,",");
						cin>>vr;
						strcat(vr_n,vr);
					}
				   random_flag = RANDOMIZE;
				   break;
			   case 2: 
				   cout<<"\nEnter the variable names one by one (0 to exit):";
					cin>>vr;
					strcat(vr_n,vr);
				   while(vr[0]!='0')
					{
						strcat(vr_n,",");
						cin>>vr;
						strcat(vr_n,vr);
					}
				   cout<<"\nEnter the variable values respectively (0 to exit):";
					cin>>vr;
					strcat(vr_v,vr);
				   while(vr[0]!='0')
					{
						strcat(vr_v,",");
						cin>>vr;
						strcat(vr_v,vr);
					}
				      random_flag=USE_VALUES;
				   break;
			    default:  cout<<"\n\nWrong Choice!!!!!\n\n";
			}
			break;
	case 3: 	cout<<"\n\n\t-----Help Content-----\n\n";
			break;
	default: 	cout<<"\n\nWrong Choice!!!\n\n";
			break;
	}
		if(random_flag==RANDOMIZE&&inst)
		{	
			tokenize_name(vr_n);
			instrument_file();
		}
		else if(random_flag==USE_VALUES&&inst)
		{
		     	tokenize_name(vr_n);
			tokenize_val(vr_v);
			instrument_file();
		}
	}
	
   }
   else if(argc==3)
    {
	strcpy(f_name,argv[1]);
	tokenize_name(argv[2]);
	random_flag=RANDOMIZE;
    }
   else if(argc==4)
    {
	strcpy(f_name,argv[1]);
	tokenize_name(argv[2]);
	tokenize_val(argv[3]);
	random_flag=USE_VALUES;
    }
   else
    cout<<"\n\n--Help Content--\n\n";
     /* printf("\n-> %s",argv[1]);
       printf("\n-> %s",argv[2]);

					tokenize_val(argv[3]);    Since we are generating random values
					int k;
 for(k=0;v_name[k]!=NULL;k++)   //stop loop if NULL is found
                    {
        printf("\n-> %s",v_name[k]);
                    }
*/
	
	return 0;
}