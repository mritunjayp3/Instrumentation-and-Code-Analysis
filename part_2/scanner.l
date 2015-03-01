%option yylineno
%{
#include<stdio.h>
#include "scanner.h"
%}

%%

"if"				return IF;
"else"				return ELSE;
"while"				return WHILE;
"do"				return DO;
"for"				return FOR;
"("				return S_OPENING;
")"				return S_CLOSING;
"{"				return B_OPENING;
"}"				return B_CLOSING;
=      				return ASSIGN;
[a-zA-Z_]+   			return IDENTIFIER;
[0-9]+"."[0-9]+ 		return DOUBLE;
[0-9]+    			return INTEGER;
;         			return END;
[ \t\n]+				;
.    

%%

int yywrap(void)
{
 return 1;
}
