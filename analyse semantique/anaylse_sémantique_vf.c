#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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
void erreur_syntaxique(const char *message);
void accepter();
int rangerid();

typedef struct {
    char name[MAX_LEN]; // nom de variable
    int nb;  // si nombre , ce champs est remplit
    char contenu[MAX_LEN]; // si charactere , ce champs est remplit
    bool isnumber; // si variable est un nombre egal a 1 sinon null
}variable;

variable tab_variable[TABLE_LEN];
typedef struct {
    int ul;
    int att;
}unilex ;

unilex analyseur_lexical();

unilex symbol;
char* file;
FILE *f;
int *last=0;
int len=0;
int indice=0;


// analyse semantique

void accepter(int t){
    if( symbol.ul ==t){
        symbol=analyseur_lexical(file);
    }else{
        erreur_de_compilation();
    }
}



// void ajouter_type(int type, char* name_var) {
//   if (indice < 0 || indice >= len) {
//     printf("erreur: depassement de la limite du nombre de variables \n");
//     exit(0);
//   }

//   for(int i=0; i<indice; i++){
//     if (strcmp(tab_variable[i].name,name_var)==0){
//         printf("erreur de redéclaration");
//         exit(0);
//     }
//   }
//   tab_variable[indice].isnumber=(type==INTEGER);
//   tab_variable[indice].name=name_var;
//   indice++;

// }

// char* chercher_type(int indice_tab) {
//   if (indice_tab < 0 || indice_tab >= len){
//     printf("erreur: %d non declaree \n",indice_tab);
//     exit (0);
//   }
//   return &tab_variable[indice_tab];
// }


// analyse syntaxique
void erreur_syntaxique(const char *message) {
    printf("Erreur de syntaxe : %s\n", message);
    exit(1);
}
bool test_semantique(int x,int y){
    if(x==y){
        return true;
    }else{
        erreur_de_compilation();
        exit(0);
    }
}
void program() {
    if (symbol.ul==PROGRAM){
        accepter(PROGRAM);
        if (symbol.ul==ID) {
            accepter(ID);
            if (symbol.ul==PV) {
                accepter(PV);
                dcl();
                inst_composee();
                    if (symbol.ul==P) {
                    printf("Analyse reussie!\n");
                } else {
                    erreur_syntaxique("Attendu '.'");
                }
            } else {
                erreur_syntaxique("Attendu ';' apres id");
            }
        } else {
            erreur_syntaxique("Attendu un id apres program");
        }
    } else {
        erreur_syntaxique("Attendu 'program'");
    }
}

void dcl() {
    dcl_prime();
}
int variable_types_len=0;
int variable_types[MAX_LEN];

void dcl_prime(){
    if (VAR==symbol.ul) {
        variable_types_len=0;
        accepter(VAR);
        liste_id();
        if (symbol.ul==DP) {
            accepter(DP);
            type();
            if (symbol.ul== PV) {
                accepter(PV);
                dcl_prime();
            } else {
                erreur_syntaxique("Attendu ';'");
            }
        } else {
            erreur_syntaxique("Attendu ':'");
        }
    } else {
        return; // epsilon
    }
}

void liste_id() {
    if (symbol.ul ==ID) {
        variable_types[variable_types_len]=symbol.att;
        variable_types_len++;
        accepter(ID);
        liste_id_prime();
    } else {
        erreur_syntaxique("Attendu 'id'");
    }
}

void liste_id_prime() {
    if (symbol.ul==V) {
        accepter(V);
        if (symbol.ul==ID) {
            variable_types[variable_types_len]=symbol.att;
            variable_types_len++;
            accepter(ID);
            liste_id_prime();
        } else {
            erreur_syntaxique("Attendu 'id' apres ','");
        }
    }
}

void liste_inst() {
    i();
    liste_inst_prime();
}

