%option noyywrap
%option noinput
%option nounput

%{

#include <stdio.h>
#include <stdlib.h>
#include "tokeni_v.h"

%}




%%


"stampaj"         {return stampaj_token;}

"sifra"            {return sifra_token;}

0|[1-9][0-9]*        { return broj; }

[=;(),+-]             {return *yytext;}

[a-zA-Z_][a-zA-Z0-9_]*   {return id;}

[ \t\n]             {}

.               {
            fprintf(stderr, "Leksicka greska: %s nije prepoznat!", yytext);
            exit(EXIT_FAILURE);
            }
%%
