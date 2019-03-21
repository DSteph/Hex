#include "IHM.h"
#include "Hex.h"
#include "Test.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void viderBuffer() {
	int c = 0;
	while (c != '\n') {
		c = getchar();
	}
}

int lire(char *chaine, int longueur) {
	char *positionEntree = NULL;

	if (fgets(chaine, longueur, stdin) != NULL) {
		positionEntree = strchr(chaine, '\n'); //on recherche le passage a la ligne
		if (positionEntree != NULL) { //si il existe
			*positionEntree = '\0';//on le remplace par \0
		}
		else {
			viderBuffer();
		}
		return 1;
	}
	else {
		viderBuffer();
		return 0;
	}
}

int lireInt() {
	char nbTxt[10] = { 0 }; 
	if (lire(nbTxt, 10)) {
		return strtol(nbTxt, NULL, 10); //Si lecture du txt ok on converti la chaine
										//en int et on la retourne
	}
	else {

		return 0;
	}
}

void afficherChaineCaractere(char *chaineAAfficher) {
	printf("%s", chaineAAfficher);
}

int defCoordoneeLigne(unsigned int tailleLigne) {

	afficherChaineCaractere("Entrez le numero de ligne souhaite :");

	unsigned int coordoneeLigne = lireInt();
	while (coordoneeLigne > tailleLigne || coordoneeLigne < 1) {
		printf("Choix errone , merci d'entrer une valeur de ligne entre 1 et %d\n", tailleLigne);
		coordoneeLigne = lireInt();
	}
	return coordoneeLigne;
}

int defCoordoneeColonne(unsigned int tailleLigne) {

	afficherChaineCaractere("Entrez le numero de colonne souhaite :");
	unsigned int coordoneeColonne = lireInt();
	if (coordoneeColonne > tailleLigne || coordoneeColonne < 1) {
		printf("Choix errone , merci d'entrer une valeur de colonne entre 1 et %d\n", tailleLigne);
		coordoneeColonne = lireInt();
	}
	return coordoneeColonne;
}

int defTailleLigne() {

	int tailleLigne = 0;

	afficherChaineCaractere("Veuillez entrer la largeur/longueur de la grille, une valeur comprise entre 3 et 50.\n");
	tailleLigne = lireInt();

	while (tailleLigne > 50 || tailleLigne < 3)
	{
		afficherChaineCaractere("Valeur erronee, merci d'entrer une valeur entre 3 et 50.\n");
		tailleLigne = lireInt();
	}

	return tailleLigne;

}

void afficherEcranTitre() {

	afficherChaineCaractere("\n");
	afficherChaineCaractere("\n");
	afficherChaineCaractere("		\\\\\\                 \\\\\\           \\\\\\=================           \\\\\\          ///   \n");
	afficherChaineCaractere("		 \\\\\\                 \\\\\\           \\\\\\                            \\\\\\        ///    \n");
	afficherChaineCaractere("		  \\\\\\                 \\\\\\           \\\\\\                            \\\\\\      ///     \n");
	afficherChaineCaractere("		   \\\\\\                 \\\\\\           \\\\\\                            \\\\\\    ///      \n");
	afficherChaineCaractere("		    \\\\\\                 \\\\\\           \\\\\\                            \\\\\\  ///       \n");
	afficherChaineCaractere("		     \\\\\\=================\\\\\\           \\\\\\=================           \\\\\\///        \n");
	afficherChaineCaractere("		      \\\\\\                 \\\\\\           \\\\\\                           ///\\\\\\        \n");
	afficherChaineCaractere("		       \\\\\\                 \\\\\\           \\\\\\                         ///  \\\\\\       \n");
	afficherChaineCaractere("		        \\\\\\                 \\\\\\           \\\\\\                       ///    \\\\\\      \n");
	afficherChaineCaractere("		         \\\\\\                 \\\\\\           \\\\\\                     ///      \\\\\\     \n");
	afficherChaineCaractere("		          \\\\\\                 \\\\\\           \\\\\\=================  ///        \\\\\\    \n");
	afficherChaineCaractere("\n");
	afficherChaineCaractere("\n");
}

void demanderARejouer(int *valeurRejouer) {

	afficherChaineCaractere("Voulez-vous rejouer ? tapez 1 pour rejouer ou tout autre caractere pour quitter.\n");
	*valeurRejouer = lireInt();
}

int reinitValeurVictoire() {

	return 0;
}

void afficherVainqueur(int valeurVictoire) {

	if (valeurVictoire == 1)
	afficherChaineCaractere("\n Le joueur B a gagne !\n");
	else if (valeurVictoire == 2)
	afficherChaineCaractere("\n Le joueur R a gagne !\n");

}

int choixPartieOuTest() {

	afficherChaineCaractere("Voulez-vous jouer ou lancer les tests ?");
	afficherChaineCaractere("\n Tapez 1 pour lancer les tests ou 2 pour jouer\n");

	unsigned int choix = lireInt();

	while (choix != 2 && choix != 1) {
		afficherChaineCaractere("Choix erronne, merci de taper 1 pour lancer les tests ou 2 pour jouer\n");
		choix = lireInt();
	}
	return choix;
}

void lancerPartieOuTest() {

	unsigned int lancerPartie = 0;

	while (lancerPartie == 0) {

		unsigned int choix = choixPartieOuTest();

		if (choix == 1) {
			tester();
			choix = 0;
		}
		else {
			lancerPartie = 1;
			lancerPartieHex();
		}
	}
}
