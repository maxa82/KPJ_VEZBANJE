%option noyywrap
%option noinput
%option nounput



%{
    #include<iostream>
    #include<cstdlib>
    #include<vector>
    #include<map>
    #include<set>

    using namespace std;


    #include"parser.tab.hpp"


%}


%%

"Set"           {return skup_token;}
"proizvod"      {return proizvod_token;}
"print"            {return print_token;}

"/\\"           {return presek_token;}
"\\/"           {return unija_token;}

"\""[^"]*"\""       {
    yylval.s = new string(yytext);
    return string_token;}

[a-zA-Z_][a-zA-Z_0-9]+      {
    yylval.s = new string(yytext);
    return id_token;}

-?[0-9]+        {
    yylval.i = atoi(yytext);
    return num_token;}

#[^\n]*              {}

[={};,()~^-]          {return *yytext;}

[ \n\t]             {}

.           {
        cerr<<"LEX GRESKA: "<<*yytext<<endl;
        exit(EXIT_FAILURE);


}

%%



