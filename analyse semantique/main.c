#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ID 1
#define PV 2
#define NB 3
#define DP 4
#define AFF 5
#define PGQ 6
#define PGE 7
#define PPQ 8
#define PPE 9
#define EGA 10
#define DIFF 11
#define ADD 12
#define SUB 13
#define OR 14
#define MUL 15
#define DIV 16
#define MOD 17
#define AND 18
#define CMT 19
#define BL 20
#define PO 21
#define PF 22
#define V 23
#define PROGRAM 24
#define VAR 25
#define BEGIN 26
#define END 27
#define INTEGER 28
#define CHR 29
#define IF 30
#define THEN 31
#define ELSE 32
#define WHILE 33
#define DO 34
#define READ 35
#define READLN 36
#define WRITE 37
#define WRITELN 38
#define P 39

#define MAX_TOKEN_LEN 80
#define MAX_OUTPUT_LEX_LEN 500
#define TABLE_LEN 40
#define MAX_LEN 100



void program();
void dcl();
void dcl_prime();
void liste_id();
void liste_id_prime();
void liste_inst();
void liste_inst_prime();
void exp_simple();
void exp_simple_prime();
void terme();
void terme_prime();
void facteur();
void type();
void inst_composee();
void inst();
void Exp();
void s();
void i();
void error(const char *message);
void accepter();
int analyseur_lexical();
// analyse syntaxique
char *file[50];
FILE *f;
int symbol;
void accepter(int t){
    if( symbol ==t){
        symbol =analyseur_lexical(file);
    }else{
        switch (t){
        case 1:

            break;

        default:
            break;
        }
    }
}

void error(const char *message) {
    printf("Erreur de syntaxe : %s\n", message);
    exit(1);
}

void program() {
    if (symbol==PROGRAM){
        accepter(PROGRAM);
        if (symbol==ID) {
            accepter(ID);
            if (symbol==PV) {
                accepter(PV);
                dcl();
                inst_composee();
                    if (symbol==P) {
                        accepter(P);
                    printf("Analyse reussie!\n");
                } else {
                    error("Attendu '.'");
                }
            } else {
                error("Attendu ';' apres id");
            }
        } else {
            error("Attendu un id apres program");
        }
    } else {
        error("Attendu 'program'");
    }
}

void dcl() {
    dcl_prime();
}

void dcl_prime() {
    if (VAR==symbol) {
        accepter(VAR);
        liste_id();
        if (symbol==DP) {
            accepter(DP);
            type();
            if (symbol== PV) {
                accepter(PV);
                dcl_prime();
            } else {
                error("Attendu ';'");
            }
        } else {
            error("Attendu ':'");
        }
    } else {
        return; // epsilon
    }
}

void liste_id() {
    if (symbol ==ID) {
        accepter(ID);
        liste_id_prime();
    } else {
        error("Attendu 'id'");
    }
}

void liste_id_prime() {
    if (symbol==V) {
        accepter(V);
        if (symbol==ID) {
            accepter(ID);
            liste_id_prime();
        } else {
            error("Attendu 'id' apres ','");
        }
    }
}

void liste_inst() {
    i();
    liste_inst_prime();
}

void liste_inst_prime() {
    if (symbol==PV) {
        accepter(PV);
        i();
        liste_inst_prime();
    }
}
void exp_simple() {
    terme();
    exp_simple_prime();
}

void exp_simple_prime() {
    if (symbol==ADD){
        accepter(ADD);
        terme();
        exp_simple_prime();
    }else if (symbol==SUB){
        accepter(SUB);
        terme();
        exp_simple_prime();
    }else if (symbol==OR){
        accepter(OR);
        terme();
        exp_simple_prime();
    }
}

void terme() {
    facteur();
    terme_prime();
}

void terme_prime() {
    if (symbol==MUL){
        accepter(MUL);
        facteur();
        terme_prime();
    }else if (symbol==DIV){
        accepter(DIV);
        facteur();
        terme_prime();
    }else if (symbol==MOD){
        accepter(MOD);
        facteur();
        terme_prime();
    }else if (symbol==AND){
        accepter(AND);
        facteur();
        terme_prime();
    }
}

void facteur() {
    if (symbol==ID) {
        accepter(ID);
        return;
    } else if (symbol==NB) {
        accepter(NB);
        return;
    } else if (symbol==PO) {
        accepter(PO);
        exp_simple();
        if (symbol==PF) {
            accepter(PF);
            return;
        } else {
            error("Attendu ')'");
        }
    } else {
        error("Attendu id, nb, ou (exp)");
    }
}

void type() {
    if (symbol==INTEGER) {
        accepter(INTEGER);
        return;
    } else if(symbol==CHR){
        accepter(CHR);
        return;
    }else{
        error("Attendu 'integer' ou 'char'");
    }
}

