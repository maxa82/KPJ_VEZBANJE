#include <stdio.h>
#include <stdlib.h>
#include "tokeni_v.h"


extern int yylex();

int token;

void greska(char* poruka){
    fprintf(stderr,"Sintaksna greska: %s\n", poruka);
    exit(EXIT_FAILURE);
}

void NIZ_N();
void NAR();
void DEK();
void E();
void EP();
void T();



int main(){

        token = yylex();

        NIZ_N();
        if(token == eoi){
            printf("Recenica je PRIHVACENA!\n");
        }else{
            printf("Recenica NIJE PRIHVACENA!\n");
        }

        return 0;
}

void NIZ_N(){

        if(token == stampaj_token || token == sifra_token){
        printf("NIZ_N -> NAREDBA; NIZ_N\n");

        NAR();

        if(token!=';')
            greska("[NIZ_N] Ocekivan ; na ulazu!");

        token = yylex();

        NIZ_N();


        }else if(token == eoi){
            printf("NIZ_N -> eps\n");
        }else{
            greska("[NIZ_N] Ocekivan stampaj_token, sifra_token ili eoi na ulazu!");

        }  }

void NAR(){

        if(token == stampaj_token){
        printf("NAREDBA-> stampaj_token E\n");

       token = yylex();

       E();

        }else if(token == sifra_token){
            printf("NAREDBA -> sifra_token id DEKLARACIJA\n");
            token = yylex();
            if(token!=id)
                greska("[NAREDBA] Ocekivan id na ulazu!");
            token = yylex();
            DEK();
        }else{
            greska("[NAREDBA] Ocekivan stampaj_token ili sifra_token na ulazu!");

        }  }


void DEK(){

        if(token == '='){
        printf("DEKLARACIJA -> = E\n");

       token = yylex();

       E();

        }else if(token == ';'){
            printf("DEKLARACIJA -> EPS\n");
        }else if(token=='('){
            printf("DEKLARACIJA -> (broj,broj)\n");

            token = yylex();
            if(token!=broj)
                greska("[DEK] Ocekivan broj na ulazu!");
            token = yylex();
            if(token!=',')
                greska("[DEK] Ocekivan , na ulazu!");
            token = yylex();
            if(token!=broj)
                greska("[DEK] Ocekivan broj na ulazu!");
            token = yylex();
            if(token!=')')
                greska("[DEK] Ocekivan ) na ulazu!");

            token = yylex();


        }else{
            greska("[DEK] Ocekivan =, ; ili ( na ulazu!");

        }  }






void E(){

        if(token == id || token==broj){
        printf("E-> T E'\n");

        T();
        EP();

        }else{
            greska("[E] Ocekivan id ili broj na ulazu!");

        }  }

void EP(){

        if(token == '+'){
        printf("E'-> +T E'\n");
        token = yylex();
        T();
        EP();

        }else if(token == '-'){
        printf("E'-> -T E'\n");
        token = yylex();
        T();
        EP();

        }else if(token == ';'){
            printf("E' -> eps\n");
        }else{
            greska("[EP] Ocekivan +,- ili ; na ulazu!");

        }  }

void T(){

        if(token == id){
        printf("T -> id\n");
        token = yylex();

        }else if(token == broj){
        printf("T -> broj\n");
        token = yylex();
        }
       else{
            greska("[T] Ocekivan broj ili id na ulazu!");

        }   }

