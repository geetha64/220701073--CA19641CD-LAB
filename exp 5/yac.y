%{
#include <stdio.h>
#include <stdlib.h>

extern char *yytext;
int yylex();
int yyerror(char *msg);
%}

%token IDENTIFIER

%%

variable: IDENTIFIER { printf("Valid variable name: %s\n", yytext); }
        ;

%%

int main() {
    printf("Enter a variable name:\n");
    yyparse();
    return 0;
}

int yyerror(char *msg) {
    printf("invalid variable name", msg);
    return 0;
}

