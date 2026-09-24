#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TOKENS 100

// Structure pour le traducteur
typedef struct {
    char *tokens[MAX_TOKENS];
    int index;
    char *resultat[MAX_TOKENS];
    int resultat_index;
} Traducteur;

// Fonction pour obtenir le token courant
char* token_courant(Traducteur *traducteur) {
    if (traducteur->index < MAX_TOKENS && traducteur->tokens[traducteur->index] != NULL) {
        return traducteur->tokens[traducteur->index];
    }
    return NULL;
}

// Fonction pour avancer d'un token
void avancer(Traducteur *traducteur) {
    traducteur->index++;
}

// Fonction pour analyser la liste de tokens
void analyser(Traducteur *traducteur) {
    traducteur->index = 0;
    traducteur->resultat_index = 0;
    operation(traducteur);
}

// Fonction pour traiter une opération d'affectation
void operation(Traducteur *traducteur) {
    if (strcmp(token_courant(traducteur), "id") == 0) {
        traducteur->resultat[traducteur->resultat_index++] = "Valeurg id";  // Valeur de l'identifiant
        avancer(traducteur);
        traducteur->resultat[traducteur->resultat_index++] = "empiler nb";  // Empiler le nombre
        if (strcmp(token_courant(traducteur), ":=") == 0) {
            avancer(traducteur);
            exp_simple(traducteur);  // Traiter l'expression simple
            traducteur->resultat[traducteur->resultat_index++] = ":=";  // Ajouter l'affectation
        }
    }
}

// Fonction pour traiter une expression simple
void exp_simple(Traducteur *traducteur) {
    terme(traducteur);
    exp_simple_prime(traducteur);
}

// Fonction pour traiter une partie de l'expression simple (opadd)
void exp_simple_prime(Traducteur *traducteur) {
    if (strcmp(token_courant(traducteur), "opadd") == 0) {
        avancer(traducteur);
        traducteur->resultat[traducteur->resultat_index++] = "opadd";  // Ajouter l'opération addition
        terme(traducteur);  // Traiter le terme suivant l'opération
    }
}

// Fonction pour traiter un terme (facteur et terme_prime)
void terme(Traducteur *traducteur) {
    facteur(traducteur);
    terme_prime(traducteur);
}

// Fonction pour traiter un terme (opmul)
void terme_prime(Traducteur *traducteur) {
    if (strcmp(token_courant(traducteur), "opmul") == 0) {
        avancer(traducteur);
        facteur(traducteur);
        terme_prime(traducteur);
    }
}

// Fonction pour traiter un facteur (id, nb ou expression entre parenthèses)
void facteur(Traducteur *traducteur) {
    if (strcmp(token_courant(traducteur), "id") == 0) {
        traducteur->resultat[traducteur->resultat_index++] = "Valeurd id";  // Valeur de l'identifiant
        avancer(traducteur);
    } else if (strcmp(token_courant(traducteur), "nb") == 0) {
        traducteur->resultat[traducteur->resultat_index++] = "Valeurd nb";  // Valeur du nombre
        avancer(traducteur);
    } else if (strcmp(token_courant(traducteur), "(") == 0) {
        avancer(traducteur);
        exp_simple(traducteur);
        if (strcmp(token_courant(traducteur), ")") == 0) {
            avancer(traducteur);
        } else {
            printf("Erreur de syntaxe : ')' attendu après l'expression\n");
            exit(1);
        }
    } else {
        printf("Erreur de syntaxe : Facteur invalide\n");
        exit(1);
    }
}

// Fonction principale pour tester le traducteur
int main() {
    Traducteur traducteur;

    // Exemple d'entrée
    traducteur.tokens[0] = "id";
    traducteur.tokens[1] = ":=";
    traducteur.tokens[2] = "nb";
    traducteur.tokens[3] = "opadd";
    traducteur.tokens[4] = "id";
    traducteur.tokens[5] = NULL;  // Fin des tokens

    analyser(&traducteur);

    // Affichage des résultats
    for (int i = 0; i < traducteur.resultat_index; i++) {
        printf("%s\n", traducteur.resultat[i]);
    }

    return 0;
}

