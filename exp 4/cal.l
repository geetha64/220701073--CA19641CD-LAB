%{
#include <stdio.h>
#include <stdlib.h>
%}

%%
[0-9]+    { printf("NUMBER: %s\n", yytext); }
[+\-*/]   { printf("OPERATOR: %s\n", yytext); }
[\n]      { printf("NEWLINE\n"); }
[ \t]     { /* Ignore whitespace */ }
.         { printf("INVALID CHARACTER: %s\n", yytext); }
%%

int main() {
    printf("Enter an expression: ");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
