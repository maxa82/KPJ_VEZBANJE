#include <stdio.h>
#include <stdlib.h>
#include "tokeni_v.h"

/*
GRAMATIKA
NIZ_LABELA -> LAB NIZ_L {id_l_token}
            | eps       {eoi}
LAB -> id_l: NIZ_NAR    {id_l_token}
NIZ_NAR -> NAR NIZ_NAR {FIRST(NAR)}
            | eps {eoi , id_l_token}
NAR ->    enter_token broj,broj {enter_token}
        | cm_token id_p_token, id_p_token {cm_token} (cm -> cmp i mov, id_p id za procesore)
        | j_token id_l_token {j_token} (j_token -> jmp i jge, id_l id za labelu)
        | leave_token {leave_token}
        | ret_token {ret_token}
 */

extern int yylex();
int token;

void greska(char * poruka){
        fprintf(stderr, "Sintaksna greska: %s\n", poruka);
        exit(EXIT_FAILURE);
}



void NIZ_L();
void LAB();
void NIZ_N();
void NAR();


int main(){
    token = yylex();
    NIZ_L();

    if(token==eoi){
        printf("Recenica PRIPADA gramatici!\n");
    }else{
        printf("Recenica NE PRIPADA gramatici!\n");
    }

    return 0;
}


void NIZ_L(){
    if(token == id_l_token){
        printf("NIZ_L -> LAB NIZ_L\n");
        LAB();
        NIZ_L();
    }else if(token == eoi){
        printf("NIZ_L -> EPS\n");

    }else{
        greska("[NIZ_L] Ocekivan id_l_token ili eoi na ulazu!");
    }

}

void LAB(){
    if(token == id_l_token){
        printf("LAB -> id_l: NIZ_N\n");
        token = yylex();
        if(token!= ':')
            greska("[LAB] Ocekivan : na ulazu!");
        token=yylex();
        NIZ_N();
    } else{
        greska("[LAB] Ocekivan id_l_token na ulazu!");
    }

}

void NAR(){
    if(token == enter_token){
        printf("NAR -> enter_token broj, broj\n");
        token = yylex();
        if(token!= broj)
            greska("[NAR] Ocekivan broj na ulazu!");
        token = yylex();
        if(token!= ',')
            greska("[NAR] Ocekivan , na ulazu!");
        token = yylex();
        if(token!= broj)
            greska("[NAR] Ocekivan broj na ulazu!");
        token=yylex();

    } else if(token == j_token){
                printf("NAR -> j_token id_l_token\n");
                token = yylex();
                if(token!= id_l_token)
                     greska("[NAR] Ocekivan id_l_token na ulazu!");
                token= yylex();
    }else if(token == cm_token){
                printf("NAR -> cm_token id_p_token, id_p_token\n");
                token = yylex();
                if(token!= id_p_token)
                    greska("[NAR] Ocekivan id_p_token na ulazu!");
        token = yylex();
        if(token!= ',')
            greska("[NAR] Ocekivan , na ulazu!");
        token = yylex();
        if(token!= id_p_token)
            greska("[NAR] Ocekivan id_p_token na ulazu!");
        token=yylex();
    }else if( token == leave_token){
        printf("NAR -> leave\n");
        token = yylex(); }else if(token == ret_token){
        printf("NAR -> ret\n");
            token = yylex();
        }else{
        greska("[NAR] Ocekivan ret, leave, cm_token, j_token ili enter_token na ulazu!");
    }

}

void NIZ_N(){
    if(token == enter_token || token == cm_token || token== j_token || token== leave_token || token == ret_token){
        printf("NIZ_N -> NAR NIZ_N\n");
        NAR();
        NIZ_N();
    } else if(token == eoi || token == id_l_token){
        printf("NIZ_N -> EPS\n");
    }else{
        greska("[NIZ_N] Ocekivan FIRST(NAR), id_l_token ili eoi na ulazu!");
    }

}









