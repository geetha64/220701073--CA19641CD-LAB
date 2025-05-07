%{
#include <stdio.h>
#include <stdlib.h>
int yylex();              
void yyerror(char *msg);  // Declared as void to match definition
%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%

S: E {
    printf("Result = %d\n", $1);
    return 0;
};

E: E '+' E   { $$ = $1 + $3; }
 | E '-' E   { $$ = $1 - $3; }
 | E '*' E   { $$ = $1 * $3; }
 | E '/' E   { 
     if ($3 == 0) {
         printf("Error: Division by zero\n");
         exit(1);
     }
     $$ = $1 / $3;
   }
 | '(' E ')' { $$ = $2; }
 | NUMBER    { $$ = $1; }
 ;

%%

int main() {
    printf("Enter an arithmetic expression:\n");
    yyparse();
    return 0;
}

void yyerror(char *msg) {
    printf("Syntax Error: %s\n", msg);
}
