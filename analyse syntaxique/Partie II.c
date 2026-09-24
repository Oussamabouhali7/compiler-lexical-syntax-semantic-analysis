#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    printf("Entrez une chaine a analyser :\n");
    jeton_suivant();
    program();
    return 0;
}

//  Oussama Bouhali et Karim Lazghab
/*
exemple d'execution :
     program id ; var id : integer ; begin     read(id) ;    write(id) ; end .
     program id ; var id : integer ; begin     id := id ; end .
*/