void liste_inst_prime() {
    if (symbol.ul==PV) {
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
    if (symbol.ul==ADD){
        accepter(ADD);
        terme();
        exp_simple_prime();
    }else if (symbol.ul==SUB){
        accepter(SUB);
        terme();
        exp_simple_prime();
    }else if (symbol.ul==OR){
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
    if (symbol.ul==MUL){
        accepter(MUL);
        facteur();
        terme_prime();
    }else if (symbol.ul==DIV){
        accepter(DIV);
        facteur();
        terme_prime();
    }else if (symbol.ul==MOD){
        accepter(MOD);
        facteur();
        terme_prime();
    }else if (symbol.ul==AND){
        accepter(AND);
        facteur();
        terme_prime();
    }
}

void facteur() {
    if (symbol.ul==ID) {
        accepter(ID);
        return;
    } else if (symbol.ul==NB) {
        accepter(NB);
        return;
    } else if (symbol.ul==PO) {
        accepter(PO);
        exp_simple();
        if (symbol.ul==PF) {
            accepter(PF);
            return;
        } else {
            erreur_syntaxique("Attendu ')'");
        }
    } else {
        erreur_syntaxique("Attendu id, nb, ou (exp)");
    }
}


void type() {
    if (symbol.ul==INTEGER) {
        accepter(INTEGER);
        for(int i=0;i<variable_types_len;i++){
            tab_variable[variable_types[i]].isnumber=1;
        }
        return;
    } else if(symbol.ul==CHR){
        accepter(CHR);
        return;
    }else{
        erreur_syntaxique("Attendu 'integer' ou 'char'");
    }
}

void inst_composee() {
    if (BEGIN==symbol.ul) {
        accepter(BEGIN);
        inst();
        if (symbol.ul==END) {
            accepter(END);
            return;
        } else {
            erreur_syntaxique("Attendu 'end'");
        }
    } else {
        erreur_syntaxique("Attendu 'begin'");
    }
}

void inst() {
    liste_inst();
}

void Exp() {
    exp_simple();
    if (symbol.ul==PGQ) {
        accepter(PGQ);
        exp_simple();
    }else if (symbol.ul==PGE) {
        accepter(PGE);
        exp_simple();
    }else if (symbol.ul==PPQ) {
        accepter(PPQ);
        exp_simple();
    }else if (symbol.ul==PPE) {
        accepter(PPE);
        exp_simple();
    }else if (symbol.ul==EGA) {
        accepter(EGA);
        exp_simple();
    }else if (symbol.ul==DIFF) {
        accepter(DIFF);
        exp_simple();
    }
}


void i() {
    if (symbol.ul==ID) {
        accepter(ID);
        if (symbol.ul==AFF) {
            accepter(AFF);
            exp_simple();
        } else {
            erreur_syntaxique("Attendu ':=' apres l'identifiant");
        }
    } else if (symbol.ul==IF) {
        accepter(IF);
        Exp();
        if (symbol.ul==THEN) {
            accepter(THEN);
            i();
            if (symbol.ul==ELSE) {
                accepter(ELSE);
                i();
            } else {
                erreur_syntaxique("Attendu 'else'");
            }
        } else {
            erreur_syntaxique("Attendu 'then' apres l'expression");
        }
    } else if (symbol.ul==WHILE) {
        accepter(WHILE);
        Exp();
        if (symbol.ul==DO) {
            accepter(DO);
            i();
        } else {
            erreur_syntaxique("Attendu 'do' apres l'expression");
        }
    }else if (symbol.ul==READ) {
        accepter(READ);
        if(symbol.ul==PO){
            accepter(PO);
            if(symbol.ul==ID){
                accepter(ID);
                if(symbol.ul==PF){
                    accepter(PF);
                }else{
                    erreur_syntaxique("Attendu ')' apres l'expression");
                }
            }else{
                erreur_syntaxique("Attendu 'id' apres l'expression");
            }
        }else{
            erreur_syntaxique("Attendu '(' apres l'expression");
        }
        return;
    }else if (symbol.ul==READLN) {
        accepter(READLN);
        if(symbol.ul==PO){
            accepter(PO);
            if(symbol.ul==ID){
                accepter(ID);
                if(symbol.ul==PF){
                    accepter(PF);
                }else{
                    erreur_syntaxique("Attendu ')' apres l'expression");
                }
            }else{
                erreur_syntaxique("Attendu 'id' apres l'expression");
            }
        }else{
            erreur_syntaxique("Attendu '(' apres l'expression");
        }
        return;
    }else if (symbol.ul==WRITE) {
        accepter(WRITE);
        if(symbol.ul==PO){
            accepter(PO);
            if(symbol.ul==ID){
                accepter(ID);
                if(symbol.ul==PF){
                    accepter(PF);
                }else{
                    erreur_syntaxique("Attendu ')' apres l'expression");
                }
            }else{
                erreur_syntaxique("Attendu 'id' apres l'expression");
            }
        }else{
            erreur_syntaxique("Attendu '(' apres l'expression");
        }
        return;
    }else if (symbol.ul==WRITELN) {
        accepter(WRITELN);
        if(symbol.ul==PO){
            accepter(PO);
            if(symbol.ul==ID){
                accepter(ID);
                if(symbol.ul==PF){
                    accepter(PF);
                }else{
                    erreur_syntaxique("Attendu ')' apres l'expression");
                }
            }else{
                erreur_syntaxique("Attendu 'id' apres l'expression");
            }
        }else{
            erreur_syntaxique("Attendu '(' apres l'expression");
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
void erreur_de_compilation(){
    printf("\nCOMPILATION ERROR!\n\n");
    printf("LEXICAL ERROR!\n");
    printf("\n\n");
    exit(0);
}
char *table[TABLE_LEN] = {
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "program",
    "var", "begin", "end", "integer", "char", "if", "then", "else", "while", "do", "readln", "read", "writeln", "write","."
};
unilex analyseur_lexical(char *file){
    int etat=0;
    if(!feof(f)){
        char token[MAX_TOKEN_LEN]="0";
        unilex unite_courant;
        while(1){
            char c;
            switch(etat){
                case 0:
                    strcpy(token, "\0");
                    if(feof(f)){
                        erreur_de_compilation();
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
                        unite_courant.ul=P;
                        return unite_courant;
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
                        erreur_de_compilation();
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
                            unite_courant.ul=i;
                            return unite_courant;
                            ok=1;
                            break;
                        }
                    }
                    if(ok==0){// ajout d'un variable
                        unite_courant.ul=ID;
                        for(int i=0;i<=len;i++){
                            if(strcmp(tab_variable[i].name,token)==0){
                                unite_courant.att=i;
                                return unite_courant;
                            }
                        }
                        unite_courant.att=len;
                        strcpy(tab_variable[len].name,token);
                        len++;
                        return unite_courant;

                    }
                    etat=0;
                    break;
                }
                case 3:
                    unite_courant.ul=PV;
                    return unite_courant;
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
                    unite_courant.ul=NB;
                    int tmp=0;
                    int i=0;
                    while(token[i]!='\0'){
                        tmp=tmp*10+(token[i]-'0');
                        i++;
                    }
                    unite_courant.att=tmp;
                    return unite_courant;
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
                    unite_courant.ul=AFF;
                    return unite_courant;
                case 8:
                    c = fgetc(f);
                    strncat(token,&c,1);
                    fseek(f, -1, SEEK_CUR);
                    unite_courant.ul=DP;
                    return unite_courant;
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
                    unite_courant.ul=PPE;
                    return unite_courant;
                case 11:
                    unite_courant.ul=DIFF;
                    return unite_courant;
                case 12:
                    fseek(f, -1, SEEK_CUR);
                    unite_courant.ul=PPQ;
                    return unite_courant;
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
                    unite_courant.ul=PGE;
                    return unite_courant;
                case 15:
                    unite_courant.ul=PGQ;
                    return unite_courant;
                case 16:
                    unite_courant.ul=EGA;
                    return unite_courant;
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
                    unite_courant.ul=OR;
                    return unite_courant;
                case 19:
                    erreur_de_compilation();
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
                    unite_courant.ul=CMT;
                    return unite_courant;
                case 24:
                    unite_courant.ul=PF;
                    return unite_courant;
                case 25:
                    fseek(f, -1,SEEK_CUR);
                    unite_courant.ul=PO;
                    return unite_courant;
                case 26:
                    unite_courant.ul=V;
                    return unite_courant;
                case 27:
                    unite_courant.ul=ADD;
                    return unite_courant;
                case 28:
                    unite_courant.ul=SUB;
                    return unite_courant;
                case 29:
                    unite_courant.ul=MUL;
                    return unite_courant;
                case 30:
                    unite_courant.ul=DIV;
                    return unite_courant;
                case 31:
                    unite_courant.ul=MOD;
                    return unite_courant;
                case 32:
                    unite_courant.ul=P;
                    return unite_courant;
            }
        }
    }
}

int main() {
    file="textfichier permutation.txt";
    f=fopen(file,"r");
    symbol=analyseur_lexical(file);
    program();
    //fine
    return 0;
}
// Oussama Bouhali et Karim lazghab
