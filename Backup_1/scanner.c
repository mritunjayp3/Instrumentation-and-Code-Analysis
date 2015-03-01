#include<stdio.h>
#include<string.h>
#include "scanner.h"


// Declaration of global variables

int mod_flag = 0;
char *v_name[30],*v_val[30];

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



inline void func1(char *ident,char *value)              // Function 1 to take input from file and save the instrumented data in temp.cpp
{
    FILE *f1,*f2;
    printf("\n\nModifying file!!!\n\n");
					f1= fopen("prog1.cpp","r");
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


// Main Function


int main(int argc,char *argv[])
{

   if(argc < 3)
   {
       printf("\nArguments Required!!!!!  \n\n Command format:  scanner < file_name.cpp var_name1,var_name2,var_name3,... var_val1,var_val2,var_val3,....");
       return 1;
   }
      printf("\n-> %s",argv[1]);
        printf("\n-> %s",argv[2]);

					 tokenize_name(argv[1]);
					tokenize_val(argv[2]);
					int k;
 for(k=0;v_name[k]!=NULL;k++)   // modify the value 4 to exact NULL condition
                    {
        printf("\n-> %s",v_name[k]);
                    }

	int n_return,v_return;
	char ident[38] = DEFAULT;
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
				if(n_return==INTEGER||n_return==DOUBLE)
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
                             func1(v_name[k],v_val[k]);
                             v_name[k]="*";                     // So that variable is instrumented only once
                           }
                           else
                           {
                             func2(v_name[k],v_val[k]);
                             v_name[k]="*";                    //  So that variable is instrumented only once
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


                             // Renaming output file to Inst_code.cpp
                             remove("inst_code.cpp");
                             rename("temp.cpp","inst_code.cpp");
	return 0;
}
