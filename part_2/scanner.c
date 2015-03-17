#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include "scanner.h"


// Declaration of global variables

int mod_flag = 0,cntr_val = 0;
char *v_name[30],*v_val[30];
char value[30];   // Variable for function d_rand

// Declaration of external variables

extern int yylex();
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
    srand(time(0));
    int f_rv  =  rand()%20 - 10;                // First Random Value
    srand(time(0));
    int s_rv  =  rand()%20 - 10;                // Second Random Value
    double val = (double)s_rv + (f_rv/100.0);
    sprintf(value,"%2.2f",val);
    return value;

}


inline void create_temp_file(char *f_name)              // Function 1 to take input from file and save the instrumented data in temp.cpp
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


inline void func2()                 // Function 2 to instrument temp.cpp file
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
                       
			/* if(cnt==(yylineno+mod_flag*2-2))
                        {
                            char ch[50];
                            fprintf(f2,"int cntr%d =0;	//Instrumented code \n",cntr_val);
                            //strcat(ch,mod_flag);
                            //strcat(ch,"=0;        // Instrumented code\n");
                            //fputs(ch,f2);
                        }
			else*/

			 if(cnt==(yylineno+mod_flag))
			{
				char ch[50];
                            fprintf(f2,"cntr%d++;	// Instrumented code\n",cntr_val);
				cntr_val++;
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

// Main Function


int main(int argc,char *argv[])
{

   if(argc < 2)
   {
       printf("\nArguments Required!!!!!  \n\n Command format:  scanner < file_name.cpp file_name.cpp \n\n");
       return 1;
   }
     /* printf("\n-> %s",argv[1]);
     //   printf("\n-> %s",argv[2]);

					 tokenize_name(argv[2]);
					//tokenize_val(argv[3]);    Since we are generating random values
					int k;
 for(k=0;v_name[k]!=NULL;k++)   // stop loop if NULL is found
                    {
        printf("\n-> %s",v_name[k]);
                    }
*/
	int n_return,v_return;
	char ident[38] = DEFAULT;
	 n_return = yylex();
	
		create_temp_file(argv[1]);
	 while(n_return)
	 {
		//if(n_return==IDENTIFIER)
		 //  strcpy(ident,yytext);
		

		if(n_return==IF||n_return==FOR||n_return==WHILE)
		{
			n_return=yylex();
			while(n_return!=S_CLOSING)
				n_return=yylex();
			n_return=yylex();
			if(n_return==B_OPENING)
                    func2();
				
                    }
		n_return = yylex();
	 }


			if(mod_flag == 0)
				printf("\n 0 Blocks found!!!!!\n");
			else
			{
				declare_variables();
					printf("\nSuccessfully Instrumented given file!!!! \n \nExecuting the code.....\n\n");
                             // Renaming output file to Inst_code.cpp
                             remove("inst_code.cpp");			//Removing previously instrumented file
                             rename("temp.cpp","inst_code.c");


                             // Compiling and executing the instrumented code
                            // system("g++ inst_code.cpp -o test");
                            // system("./test");
			}
	return 0;
}
