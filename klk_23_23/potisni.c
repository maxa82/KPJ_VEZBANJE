#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define YYDEBUG
#include "tokeni.h"
#define MAX 10000

extern int yylex();

int sp;

int stek[MAX];

bool pun(){
    return sp==MAX;
}
bool prazan(){
    return sp==0;
}

int skini_sa_steka(){
    if(prazan()){
        fprintf(stderr, "GRESKA: Prazan je stek!\n");
        exit(EXIT_FAILURE);
    }
    return stek[--sp];
}
void greska(char *poruka){
    fprintf(stderr, "Sintaksna greska!: %s\n", poruka);
    exit(EXIT_FAILURE);
}
void stavi_na_stek(int elem){
    if(pun()){
        fprintf(stderr, "GRESKA: Pun je stek!\n");
        exit(EXIT_FAILURE);
    }
     stek[sp++] = elem;
}

int token;


int main(){
    token = yylex();

    stavi_na_stek(F);

    while(!prazan()){

        int element = skini_sa_steka();

        switch(element){

            case F:
                if(token == function_t){
                    #ifdef YYDEBUG
                    printf("F -> function id = id(id) NIZ_NAREDBI\n");
                    #endif
                    stavi_na_stek(NIZ_N);
                    stavi_na_stek(')');
                    stavi_na_stek(id_t);
                    stavi_na_stek('(');
                    stavi_na_stek(id_t);
                    stavi_na_stek('=');
                    stavi_na_stek(id_t);
                    stavi_na_stek(function_t);

                }else{
                    greska("[F]\n");
                }
                break;
            case NIZ_N:
                if(token == if_t || token == id_t ||
                    token == for_t ||token == error_t
                ){
                    #ifdef YYDEBUG
                    printf("NIZ_NAREDBI -> NAREDBA NIZ_NAREDBI\n");
                    #endif
                    stavi_na_stek(NIZ_N);
                    stavi_na_stek(NAR);

                }else if(token == eoi_t || token== end_t){
#ifdef YYDEBUG
                    printf("NIZ_NAREDBI -> EPS\n");
#endif

                }else{
                    greska("[NIZ_NAR]\n");
                }
                break;
            case NAR:
                if(token == if_t){
                    #ifdef YYDEBUG
                    printf("NAREDBA -> if A\n");
                    #endif
                    stavi_na_stek(A);
                    stavi_na_stek(if_t);

                }else if(token == for_t){
                    #ifdef YYDEBUG
                    printf("NAREDBA ->for id = B\n");
                    #endif
                    stavi_na_stek(B);
                    stavi_na_stek('=');
                    stavi_na_stek(id_t);
                    stavi_na_stek(for_t);

                }else if(token == error_t){
                    #ifdef YYDEBUG
                    printf("NAREDBA -> error(tekst)\n");
                    #endif
                    stavi_na_stek(')');
                    stavi_na_stek(tekst_t);
                    stavi_na_stek('(');
                    stavi_na_stek(error_t);

                }else if(token == id_t){
                    #ifdef YYDEBUG
                    printf("NAREDBA -> id(id) = [NIZ_BROJEVA]\n");
                    #endif
                    stavi_na_stek(']');
                    stavi_na_stek(NIZ_BR);
                    stavi_na_stek('[');
                    stavi_na_stek('=');
                    stavi_na_stek(')');
                    stavi_na_stek(id_t);
                    stavi_na_stek('(');
                    stavi_na_stek(id_t);

                }else{
                    greska("[NAR]\n");
                }
                break;
            case A:
                if(token == length_t){
                    #ifdef YYDEBUG
                    printf("A -> length(id)<broj NIZ_NAREDBI end\n");
                    #endif
                    stavi_na_stek(end_t);
                    stavi_na_stek(NIZ_N);
                     stavi_na_stek(broj_t);
                    stavi_na_stek('<');
                     stavi_na_stek(')');
                    stavi_na_stek(id_t);
                     stavi_na_stek('(');
                    stavi_na_stek(length_t);


                }else if(token == '~'){
                    #ifdef YYDEBUG
                    printf("A -> ~isequal(id,id) NIZ_NAREDBI end\n");
                    #endif
                    stavi_na_stek(end_t);
                    stavi_na_stek(NIZ_N);

                     stavi_na_stek(')');
                    stavi_na_stek(id_t);
                    stavi_na_stek(',');
                    stavi_na_stek(id_t);
                     stavi_na_stek('(');
                    stavi_na_stek(isequal_t);
                    stavi_na_stek('~');
                }else if(token == isequal_t){
                    #ifdef YYDEBUG
                     printf("A -> isequal(id,id) NIZ_NAREDBI end\n");
                     #endif
                    stavi_na_stek(end_t);
                    stavi_na_stek(NIZ_N);

                     stavi_na_stek(')');
                    stavi_na_stek(id_t);
                    stavi_na_stek(',');
                    stavi_na_stek(id_t);
                     stavi_na_stek('(');
                    stavi_na_stek(isequal_t);
                   // stavi_na_stek('~');
                }else{
                    greska("[A]");
                }
                break;
            case B:
                if(token == length_t){
                    #ifdef YYDEBUG
                     printf("B -> length(id):broj:broj NIZ_NAREDBI end\n");
                     #endif
                    stavi_na_stek(end_t);
                    stavi_na_stek(NIZ_N);
                     stavi_na_stek(broj_t);
                    stavi_na_stek(':');
                    stavi_na_stek(broj_t);
                    stavi_na_stek(':');
                     stavi_na_stek(')');
                    stavi_na_stek(id_t);
                     stavi_na_stek('(');
                    stavi_na_stek(length_t);


                }else if(token == broj_t){
                    #ifdef YYDEBUG
                    printf("B -> broj:broj:broj NIZ_NAREDBI end\n");
                    #endif
                    stavi_na_stek(end_t);
                    stavi_na_stek(NIZ_N);
                     stavi_na_stek(broj_t);
                    stavi_na_stek(':');
                    stavi_na_stek(broj_t);
                    stavi_na_stek(':');
                     stavi_na_stek(broj_t);}
                     else{
                         greska("[B]");
                    }
                    break;
            case NIZ_BR:
                if(token == broj_t){
                    #ifdef YYDEBUG
                    printf("NIZ_BROJEVA -> NIZ_BROJEVA'\n");
                    #endif
                    stavi_na_stek(NIZ_BR_P);
                }else if(token == ']'){
                    #ifdef YYDEBUG
            printf("NIZ_BROJEVA -> EPS\n");
            #endif
                }else{
                    greska("[NIZ_BR]");
                }
                break;
            case NIZ_BR_P:
                if(token == broj_t){
                    #ifdef YYDEBUG
                    printf("NIZ_BROJEVA' -> broj NIZ_BROJEVA''\n");
                    #endif
                    stavi_na_stek(NIZ_BR_PP);
                    stavi_na_stek(broj_t);
                }else{
                    greska("[NIZ_BR_P]");
                }
                break;
            case NIZ_BR_PP:
                if(token == ','){
                    #ifdef YYDEBUG
                    printf("NIZ_BROJEVA'' -> , NIZ_BROJEVA'\n");
                    #endif
                    stavi_na_stek(NIZ_BR_P);
                    stavi_na_stek(',');
                }else if(token == ']'){
                    #ifdef YYDEBUG
            printf("NIZ_BROJEVA'' -> EPS\n");
                #endif
                }else{
                    greska("[NIZ_BR_PP]");
                }
                break;
            default:
                if(token!=element){
                    fprintf(stderr,"Token i element se ne poklapaju!\n");
                    exit(EXIT_FAILURE);
                }
                token = yylex();



    }


}

    if(token == eoi_t){
        printf("Recenica pripada gramatici!\n");
    }else{
        printf("Recenica NE pripada gramatici!\n");
    }

    return 0;
}




















