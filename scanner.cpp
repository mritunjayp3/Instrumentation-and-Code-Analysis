#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include "scanner.h"
using namespace std;

// Declaration of global variables

int mod_flag = 0,cntr_val=0,random_flag=NOT_SET,values_flag=NEW_VALUE;
char mi_stat[4]="on",ci_stat[4]="off";					/*mod_flag to show if the file is modified
							 random_flag -> default value is 0
							mi_stat -> multiple Instrumentation of a single variable -> default "on"
							values_flag ->To check if the values to be used are new or old
							0 -> not set
							1 -> randomize values
							2 -> instrument with given values
							*/
	
int tok_n_cnt=0,tok_v_cnt=0;		//Token name and value count			
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
     tok_n_cnt=1;
     while((v_name[tok_n_cnt] = strtok(NULL,","))!=NULL)
     {
       // printf("\n%s",v_name[i]);
         ++tok_n_cnt;
     }
}


// Function to tokenize the second argument


void tokenize_val(char *str)
{
     v_val[0]=strtok(str,",");
     tok_v_cnt=1;
     while((v_val[tok_v_cnt] = strtok(NULL,","))!=NULL)
     {
       // printf("\n%s",v_val[i]);
         ++tok_v_cnt;
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


inline void create_temp_file(char *f_name)              // Function 1 to create a temp file
{
    FILE *f1,*f2;
    printf("\n\nCopying file!!!\n\n");
					f1= fopen(f_name,"r");
                    f2=fopen("temp.cpp","w");
                    char line[128];
                    while(fgets ( line, sizeof line, f1 )!=NULL)
                    {
                        fputs(line,f2);
                    }
                    fclose(f2);
                    fclose(f1);
}

/*
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

inline void func3()                 // Function 2 to instrument temp.cpp file
{
    FILE *f1,*f2;
    printf("\n\nInserting Counter!!!\n\n");
					f1= fopen("temp.cpp","r");
                    f2=fopen("temp1.cpp","w");
                    char line[128];
                    int cnt=0;
                    while(fgets ( line, sizeof line, f1 )!=NULL)
                    {   ++cnt;
                        fputs(line,f2);
                       
			 if(cnt==(yylineno+mod_flag*2-2))
                        {
                            char ch[50];
                            fprintf(f2,"int cntr%d =0;	//Instrumented code \n",cntr_val);
                            //strcat(ch,mod_flag);
                            //strcat(ch,"=0;        // Instrumented code\n");
                            //fputs(ch,f2);
                        }
			else

			 if(cnt==(yylineno+mod_flag))
			{
				
                            //strcat(ch,mod_flag);
                            //strcat(ch,"++;        // Instrumented code\n");
                            //fputs(ch,f2);
			}
                    }
                    fclose(f2);
                    fclose(f1);
                    remove("temp.cpp");
                    rename("temp1.cpp","temp.cpp");
                    ++mod_flag;
}
*/
void declare_variables()
{
	FILE *f1,*f2;	
	f1= fopen("temp.cpp","r");
                    f2=fopen("temp1.cpp","w");
                    char line[128];
                    int cnt=0,i=1;
			fprintf(f2,"int cntr0=0");
		    while(i<cntr_val)
			{
			fprintf(f2,",cntr%d=0",i);
			++i;
			}
			fprintf(f2,";\n");
                    while(fgets ( line, sizeof line, f1 )!=NULL)
                        fputs(line,f2);
	 	    fclose(f2);
                    fclose(f1);
                    remove("temp.cpp");
                    rename("temp1.cpp","temp.cpp");
                    ++mod_flag;
}


//Function to instrument the file
void instrument_file()
{
    
    create_temp_file(f_name);    //Create a temp file for given input file
    
    FILE *f1,*f2;
    printf("\n\nModifying file!!!\n\n");
    f1= fopen("temp.cpp","r");
    f2=fopen("temp1.cpp","w");
    char line[128];
    int cnt=0;
    
    
	int n_return,v_return;
	char ident[38] = DEFAULT;
    
  
    
	yylineno = 1;			//Reset yylineno for each execution
	yyin = fopen(f_name,"r");
	 n_return = yylex();
    
    
    
    int yyline_old = 0;
    
    
	 while(n_return)
	 {
         
         
         
         if(yyline_old!=yylineno)
         {
             fgets ( line, sizeof line, f1 );
             fputs ( line, f2 );
             ++yyline_old;
         }
         
         
         
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
		for(k=0;v_name[k]!=NULL;k++)   // modify the value 4 to exact NULL condition
                    {
                    if(strcmp(ident,v_name[k])==0)
                    {
                       /*    if(mod_flag == 0)
                           {
				if(random_flag==RANDOMIZE)
                             		func1(v_name[k],d_rand(),f_name);
 				else
			     		func1(v_name[k],v_val[k],f_name);
				if(strcmp(mi_stat,"off")==0)
                          		strcpy(v_name[k],"*");                     // So that variable is instrumented only once
                           }
                           else
                           {*/
				if(random_flag==RANDOMIZE)
                {
                    fprintf(f2,"%s+=%s; \t\t\t // Instrumented code \n",v_name[k],d_rand());
                    ++mod_flag;
                }
                else
                {
                    fprintf(f2,"%s+=%s; \t\t\t // Instrumented code \n",v_name[k],v_val[k]);
                    ++mod_flag;
                }
				if(strcmp(mi_stat,"off")==0)
                             	 	strcpy(v_name[k],"*");                  //  So that variable is instrumented only once
                          // }
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
         if(strcmp(ci_stat,"on")==0)            // If counter instrumentation is on
         {
             if(n_return==IF||n_return==FOR||n_return==WHILE)
             {
                 n_return=yylex();
                 while(n_return!=S_CLOSING)
                     n_return=yylex();
                n_return=yylex();
                 if(n_return==B_OPENING)
                 {
                     for(int i=0;i<2;i++)
                     {
                     fgets ( line, sizeof line, f1 );
                     fputs ( line, f2 );
                         ++yyline_old;
                     }
                     fprintf(f2,"cntr%d++;	// Instrumented code\n",cntr_val);
                     cntr_val++;
                     ++mod_flag;
                 }
             }
         }
		n_return = yylex();
         
	 }
    fclose(f2);
    fclose(f1);
    remove("temp.cpp");
    rename("temp1.cpp","temp.cpp");

			if(mod_flag == 0)
				printf("\nVariable assignment(s) not found!!!!!\n");
			else
			{
                if(strcmp(ci_stat,"on")==0)
                    declare_variables();    //Declare counter variables
					printf("\nSuccessfully Instrumented given file!!!! \n \nExecuting the code.....\n\n");
                             // Renaming output file to Inst_code.cpp
                             remove("inst_code.cpp");
                             rename("temp.cpp","inst_code.cpp");


                             // Compiling and executing the instrumented code
                             system("g++ inst_code.cpp -o test");
                             system("./test");
			}
	fclose(yyin);
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
		inst=0;						//To stop invoking the instrument() function automatically at the end
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
	 case 2:	cout<<"\n\n1. Randomize values\n2. Set Values\n3. Multiple Instrumentation ("<<mi_stat<<")\n4. Insert Counter ("<<ci_stat<<")\n0. Main Menu \n--> Enter your choice:";
			int ch2;
			cin>>ch2;
			switch(ch2)
			{
			   case 0: break;
			   case 1: char vr[VR_SZ];
				   cout<<"\nEnter the variable names one by one (0 to exit):";
					cin>>vr;
					strcpy(vr_n,vr);
				   while(vr[0]!='0')
					{
						strcat(vr_n,",");
						cin>>vr;
						strcat(vr_n,vr);
					}
					cout<<vr_n;
				   random_flag = RANDOMIZE;
				   values_flag = NEW_VALUE;
				   break;
			   case 2: 
				   cout<<"\nEnter the variable names one by one (0 to exit):";
					cin>>vr;
					strcpy(vr_n,vr);
				   while(vr[0]!='0')
					{
						strcat(vr_n,",");
						cin>>vr;
						strcat(vr_n,vr);
					}
				   cout<<"\nEnter the variable values respectively (0 to exit):";
					cin>>vr;
					strcpy(vr_v,vr);
				   while(vr[0]!='0')
					{
						strcat(vr_v,",");
						cin>>vr;
						strcat(vr_v,vr);
					}
				      random_flag=USE_VALUES;
				      values_flag=NEW_VALUE;
				   break;
			    case 3:		int temp_value;
				  cout<<"\nEnter option(0 -> off / 1 -> on):";
				  cin>>temp_value;
					if(temp_value==0)
						strcpy(mi_stat,"off");
					else if(temp_value==1)
						strcpy(mi_stat,"on");
					else
						cout<<"\n\nWrong option entered!!!  Exiting!!!!\n";
				  break;
                case 4:
                    cout<<"\nEnter option(0 -> off / 1 -> on):";
                    cin>>temp_value;
                    if(temp_value==0)
                        strcpy(ci_stat,"off");
                    else if(temp_value==1)
                        strcpy(ci_stat,"on");
                    else
                        cout<<"\n\nWrong option entered!!!  Exiting!!!!\n";
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
			if(values_flag==NEW_VALUE)			//To tokenize values only if new values are entered otherwise use old values
			{
			tokenize_name(vr_n);
			values_flag=OLD_VALUE;
			}
            mod_flag = 0; cntr_val=0;
			instrument_file();
			if(strcmp(mi_stat,"off")==0)
				random_flag=NOT_SET;
		}
		else if(random_flag==USE_VALUES&&inst)
		{
		     	if(values_flag==NEW_VALUE)			//To tokenize values only if new values are entered otherwise use old values
			{
			tokenize_name(vr_n);
			tokenize_val(vr_v);
			values_flag=OLD_VALUE;
			}
			if(tok_n_cnt!=tok_v_cnt)
				cout<<"\nNumber of variables and values should be same!!!\n";
			else
			{
                mod_flag = 0; cntr_val=0;
			instrument_file();
			if(strcmp(mi_stat,"off")==0)
				random_flag=NOT_SET;
			}
		}
	}
	
   }
   else if(argc==3)
    {
	strcpy(f_name,argv[1]);
	tokenize_name(argv[2]);
	random_flag=RANDOMIZE;
	instrument_file();
    }
   else if(argc==4)
    {
	strcpy(f_name,argv[1]);
	tokenize_name(argv[2]);
	tokenize_val(argv[3]);
	random_flag=USE_VALUES;
	if(tok_n_cnt!=tok_v_cnt)
		cout<<"\n\nNumber of variables and values should be same....!!\n\n";
	else
	instrument_file();
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
