%{
#include <stdio.h>
#include <string.h>

void yyerror(const char *str){
    fprintf(stderr, "error: %s\n", str);
}

int yywrap(){
    return 1;
}

int main(){
    yyparse();
    return 0;

}
%}

%token H12 H24 MIN AM PM

%%
times:  times time
        | time

time:
        H12 AM
        {
            printf("%d:00\n", $1);
        }
        | H12 PM
        {
            printf("%d:00\n", $1 + 12);
        }
        | H12 MIN AM 
        {
            printf("%d:%d\n", $1, $2);
        }
        | H12 MIN PM
        {
            printf("%d:%d\n", $1 + 12, $2);
        }
        | H24 MIN 
        {
            printf("%d:%d\n", $1, $2);
        }
        ;
