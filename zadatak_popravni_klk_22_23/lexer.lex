%option noyywrap
%option noinput
%option nounput


%{

#include<stdio.h>
#include<stdlib.h>
#include"tokeni.h"

%}


%%

"class"             {return class_token;}

"print"             {return print_token;}

"def"             {return def_token;}

[.,}{;):(#=]         {return *yytext;}

[A-Z][a-zA-Z_]*            {return id_c_token;}

[a-z_][a-zA-Z_0-9]*            {return id;}

[#][^\n]*                {return kom_token;}

[ \t\n]                 {}

.                   {
                fprintf(stderr,"Leksicka greska: nije prepoznato %s !\n", yytext);
                exit(EXIT_FAILURE);
}

%%




























