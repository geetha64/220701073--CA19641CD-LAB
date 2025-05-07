%{
#include "yac.tab.h"
#include <stdio.h>

int yywrap(void) {
    return 1;
}

%}

%%

[a-zA-Z_][a-zA-Z0-9_]*   { return IDENTIFIER; }
\n                       { return 0; }
.                        { return yytext[0]; }

%%
