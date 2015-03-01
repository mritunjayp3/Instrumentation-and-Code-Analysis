%option yylineno
%{
#include<stdio.h>
#include "scanner.h"
%}

%%

=      				return ASSIGN;
[a-zA-Z_]+   		return IDENTIFIER;
[0-9]+"."[0-9]+ 	return DOUBLE;
[0-9]+    			return INTEGER;
;         			return END;
[ \t\n]+					;
.    

%%

int yywrap(void)
{
 return 1;
}
