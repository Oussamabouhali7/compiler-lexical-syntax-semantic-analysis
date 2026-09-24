#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//analyse lexicale partie I
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

#define MAX_TOKEN_LEN 80
#define MAX_OUTPUT_LEX_LEN 500
#define TABLE_LEN 39
char *table[TABLE_LEN] = {
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "program",
    "var", "begin", "end.", "integer", "char", "if", "then", "else", "while", "do", "readln", "read", "writeln", "write"
};

void build(){

}
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

char  analyseur_lexical(){
    int etat=0;
    char *file="fichier.txt";
    FILE *f=fopen(file,"r");
    char output_analyseur_lexical[MAX_OUTPUT_LEX_LEN]="\0";
    if(!feof(f)){
        char token[MAX_TOKEN_LEN]="0";
        while(1){
            char c;
            switch(etat){
                case 0:
                    strcpy(token, "\0");
                    if(feof(f)){
                        return "-1";
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
                    }else{
                        puts(output_analyseur_lexical);
                        return output_analyseur_lexical;
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
                case 2:
                    int ok=0;
                    char g=token[strlen(token)- 1];
                    if((!isLetter(g) ) && (!isNumber(g))){
                        token[strlen(token)- 1]='\0';
                    }
                    if(c=='.'){
                        //
                    }
                    for(int i=24;i<TABLE_LEN;i++){
                        if(strcmp(table[i],token)==0){
                            strncat(output_analyseur_lexical ,table[i],MAX_OUTPUT_LEX_LEN - strlen(output_analyseur_lexical) - 1);
                            strncat(output_analyseur_lexical ," ",MAX_OUTPUT_LEX_LEN/2);
                            ok=1;
                            break;
                        }
                    }
                    if(ok==0){
                        fseek(f, -1,SEEK_CUR);
                        strncat(output_analyseur_lexical ,"id ",MAX_OUTPUT_LEX_LEN/2);
                    }
                    etat=0;
                    break;
                case 3:
                    strncat(output_analyseur_lexical ,"; ",MAX_OUTPUT_LEX_LEN/2);
                    etat=0;
                    break;
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
                    strncat(output_analyseur_lexical ,"nb ",MAX_OUTPUT_LEX_LEN/2);
                    etat =0;
                    break;
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
                    strncat(output_analyseur_lexical ,":= ",MAX_OUTPUT_LEX_LEN/2);
                    etat =0;
                    break;
                case 8:
                    c = fgetc(f);
                    strncat(token,&c,1);
                    fseek(f, -1, SEEK_CUR);
                    strncat(output_analyseur_lexical ,": ",MAX_OUTPUT_LEX_LEN/2);
                    etat =0;
                    break;
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
                    strncat(output_analyseur_lexical ,"<= ",MAX_OUTPUT_LEX_LEN/2);
                    etat =0;
                    break;
                case 11:
                    strncat(output_analyseur_lexical ,"<> ",MAX_OUTPUT_LEX_LEN/2);
                    etat =0;
                    break;
                case 12:
                    fseek(f, -1, SEEK_CUR);
                    strncat(output_analyseur_lexical ,"< ",MAX_OUTPUT_LEX_LEN/2);
                    etat =0;
                    break;
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
                    strncat(output_analyseur_lexical ,">= ",MAX_OUTPUT_LEX_LEN/2);
                    etat =0;
                    break;
                case 15:
                    strncat(output_analyseur_lexical ,"> ",MAX_OUTPUT_LEX_LEN/2);
                    etat =0;
                    break;
                case 16:
                    strncat(output_analyseur_lexical ,"= ",MAX_OUTPUT_LEX_LEN/2);
                    etat =0;
                    break;
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
                    strncat(output_analyseur_lexical ,"|| ",MAX_OUTPUT_LEX_LEN/2);
                    etat =0;
                    break;
                case 19:
                    erreur();
                case 20:
                    c = fgetc(f);
                    strncat(token,&c,1);
                    if(c == '*'){
                        etat = 21;
                    }else{
                        erreur();
                        exit(0);
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
                    strncat(output_analyseur_lexical ,"(* ",MAX_OUTPUT_LEX_LEN/2);
                    strncat(output_analyseur_lexical ,token,sizeof(token)/2);
                    strncat(output_analyseur_lexical ,"*) ",MAX_OUTPUT_LEX_LEN/2);
                    etat =0;
                    break;
                case 24:
                    strncat(output_analyseur_lexical ,") ",MAX_OUTPUT_LEX_LEN/2);
                    etat =0;
                    break;
                case 25:
                    fseek(f, -1,SEEK_CUR);
                    strncat(output_analyseur_lexical ,"( ",MAX_OUTPUT_LEX_LEN/2);
                    etat =0;
                    break;
                case 26:
                    strncat(output_analyseur_lexical ,", ",MAX_OUTPUT_LEX_LEN/2);
                    etat = 0;
                    break;
            }
        }
    }
}


//analyse syntaxique partie II
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
void exp();
void s();
void i();
void error(const char *message);

char jeton[MAX_LEN];
int pos = 0;

void jeton_suivant() {
    while (1) {
        if (scanf("%s", jeton) != 1) {
            strcpy(jeton, "EOF");
            return;
        }
        if (strcmp(jeton, "") != 0) {
            break;
        }
    }
}
int accepter(const char *s) {
    if (strcmp(jeton, s) == 0) {
        jeton_suivant();
        return 1;
    }
    return 0;
}

void error(const char *message) {
    printf("Erreur de syntaxe : %s\n", message);
    exit(1);
}

void program() {
    if (accepter("program")) {
        if (accepter("id")) {
            if (accepter(";")) {
                dcl();
                inst_composee();
                    if (strcmp(jeton, ".") == 0) {
                    printf("Analyse syntaxique reussie!\n");
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
    if (accepter("var")) {
        liste_id();
        if (accepter(":")) {
            type();
            if (accepter(";")) {
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
    if (accepter("id")) {
        liste_id_prime();
    } else {
        error("Attendu 'id'");
    }
}

void liste_id_prime() {
    if (accepter(",")) {
        if (accepter("id")) {
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
    if (accepter(";")) {
        i();
        liste_inst_prime();
    }
}
void exp_simple() {
    terme();
    exp_simple_prime();
}

void exp_simple_prime() {
    if (accepter("opadd")) {
        terme();
        exp_simple_prime();
    }
}

void terme() {
    facteur();
    terme_prime();
}

void terme_prime() {
    if (accepter("opmul")) {
        facteur();
        terme_prime();
    }
}

void facteur() {
    if (accepter("id")) {
        return;
    } else if (accepter("nb")) {
        return;
    } else if (accepter("(")) {
        exp_simple();
        if (accepter(")")) {
            return;
        } else {
            error("Attendu ')'");
        }
    } else {
        error("Attendu id, nb, ou (exp)");
    }
}

void type() {
    if (accepter("integer") || accepter("char")) {
        return;
    } else {
        error("Attendu 'integer' ou 'char'");
    }
}

void inst_composee() {
    if (accepter("begin")) {
        inst();
        if (accepter("end")) {
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

void exp() {
    exp_simple();
    if (accepter("oprel")) {
        exp_simple();
    }
}


void i() {
    if (accepter("id")) {
        if (accepter(":=")) {
            exp_simple();
        } else {
            error("Attendu ':=' apres l'identifiant");
        }
    } else if (accepter("if")) {
        exp();
        if (accepter("then")) {
            i();
            if (accepter("else")) {
                i();
            } else {
                error("Attendu 'else'");
            }
        } else {
            error("Attendu 'then' apres l'expression");
        }
    } else if (accepter("while")) {
        exp();
        if (accepter("do")) {
            i();
        } else {
            error("Attendu 'do' apres l'expression");
        }
    }
    else if (accepter("read(id)") || accepter("readln(id)") ||
               accepter("write(id)") || accepter("writeln(id)")) {
        return;}


}

int main() {
    char reponse = analyseur_lexical();
    puts(reponse);
    jeton_suivant();
    program();
    return 0;
}
// Karim lazghab et oussama bouhali
