#include<stdio.h>


char **tokenize(char *str)
{
     char **token,*temp;
     token[0]=strtok(str,",");
        printf("\n%s",token[0]);
     int i=1;
     while((token[i] = strtok(NULL,","))!=NULL)
     {
        printf("\n%s",token[i]);
         ++i;
     }
    return token;
}

main(int argc,char *argv[])
{
    char **n;
    int k=0;
    n=tokenize(argv[1]);
   for(k=0;k<4&&n[k]!=NULL;k++)   // modify the value 4 to exact NULL condition
                    {
        printf("\n-> %s",n[k]);
                    }
}
