%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void); // 🔧 Fixes the warning
void yyerror(const char *s);

int temp_count = 0;
char* create_temp() {
    char* temp = (char*)malloc(10);
    sprintf(temp, "t%d", temp_count++);
    return temp;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
%}

%union {
    char* str;
}

%token <str> ID NUMBER OPERATOR
%token ASSIGN SEMICOLON
%type <str> expr

%%

statement:
      ID ASSIGN expr SEMICOLON {
          printf("%s = %s\n", $1, $3);
      }
;

expr:
      expr OPERATOR expr {
          char* temp = create_temp();
          printf("%s = %s %s %s\n", temp, $1, $2, $3);
          $$ = temp;
      }
    | '(' expr ')' {
          $$ = $2;
      }
    | ID {
          $$ = $1;
      }
    | NUMBER {
          $$ = $1;
      }
;

%%

int main() {
    yyparse();
    return 0;
}
