%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
%}

%%
"int"|"float"|"if"|"else"    { printf("KEYWORD: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*       { printf("IDENTIFIER: %s\n", yytext); }
[0-9]+                       { printf("INTEGER CONSTANT: %s\n", yytext); }
[0-9]*\.[0-9]+               { printf("FLOAT CONSTANT: %s\n", yytext); }
\/\/.*                       { printf("SINGLE-LINE COMMENT\n"); }
\/\*([^*]|\*+[^/*])*\*\/     { printf("MULTI-LINE COMMENT\n"); }
\+|\-|\*|\/|\%|=|==|!=       { printf("OPERATOR: %s\n", yytext); }
[\{\}\(\)\;\,]               { printf("SPECIAL SYMBOL: %s\n", yytext); }
[ \t\n]                      {  }

%%
int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0;
}