class Traducteur:
    def __init__(self):
        self.tokens = []
        self.index = 0
        self.resultat = []

    def token_courant(self):
        if self.index < len(self.tokens):
            return self.tokens[self.index]
        return None

    def avancer(self):
        self.index += 1

    def analyser(self, tokens):
        self.tokens = tokens
        self.index = 0
        self.resultat = []
        self.operation()
        return self.resultat

    # Traiter une opération d'affectation simple ou des expressions de base
    def operation(self):
        if self.token_courant() == "id":
            self.resultat.append("Valeurg id")  # Valeur de l'identifiant
            self.avancer()
            if self.token_courant() == ":=":
                self.avancer()
                self.resultat.append("empiler nb")  # Empiler le nombre
                self.exp_simple()  # Traiter l'expression simple
                self.resultat.append("opadd")  # Ajouter l'opération addition
                self.resultat.append(":=")  # Ajouter l'affectation

    def exp_simple(self):
        self.terme()
        self.exp_simple_prime()

    def exp_simple_prime(self):
        if self.token_courant() == "opadd":
            self.avancer()
ù # Ajouter l'opération addition
            self.terme()  # Traiter le terme suivant l'opération
            self.resultat.append("opadd")

    def terme(self):
        self.facteur()
        self.terme_prime()

    def terme_prime(self):
        if self.token_courant() == "opmul":
            self.avancer()
            self.facteur()
            self.terme_prime()

    def facteur(self):
        if self.token_courant() == "id":
            self.resultat.append("Valeurd id")  # Valeur de l'identifiant
            self.avancer()
        elif self.token_courant() == "nb":

            self.avancer()
        elif self.token_courant() == "(":
            self.avancer()
            self.exp_simple()
            if self.token_courant() == ")":
                self.avancer()
            else:
                raise SyntaxError("')' attendu après l'expression")
        else:
            raise SyntaxError("Facteur invalide")


# Exemple d'entrée
tokens = ["id", ":=", "nb", "opadd", "id", "opadd","id"]
traducteur = Traducteur()
resultat = traducteur.analyser(tokens)

# Affichage des résultats
print("\n".join(resultat))
