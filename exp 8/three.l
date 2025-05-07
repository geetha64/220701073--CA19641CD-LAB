%{
#include "three.tab.h"
#include <string.h>
%}

ID      [a-zA-Z_][a-zA-Z0-9_]*
NUMBER  [0-9]+

%%

{ID}           { yylval.str = strdup(yytext); return ID; }
{NUMBER}       { yylval.str = strdup(yytext); return NUMBER; }
"="            { return ASSIGN; }
[\+\-\*/]      { yylval.str = strdup(yytext); return OPERATOR; }
[\(\)]         { return yytext[0]; }
[ \t\n]+       { /* skip whitespace */ }
";"            { return SEMICOLON; }

%%

int yywrap() { return 1; }
