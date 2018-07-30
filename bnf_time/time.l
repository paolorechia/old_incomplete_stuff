%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
[0-9]|0[0-9]|1[0-2]     yylval=atoi(yytext); return H12;                  
1[2-9]|2[0-4]           yylval=atoi(yytext); return H24;
:[0-5][0-9]             {char * str=strtok(yytext, ":");
                         yylval=atoi(str); return MIN;
                        }
am|Am|aM|AM             yylval=yytext;       return AM;
pm|Pm|pM|PM             yylval=yytext;       return PM;
\n
[ \t]+
%%
