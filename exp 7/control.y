%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char* s);
int yylex();
extern FILE* yyin;
%}

%union {
    char* str;
}

%token <str> ID NUM
%token IF ELSE WHILE FOR
%token LE GE EQ NE

%left '<' '>' LE GE EQ NE
%left '+' '-'
%left '*' '/'

%%

program:
      stmt_list
    ;

stmt_list:
      stmt
    | stmt_list stmt
    ;

stmt:
      expr ';'                                 { /* Expression statement - skip message */ }
    | IF '(' expr ')' stmt                     { printf("IF condition works\n"); }
    | IF '(' expr ')' stmt ELSE stmt           { printf("IF-ELSE condition works\n"); }
    | WHILE '(' expr ')' stmt                  { printf("WHILE loop works\n"); }
    | FOR '(' expr ';' expr ';' expr ')' stmt  { printf("FOR loop works\n"); }
    | '{' stmt_list '}'                        { /* Compound statement - no message needed */ }
    ;

expr:
      ID '=' expr            { printf("Assignment: %s = ...\n", $1); }
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '<' expr
    | expr '>' expr
    | expr LE expr
    | expr GE expr
    | expr EQ expr
    | expr NE expr
    | ID
    | NUM
    ;
%%

void yyerror(const char* s) {
    printf("Syntax Error: %s\n", s);
}

int main() {
    printf("Enter a C control structure (Ctrl+Z to stop):\n");
    yyin = stdin;  // set to standard input
    yyparse();
    return 0;
}
