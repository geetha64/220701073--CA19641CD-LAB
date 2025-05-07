%{
#include "control.tab.h"
#include <string.h>
#include <stdlib.h>
%}

%%

"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"for"       { return FOR; }

"<="        { return LE; }
">="        { return GE; }
"=="        { return EQ; }
"!="        { return NE; }

[a-zA-Z_][a-zA-Z0-9_]*    { yylval.str = strdup(yytext); return ID; }
[0-9]+                    { yylval.str = strdup(yytext); return NUM; }

"="         { return '='; }
"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"<"         { return '<'; }
">"         { return '>'; }

"("         { return '('; }
")"         { return ')'; }
"{"         { return '{'; }
"}"         { return '}'; }
";"         { return ';'; }

[ \t\n]+    { /* ignore whitespace */ }
.           { return yytext[0]; }
%%

int yywrap() { return 1; }