void inst_composee() {
    if (BEGIN==symbol) {
        accepter(BEGIN);
        inst();
        if (symbol==END) {
            accepter(END);
            return;
        } else {
            error("Attendu 'end'");
        }
    } else {
        error("Attendu 'begin'");
    }
}

void inst() {
    liste_inst();
}

void Exp() {
    exp_simple();
    if (symbol==PGQ) {
        accepter(PGQ);
        exp_simple();
    }else if (symbol==PGE) {
        accepter(PGE);
        exp_simple();
    }else if (symbol==PPQ) {
        accepter(PPQ);
        exp_simple();
    }else if (symbol==PPE) {
        accepter(PPE);
        exp_simple();
    }else if (symbol==EGA) {
        accepter(EGA);
        exp_simple();
    }else if (symbol==DIFF) {
        accepter(DIFF);
        exp_simple();
    }
}


void i() {
    if (symbol==ID) {
        accepter(ID);
        if (symbol==AFF) {
            accepter(AFF);
            exp_simple();
        } else {
            error("Attendu ':=' apres l'identifiant");
        }
    } else if (symbol==IF) {
        accepter(IF);
        Exp();
        if (symbol==THEN) {
            accepter(THEN);
            i();
            if (symbol==ELSE) {
                accepter(ELSE);
                i();
            } else {
                error("Attendu 'else'");
            }
        } else {
            error("Attendu 'then' apres l'expression");
        }
    } else if (symbol==WHILE) {
        accepter(WHILE);
        Exp();
        if (symbol==DO) {
            accepter(DO);
            i();
        } else {
            error("Attendu 'do' apres l'expression");
        }
    }else if (symbol==READ) {
        accepter(READ);
        if(symbol==PO){
            accepter(PO);
            if(symbol==ID){
                accepter(ID);
                if(symbol==PF){
                    accepter(PF);
                }else{
                    error("Attendu ')' apres l'expression");
                }
            }else{
                error("Attendu 'id' apres l'expression");
            }
        }else{
            error("Attendu '(' apres l'expression");
        }
        return;
    }else if (symbol==READLN) {
        accepter(READLN);
        if(symbol==PO){
            accepter(PO);
            if(symbol==ID){
                accepter(ID);
                if(symbol==PF){
                    accepter(PF);
                }else{
                    error("Attendu ')' apres l'expression");
                }
            }else{
                error("Attendu 'id' apres l'expression");
            }
        }else{
            error("Attendu '(' apres l'expression");
        }
        return;
    }else if (symbol==WRITE) {
        accepter(WRITE);
        if(symbol==PO){
            accepter(PO);
            if(symbol==ID){
                accepter(ID);
                if(symbol==PF){
                    accepter(PF);
                }else{
                    error("Attendu ')' apres l'expression");
                }
            }else{
                error("Attendu 'id' apres l'expression");
            }
        }else{
            error("Attendu '(' apres l'expression");
        }
        return;
    }else if (symbol==WRITELN) {
        accepter(WRITELN);
        if(symbol==PO){
            accepter(PO);
            if(symbol==ID){
                accepter(ID);
                if(symbol==PF){
                    accepter(PF);
                }else{
                    error("Attendu ')' apres l'expression");
                }
            }else{
                error("Attendu 'id' apres l'expression");
            }
        }else{
            error("Attendu '(' apres l'expression");
        }
        return;
    }
}

