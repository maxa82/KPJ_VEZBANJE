#include<stdio.h>
#include<stdlib.h>
#include"tokeni.h"

void greska(char* poruka){
    fprintf(stderr,"Sintaksna greska: %s\n", poruka);
    exit(EXIT_FAILURE);
}
/*
 *  NIZ_NAR -> NAR; NIZ_NAR {class_token, id, print_token}
 *             | eps        {eoi}
 * NAR -> class_token id_c_token: NIZ_DEF {class_token}
 *          | id A                          {id}
 *          | print_t(id)                   {print_t}
 * A -> = id_c ()       {=}
 *      | .id(NIZ_ID)      {.}
 * NIZ_DEF -> DEF NIZ_DEF       {def_token}
 *          | eps           {;}
 * DEF -> def_token id(NIZ_ID):NIZ_KOM {def_t}
 * NIZ_KOM -> KOM NIZ_KOM       {kom_t, id}
 *          | eps       {;, def_t}
 *KOM -> kom_token {kom_token}
 *      | id.id = {}  {id}
 * NIZ_ID -> id X {id}
 * X -> , NIZ_ID {,}
 *      | eps {)}
 */
extern int yylex();

int token;

void NIZ_N();
void NIZ_D();
void NAR();
void A();
void X();
void NIZ_ID();
void NIZ_KOM();
void KOM();
void DEF();



int main(){
    token = yylex();

    NIZ_N();

    if(token == eoi){
        printf("Recenica PRIPADA gramatici!\n");
    }else{
        printf("Recenica NE PRIPADA gramatici! \n");
    }

        return 0;

}

void NIZ_N(){
    if(token == class_token || token == id|| token == print_token){
        printf("NIZ_N -> NAR; NIZ_N\n");
        NAR();
        if(token!=';')
            greska("[NIZ_N] Ocekivan ; na ulazu!");
        token = yylex();
        NIZ_N();

    }else if(token == eoi){
            printf("NIZ_N -> EPS\n");
        }else{
            greska("[NIZ_N] Ocekivan class_token, print_token ili eoi na ulazu!");
        }


}
void NAR(){
    if(token == class_token){
        printf("NAR -> class_token id_c : NIZ_D\n");
        token  = yylex();
        if(token!=id_c_token)
            greska("[NAR] Ocekivan id_c_t na ulazu!");
        token = yylex();
        if(token!=':')
            greska("[NAR] Ocekivan : na ulazu!");
        token = yylex();
        NIZ_D();
    }else if(token == id)
    {
            printf("NAR -> id A\n");
            token = yylex();
            A();

        }else if(token == print_token){
            printf("NAR -> print_token(id)\n");
            token = yylex();
            if(token!='(')
                greska("[NAR] Ocekivan ( na ulazu!");
            token = yylex();
            if(token!=id)
                greska("[NAR] Ocekivan id na ulazu!");
            token = yylex();
            if(token!=')')
                greska("[NAR] Ocekivan ) na ulazu!");
            token = yylex();
        }else{
            greska("[NAR] Ocekivan class_token, id ili print_token na ulazu!");
        }


}


void A(){
    if(token == '='){
        printf("A -> = id_c()\n");
        token  = yylex();
        if(token!=id_c_token)
            greska("[A] Ocekivan id_c_t na ulazu!");
        token = yylex();
        if(token!='(')
            greska("[A] Ocekivan ( na ulazu!");
        token = yylex();
        if(token!=')')
            greska("[A] Ocekivan ) na ulazu!");
        token = yylex();

    }else if(token == '.')
    {
            printf("A -> . id (NIZ_ID)\n");
            token = yylex();
            if(token!=id)
                greska("[A] Ocekivan id na ulazu!");
            token = yylex();
            if(token!='(')
                greska("[A] Ocekivan ( na ulazu!");

            token = yylex();

            NIZ_ID();

            if(token!=')')
                greska("[A] Ocekivan ) na ulazu!");
            token = yylex();

        }else{
            greska("[A] Ocekivan = ili . na ulazu!");
        }


}


void NIZ_D(){
    if(token ==def_token){
        printf("NIZ_D -> DEF NIZ_D\n");
        DEF();
        NIZ_D();

    }else if(token == ';')
    {
        printf("NIZ_D -> EPS\n");


    }else{
            greska("[NIZ_D] Ocekivan def_token ili ; na ulazu!");
        }


}
void DEF(){
    if(token ==def_token){
        printf("DEF -> def_t id (NIZ_ID):NIZ_KOM\n");

            token = yylex();
            if(token!=id)
                greska("[DEF] Ocekivan id na ulazu!");
            token = yylex();
            if(token!='(')
                greska("[DEF] Ocekivan ( na ulazu!");
        token = yylex();
        NIZ_ID();
            if(token!=')')
                greska("[DEF] Ocekivan ) na ulazu!");
        token = yylex();
            if(token!=':')
                greska("[DEF] Ocekivan : na ulazu!");
        token = yylex();
        NIZ_KOM();

    }else{
            greska("[DEF] Ocekivan def_t na ulazu!");
        }


}



void NIZ_KOM(){
    if(token == id || token == kom_token){
        printf("NIZ_KOM -> KOM NIZ_KOM\n");
        KOM();
        NIZ_KOM();

    }else if(token == ';' || token == def_token){
            printf("NIZ_KOM -> EPS\n");

    }else{
            greska("[NIZ_KOM] Ocekivan id, kom_token, ; ili def_t na ulazu!");
        }


}

void KOM(){
    if(token == kom_token){
        printf("KOM -> kom_token\n");
        token = yylex();

    }else if(token == id){
            printf("NIZ_KOM -> id.id = {}\n");
            token = yylex();
            if(token!='.')
                greska("[KOM] Ocekivan . na ulazu! !");
        token = yylex();
            if(token!=id)
                greska("[KOM] Ocekivan id na ulazu!");
        token = yylex();
            if(token!='=')
                greska("[KOM] Ocekivan = na ulazu!");
        token = yylex();
            if(token!='{')
                greska("[KOM] Ocekivan { na ulazu!");
         token = yylex();
            if(token!='}')
                greska("[KOM] Ocekivan } na ulazu!");
        token = yylex();
    }else{
            greska("[KOM] Ocekivan kom_token ili id na ulazu!");
        }


}

void NIZ_ID(){
    if(token == id){
        printf("NIZ_ID -> id X\n");
        token = yylex();
        X();

    }else{
            greska("[NIZ_ID] Ocekivan id na ulazu!");
        }


}

void X(){
    if(token == ','){
        printf("X -> , NIZ_ID\n");
        token = yylex();
        NIZ_ID();

    }else if(token == ')'){
        printf("X -> EPS\n");

    }else{
            greska("[X] Ocekivan ) ili , na ulazu!");
        }


}


