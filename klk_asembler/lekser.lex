%option noyywrap
%option noinput
%option nounput



%{
#include<stdio.h>
#include<stdlib.h>
#include"tokeni_v.h"


%}


%%

"enter"         {return enter_token;}
cmp|mov         {return cm_token;}
"leave"         {return leave_token;}
"ret"         {return ret_token;}
[:,]        {return *yytext;}
eax|esi|edi         {return id_p_token;}
jmp|jge             {return j_token;}

0|[1-9][0-9]*        {return broj;}

[a-zA-Z_]+        {return id_l_token;}

[ \t\n]             {}


.           {
        fprintf(stderr,"Leksicka greska: neprepoznato %s!\n", yytext);
        exit(EXIT_FAILURE);
}







%%
