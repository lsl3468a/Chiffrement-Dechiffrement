# SUJET4

https://github.com/lsl3468a/SUJET4.git

LASSERRE Ludivine et ALEXIS Mélina

Nous avons développé une application qui permet de chiffrer et déchiffrer un message en utilisant deux techniques (César et Vigenere).

Fonction qui permet de vider le buffer: 
void clearBuffer();

Fonction qui permet de vérifier si le texte saisi possède que des caractères alphanumériques. Renvoie faux si possède des caractères spéciaux et entraine un cas d'erreur :
bool verifier_alphanum(wchar_t *texte);

Fonction qui permet de retirer les accents au texte saisi :
void retirer_accents(wchar_t *texte);

Fonction qui permet de chiffrer un texte avec la méthode de César en utilisant une clé de chiffrement (entier):
void chiffrement_cesar(int decallage, wchar_t *texte);

Fonction qui permet de déchiffrer un texte avec la méthode de César en utilisant une clé de déchiffrement (entier):
void dechiffrement_cesar(int decallage, wchar_t *texte);

Fonction qui permet de chiffrer un texte avec la méthode de Vigenere en utilisant une clé de chiffrement (caractères):
void chiffrement_vigenere(wchar_t *cle, wchar_t *texte);

Fonction qui permet de chiffrer un texte avec la méthode de Vigenere en utilisant une clé de déchiffrement (caractères):
void dechiffrement_vigenere(wchar_t *cle, wchar_t *texte);

Fonction principale du programme qui permet de demander à l'utilisateur l'action qu'il veut réaliser (chiffrement/déchiffrement César/Vigenere) et réaliser les actions en fonction de ses choix. 