// analyse lexical
int isNumber(char character){
    return (((character >= '0') && (character <= '9')));
}
int isLetter(char character)
{
    return (((character >= 'a') && (character <= 'z')) || ((character >= 'A') && (character <= 'Z')));
}
int isLetterOrNumber(char character)
{
    return (isLetter(character) || isNumber(character));
}
void erreur()
{
    printf("\nCOMPILATION ERROR!\n\n");
    printf("LEXICAL ERROR!\n");
    printf("\n\n");
    exit(0);
}
char *table[TABLE_LEN] = {
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "program",
    "var", "begin", "end", "integer", "char", "if", "then", "else", "while", "do", "readln", "read", "writeln", "write","."
};
int analyseur_lexical(char *file){
    int etat=0;
    if(!feof(f)){
        char token[MAX_TOKEN_LEN]="0";
        while(1){
            char c;
            switch(etat){
                case 0:
                    strcpy(token, "\0");
                    if(feof(f)){
                        erreur();
                        exit(0);
                    }
                    c = fgetc(f);
                    strncat(token,&c,1);
                    if( (c==' ') || (c=='\t') || (c=='\n')){
                        break;
                    }
                    if (isLetter(c)){
                        etat = 1;
                        break;
                    }else if (isNumber(c)){
                        etat = 4;
                        break;
                    }else if (c==';'){
                        etat = 3;
                        break;
                    }else if (c==':'){
                        etat = 6;
                        break;
                    }else if (c=='<'){
                        etat = 9;
                        break;
                    }else if (c=='>'){
                        etat = 13;
                        break;
                    }else if (c=='='){
                        etat = 16;
                        break;
                    }else if(c=='|'){
                        etat = 17;
                        break;
                    }else if (c=='('){
                        etat = 20;
                        break;
                    }else if (c==')'){
                        etat = 24;
                        break;
                    }else if (c==','){
                        etat = 26;
                        break;
                    }else if(c=='.'){
                        return P;
                    }else if(c=='+'){
                        etat = 27;
                        break;
                    }else if(c=='-'){
                        etat = 28;
                        break;
                    }else if(c=='*'){
                        etat = 29;
                        break;
                    }else if(c=='/'){
                        etat = 30;
                        break;
                    }else if(c=='%'){
                        etat = 31;
                        break;
                    }else if(c=='.'){
                        etat=32;
                        break;
                    }else{
                        printf("%c",c);
                        erreur();
                        exit(0);
                    }
                case 1:
                    c = fgetc(f);
                     if(!((c==' ') || (c=='\t') || (c=='\n'))){
                        strncat(token,&c,1);
                     }
                    if(isLetterOrNumber(c)){
                        etat = 1;
                        break;
                    }else{
                        etat = 2;
                        break;
                    }
                case 2:{
                    int ok=0;
                    char g=token[strlen(token)- 1];
                    if((!isLetter(g) ) && (!isNumber(g))){
                        token[strlen(token)- 1]='\0';
                        fseek(f, -1,SEEK_CUR);
                    }
                    for(int i=24;i<TABLE_LEN;i++){
                        if(strcmp(table[i],token)==0){
                            symbol= i;
                            return i;
                            ok=1;
                            break;
                        }
                    }
                    if(ok==0){
                        return ID;
                    }}
                    etat=0;
                    break;
                case 3:
                    return PV;
                case 4:
                    c = fgetc(f);
                    strncat(token,&c,1);
                    if(isNumber(c)){
                        etat = 4;
                        break;
                    }else{
                        etat = 5;
                        break;
                    }
                case 5:
                    fseek(f, -1, SEEK_CUR);
                    return NB;
                case 6:
                    c = fgetc(f);
                    strncat(token,&c,1);
                    if(c == '='){
                        etat = 7;
                        break;
                    }else{
                        etat = 8;
                        break;
                    }
                case 7:
                    return AFF;
                case 8:
                    c = fgetc(f);
                    strncat(token,&c,1);
                    fseek(f, -1, SEEK_CUR);
                    return DP;
                case 9:
                    c = fgetc(f);
                    strncat(token,&c,1);
                    if(c == '='){
                        etat = 10;
                    }else if(c == '>'){
                        etat = 11;
                    }else{
                        etat = 12;
                    }
                    break;
                case 10:
                    return PPE;
                case 11:
                    return DIFF;
                case 12:
                    fseek(f, -1, SEEK_CUR);
                    return PPQ;
                case 13:
                    c = fgetc(f);
                    strncat(token,&c,1);
                    if(c == '='){
                        etat = 14;
                    }else{
                        etat = 15;
                    }
                    break;
                case 14:
                    return PGE;
                case 15:
                    return PGQ;
                case 16:
                    return EGA;
                case 17:
                    c = fgetc(f);
                    strncat(token,&c,1);
                    if(c == '|'){
                        etat = 18;
                    }else{
                        etat = 19;
                    }
                    break;
                case 18:
                    return OR;
                case 19:
                    erreur();
                case 20:
                    c = fgetc(f);
                    strncat(token,&c,1);
                    if(c == '*'){
                        etat = 21;
                    }else{
                        etat = 25;
                    }
                    break;
                case 21:
                    c = fgetc(f);
                    strncat(token,&c,1);
                    if(c == '*'){
                        etat = 22;
                    }else{
                        etat = 21;
                    }
                    break;
                case 22:
                    c = fgetc(f);
                    if(c == ')'){
                        etat = 23;
                    }else{
                        etat = 21;
                    }
                    break;
                case 23:
                    return CMT;
                case 24:
                    return PF;
                case 25:
                    fseek(f, -1,SEEK_CUR);
                    return PO;
                case 26:
                    return V;
                case 27:
                    return ADD;
                case 28:
                    return SUB;
                case 29:
                    return MUL;
                case 30:
                    return DIV;
                case 31:
                    return MOD;
                case 32:
                    return P;
            }
        }
    }
}
int main() {
    const char *file="textfichier permutation.txt";
    FILE *f=fopen(file,"r");

    analyseur_lexical(file);
    program();
    return 0;
}
// Karim lazghab et oussama bouhali
