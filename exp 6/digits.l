%{
#include "digits.tab.h"
extern int yylval;
%}

%%

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[\t\n]       ;  // Ignore spaces/tabs
.           { return yytext[0]; }

%%

int yywrap() {
    return 1;
}
