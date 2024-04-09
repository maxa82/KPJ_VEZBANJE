%option noyywrap
%option noinput
%option nounput



%{

#include<stdio.h>
#include<stdlib.h>
#include "tokeni.h"

%}


%%

"length"                {return length_t;}
"end"                {return end_t;}
"if"                {return if_t;}
"for"                {return for_t;}
"error"                {return error_t;}
"function"                {return function_t;}
"isequal"                {return isequal_t;}

[)(,<:=~\]\[]        {return *yytext;}

0|[1-9][0-9]*            {return broj_t;}
-[1-9][0-9]*            {return broj_t;}


[a-zA-Z0-9]+            {return id_t;}
['][^']*[']            {return tekst_t;}


[%][^\n]*           {}

[ \n\t]             {}


.                   {
            fprintf(stderr, "Leksicka greska: neprepoznata leksema %s!\n", yytext);
            exit(EXIT_FAILURE);
            }



%%
