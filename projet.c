#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <stdbool.h>

void clearBuffer(){
    char c = getchar();
    while('\n' != c){
        c = getchar();
    }
}

bool verifier_alphanum(wchar_t *texte)
{
	int i;
	i=0;
	bool etat;
	etat = true;
	for(i=0; i<(wcslen(texte)-1);i++){
		if(!iswalnum(texte[i])){
			etat = false;
		}
	}
	return etat;
}

void retirer_accents(wchar_t *texte)
{
	wchar_t accents[]=L"àâäÂÄèéêëÊËîïÏÎôöÖÔùûüÛÜŷÿŶŸç";
	wchar_t sans_accents[]=L"aaaAAeeeeEEiiIIooOOuuuUUyyYYc";
	int i;
	for(i=0; i<(wcslen(texte)-1);i++)
	{
		int j;
		for(j=0; j<(wcslen(accents)-1); j++){
			if(texte[i]==accents[j]){
				texte[i]=sans_accents[j];
			}
		}
	}
}

void chiffrement_cesar (int decallage, wchar_t *texte)
{
	int i;
	for(i=0; i<wcslen(texte); i++)
	{
		if ('a' <= texte[i] && texte[i] <= 'z'){
			texte[i] = 'a' + ((texte[i] - 'a' ) + decallage)%26;
		}
		if ('A' <= texte[i] && texte[i] <= 'Z'){
			texte[i] = 'A' + ((texte[i] - 'A') + decallage ) %26;
		}
		if ('0' <= texte[i] && texte[i]<= '9'){
			texte[i] = '0' + ((texte[i] - '0') + decallage ) %10;
		}
	}
}

void dechiffrement_cesar (int decallage, wchar_t *texte)
{
	int i;
	for (i=0; i<wcslen(texte); i++)
	{
		if ('a'<= texte[i] && texte[i] <= 'z')
		{
			if(((texte[i]-'a') - decallage)<0){
				texte[i]= 'a' + (((texte[i] - 'a') - decallage)+26)%26;
			} else {
				texte[i] = 'a' + ((texte[i] - 'a') -  decallage ) %26;
			}
		} else if ('A' <= texte[i] && texte[i] <= 'Z')
		{
			if(((texte[i] - 'A') - decallage) <0){
				texte[i]= 'A' + (((texte[i] -'A') - decallage)+26)%26;
			}else{
				texte[i] = 'A' + ((texte[i] - 'A') - decallage) %26;
			}
        }
        if ('0' <= texte[i] && texte[i] <= '9')
		{
			if(((texte[i]-'0') - decallage)<0){
				texte[i]='0' + (((texte[i] - '0')- decallage) +10) %10;
			} else {
				texte[i] = '0'+((texte[i] - '0') - decallage) %10;
			}
		}
	}
}

void chiffrement_vigenere(wchar_t *cle, wchar_t *texte)
{
    int longCle = wcslen(cle);
    int i;
    for(i=0;texte[i] != '\0'; i++){
        if('a'<= texte[i] && texte[i] <= 'z'){
            int rang = (texte[i] + cle[i%longCle] - 2 * 'a') %26;
            texte[i]='a'+ rang;
        }
        else if('A'<= texte[i] && texte[i] <= 'Z'){
            int rang = (texte[i] + cle[i%longCle] - 'a' - 'A') %26;
            texte[i]='A'+ rang;
        }
    }
}

void dechiffrement_vigenere(wchar_t *cle, wchar_t *texte)
{
    int i;
    int longCle = wcslen(cle);
    wchar_t cletemporaire[longCle + 1];
    for(i=0; cle[i] !=0; i++){
        int rang = (26 - (cle[i]- 'a'))%26;
        cletemporaire[i]= rang + 'a';
    }
    chiffrement_vigenere(cletemporaire,texte);
}

int main()
{
	struct lconv *loc;
	setlocale(LC_ALL,"");
	loc = localeconv();
	int choix;
    int choix1;
    int choix2;
    int cleC=0;
    FILE*f = NULL;
	wchar_t cleV[100]={0};
	wchar_t Test[100]=L"";
	wprintf(L"Pour chiffrer un message tapez 1, pour déchiffrer un message tapez 2\n");
	wscanf(L"%d",&choix1);
	clearBuffer();
	wprintf(L"Pour utiliser César tapez 3, pour utiliser Vigenere tapez 4\n");
	wscanf(L"%d",&choix2);
	clearBuffer();
	choix = choix1 * choix2;
	wprintf(L"Quel est votre texte ?\n");
	fgetws(Test, 100, stdin);

	if (!verifier_alphanum(Test)){
		wprintf(L"Erreur, le texte comporte des caractères spéciaux ! Veuillez entrer à nouveau\n");
	} else {
	    retirer_accents(Test);
	    switch(choix)
	    {
        case 3:
            wprintf(L"Vous avez choisi le chiffrement de César\n");
            wprintf(L"Quelle est la clé de chiffrement ?\n");
            wscanf(L"%d",&cleC);
            chiffrement_cesar(cleC,Test);
            break;
        case 6:
            wprintf(L"Vous avez choisi le déchiffrement de César\n");
            wprintf(L"Quelle est la clé de chiffrement ?\n");
            wscanf(L"%d",&cleC);
            dechiffrement_cesar(cleC,Test);
            break;
        case 4:
            wprintf(L"Vous avez choisi le chiffrement de Vigenere\n");
            wprintf(L"Quelle est la clé de chiffrement ?\n");
            fgetws(cleV, 100, stdin);
            chiffrement_vigenere(cleV,Test);
            break;
        case 8:
            wprintf(L"Vous avez choisi le déchiffrement de Vigenere\n");
            wprintf(L"Quelle est la clé de chiffrement ?\n");
            fgetws(cleV, 100, stdin);
            dechiffrement_vigenere(cleV,Test);
	    }

        //f = open("chiffrage.txt","w");
        //fprintf(f,"%ls", fgetws(Test,100,f));
        //fclose(f);
        wprintf(L"Votre texte : %ls\n\n", Test);
		return 0;
	}
}
