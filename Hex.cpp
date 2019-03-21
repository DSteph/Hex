#include "Hex.h"
#include "Joueur.h"
#include "IHM.h"
#include <stdlib.h>
#include <stdio.h>





void lancerPartieHex() {

	afficherEcranTitre();

	int valeurVictoire = 0, tailleLigne = 0, valeurRejouer = 1;
	while (valeurRejouer == 1) {
		Joueur j = creerJoueur();
		tailleLigne = defTailleLigne();
		Hex grilleHex = creerPlateau(tailleLigne);

		while (valeurVictoire == 0) {
			afficherTableau(&grilleHex, tailleLigne);
			defCoordoneePion(&grilleHex, tailleLigne, &j);
			valeurVictoire = verificationVictoire(&grilleHex, tailleLigne, valeurVictoire, &j);
			remettreLettreJoueurTableau(&grilleHex, tailleLigne, &j);
			changerJoueur(&j);
		}
		afficherTableau(&grilleHex, tailleLigne);
		afficherVainqueur(valeurVictoire);
		libererPlateau(&grilleHex);
		valeurVictoire = reinitValeurVictoire();
		demanderARejouer(&valeurRejouer);
	}
}

Hex creerPlateau(int tailleLigne) {

	Hex creerGrille;

	creerGrille.tableau = (char*)malloc((tailleLigne*tailleLigne) * sizeof(char));
	initCaseTableauEnPoint(&creerGrille, tailleLigne);

	return creerGrille;
}

void libererPlateau(Hex *grilleHex) {

	free(grilleHex->tableau);
}

void initCaseTableauEnPoint(Hex *creerGrille, int tailleLigne) {

	for (int i = 0; i < (tailleLigne*(tailleLigne)); ++i) 
		creerGrille->tableau[i] = '.'; // On rend toute les cases du tableau libres
}

void defCoordoneePion(Hex *grilleHex, unsigned int tailleLigne, Joueur *j) {

	printf("Joueur %c, c'est votre tour !\n", j->lettreJoueur);
	int ligne = defCoordoneeLigne(tailleLigne);
	int colonne = defCoordoneeColonne(tailleLigne);

	while (!placerUnPion(grilleHex, tailleLigne, ligne, colonne, j)) {
		afficherChaineCaractere("Choix erronne, merci de recommencer.\n");
		ligne = defCoordoneeLigne(tailleLigne);
		colonne = defCoordoneeColonne(tailleLigne);
	}
}

bool placerUnPion(Hex *grilleHex, unsigned int tailleLigne,unsigned int ligne, unsigned colonne, Joueur *j) {


	if (grilleHex->tableau[(ligne * tailleLigne) - (tailleLigne - (colonne - 1))] != '.') { // Si la case n'est pas libre
		return false; // Le coup est invalide
	}

	else {
		grilleHex->tableau[(ligne * tailleLigne) - (tailleLigne - (colonne - 1))] = j->lettreJoueur;
		return true;
	}
}

int verificationVictoire(Hex *grilleHex, int tailleLigne, int valeurVictoire, Joueur *j) {


	if (j->lettreJoueur == 'B') { //On lance la verification en fonction du Joueur dont c'est le tour
		verifPremiereLigneJoueurB(grilleHex, tailleLigne, j);
		return valeurVictoire = declarerVictoireJoueurB(grilleHex, tailleLigne, j);
	}
	else {
		verifPremiereColonneJoueurR(grilleHex, tailleLigne, j);
		return valeurVictoire = declarerVictoireJoueurR(grilleHex, tailleLigne, j);
	}
}

void verifPremiereLigneJoueurB(Hex *grilleHex, unsigned int tailleLigne, Joueur *j) {

	unsigned int b = 0;

	for (b = 0; b < tailleLigne; ++b) {
		if (grilleHex->tableau[b] == j->lettreJoueur) {// On verifie que le joueur B a au moins un pion sur la ligne du haut pour démarrer une verification de victoire
			markerCase1(grilleHex, b);
			verifCase1(grilleHex, b, tailleLigne, j);
		}
	}
	for (b = 0; b < tailleLigne; ++b) {
		if (grilleHex->tableau[b] == 'W') { // On lance la deuxieme verification en regardant si la premiere ligne contient bien un case marquée W
			markerCase2(grilleHex, b);
			verifCase2(grilleHex, b, tailleLigne, j);
		}
	}
}

void verifPremiereColonneJoueurR(Hex *grilleHex, unsigned int tailleLigne, Joueur *j) {

	unsigned int b = 0; 

	for (b = 0; b <= (tailleLigne - 1)*tailleLigne; b = (b + tailleLigne)) {
		if (grilleHex->tableau[b] == j->lettreJoueur) { // On verifie que le joueur R a au moins un pion sur la colonne de gauche pour démarrer une verification de victoire
			markerCase1(grilleHex, b);
			verifCase1(grilleHex, b, tailleLigne, j);
		}
	}
	for (b = 0; b <= (tailleLigne - 1)*tailleLigne; b = (b + tailleLigne)) {
		if (grilleHex->tableau[b] == 'W') { // On lance la deuxieme verification en regardant si la premiere ligne contient bien un case marquée W
			markerCase2(grilleHex, b);
			verifCase2(grilleHex, b, tailleLigne, j);
		}
	}
}

void markerCase1(Hex *grilleHex, int caseVerifiee) {

	grilleHex->tableau[caseVerifiee] = 'W'; // Marqueur de la première passe de vérification
}

void markerCase2(Hex *grilleHex, int caseVerifiee) {

	grilleHex->tableau[caseVerifiee] = '@';// Marqueur de la deuxième passe de vérification
}

unsigned int creationValeurHub(int caseVerifiee, unsigned int tailleLigne) {

	for (unsigned int q = 1; q <= tailleLigne - 1; ++q) {

		if (caseVerifiee < 0 || caseVerifiee>(tailleLigne*tailleLigne) - 1) // caseverifiee est alors hors du tableau, on ne verifiera rien
			return 0;
		else if (caseVerifiee == 0) // caseVerifiee est en haut a gauche, on ne verifiera pas ce qui est hors du tableau
			return 1;
		else if (caseVerifiee == (q*tailleLigne)) //caseVerifiee est sur la colonne de gauche, on ne verifiera pas ce qui est hors du tableau
			return 2;
		else if (caseVerifiee == (tailleLigne - 1)*tailleLigne) //caseVerifiee est en bas a gauche, on ne verifiera pas ce qui est hors du tableau
			return 3;
		else if (caseVerifiee == tailleLigne - 1) //caseVerifiee est en haut a droite, on ne verifiera pas ce qui est hors du tableau
			return 4;
		else if (caseVerifiee == ((q*tailleLigne) - 1)) //caseVerifiee est sur la colonne de droite, on ne verifiera pas ce qui est hors du tableau
			return 5;
		else if (caseVerifiee == (tailleLigne*tailleLigne) - 1) //caseVerifiee est en bas a droite, on ne verifiera pas ce qui est hors du tableau
			return 6;
		else if (caseVerifiee == q) // caseVerifiee est sur la premiere ligne, on ne verifiera pas ce qui est hors du tableau
			return 7;
		else if (caseVerifiee == ((tailleLigne-1)*tailleLigne) + q) // caseVerifiee est sur la dernière ligne, on ne verifiera pas ce qui est hors du tableau
			return 8;
	}
			return 9; //caseVerifiee n'est dans aucun cas particulier , on verifiera toutes les coordonees autour
}

void verifCase1(Hex *grilleHex, int caseVerifiee, unsigned int tailleLigne, Joueur *j) {

	// On verifie ici que les cases autour de la case verifiee (en hexagone) contiennent un pion du joueur dont c'est le tour
	// On marque alors cette case et on relance cette même verification sur la case en question
	// Les cas particuliers comme les coins de tableau et les bords sont traités par creationValeurHub
	// Certaines verification ne sont donc pas lancées en fonction de la valeur de hub
	// Le sens de vérification pour cette première passe est le sens horaire

	unsigned int hub = creationValeurHub(caseVerifiee, tailleLigne);

	if (grilleHex->tableau[(caseVerifiee - tailleLigne) + 1] == j->lettreJoueur && hub != 0 && hub != 1 && hub != 4 && hub != 5 && hub!= 6 && hub != 7) {
		markerCase1(grilleHex, ((caseVerifiee - tailleLigne) + 1));
		verifCase1(grilleHex, ((caseVerifiee - tailleLigne) + 1), tailleLigne, j);
	}
	else if (grilleHex->tableau[(caseVerifiee + 1)] == j->lettreJoueur && hub != 0 && hub != 4 && hub != 5 && hub != 6) {
		markerCase1(grilleHex, (caseVerifiee + 1));
		verifCase1(grilleHex, (caseVerifiee + 1), tailleLigne, j);
	}
	else if (grilleHex->tableau[caseVerifiee + tailleLigne] == j->lettreJoueur && hub != 0 && hub != 3 && hub != 6 && hub != 8) {
		markerCase1(grilleHex, (caseVerifiee + tailleLigne));
		verifCase1(grilleHex, (caseVerifiee + tailleLigne), tailleLigne, j);
	}
	else if (grilleHex->tableau[(caseVerifiee + tailleLigne) - 1] == j->lettreJoueur && hub != 0 && hub != 1 && hub != 2 && hub != 3 && hub != 6 && hub != 8) {
		markerCase1(grilleHex, ((caseVerifiee + tailleLigne) - 1));
		verifCase1(grilleHex, ((caseVerifiee + tailleLigne) - 1), tailleLigne, j);
	}
	else if (grilleHex->tableau[(caseVerifiee - 1)] == j->lettreJoueur && hub != 0 && hub != 1 && hub != 2 && hub != 3) {
		markerCase1(grilleHex, (caseVerifiee - 1));
		verifCase1(grilleHex, (caseVerifiee - 1), tailleLigne, j);
	}
	else if (grilleHex->tableau[caseVerifiee - tailleLigne] == j->lettreJoueur && hub != 0 && hub != 1 && hub != 4 && hub != 7) {
		markerCase1(grilleHex, (caseVerifiee - tailleLigne));
		verifCase1(grilleHex, (caseVerifiee - tailleLigne), tailleLigne, j);
	}
}

void verifCase2(Hex *grilleHex, int caseVerifiee, unsigned int tailleLigne, Joueur *j) {


	// On verifie ici que les cases autour de la case verifiee (en hexagone) contiennent 
	// 1)un pion du joueur dont c'est le tour
	// 2)un marker W
	// Dans le premier cas, on est a un embranchement non vérifié par la première passe
	// On relance donc la premiere verification (verifCase1)
	// Dans le second cas, on marque la case avec le marker @ et on continue la verification (verifCase2)
	// Les cas particuliers comme les coins de tableau et les bords sont traités par creationValeurHub
	// Certaines verification ne sont donc pas lancées en fonction de la valeur de hub
	// Le sens de vérification pour cette première passe est cette fois le sens anti - horaire


	unsigned int hub = creationValeurHub(caseVerifiee, tailleLigne);

	if (grilleHex->tableau[caseVerifiee - tailleLigne] == 'W'  && hub != 0 && hub != 1 && hub != 4 && hub != 7) {
		markerCase2(grilleHex, (caseVerifiee - tailleLigne));
		verifCase1(grilleHex, (caseVerifiee - tailleLigne), tailleLigne, j);
		verifCase2(grilleHex, (caseVerifiee - tailleLigne), tailleLigne, j);
	}
	else if (grilleHex->tableau[(caseVerifiee - 1)] == 'W' && hub != 0 && hub != 1 && hub != 2 && hub != 3) {
		markerCase2(grilleHex, (caseVerifiee - 1));
		verifCase1(grilleHex, (caseVerifiee - 1), tailleLigne, j);
		verifCase2(grilleHex, (caseVerifiee - 1), tailleLigne, j);
	}
	else if (grilleHex->tableau[(caseVerifiee + tailleLigne) - 1] == 'W' && hub != 0 && hub != 1 && hub != 2 && hub != 3 && hub != 6 && hub != 8) {
		markerCase2(grilleHex, ((caseVerifiee + tailleLigne) - 1));
		verifCase1(grilleHex, ((caseVerifiee + tailleLigne) - 1), tailleLigne, j);
		verifCase2(grilleHex, ((caseVerifiee + tailleLigne) - 1), tailleLigne, j);
	}
	else if (grilleHex->tableau[caseVerifiee + tailleLigne] == 'W' && hub != 0 && hub != 3 && hub != 6 && hub != 8) {
		markerCase2(grilleHex, (caseVerifiee + tailleLigne));
		verifCase1(grilleHex, (caseVerifiee + tailleLigne), tailleLigne, j);
		verifCase2(grilleHex, (caseVerifiee + tailleLigne), tailleLigne, j);
	}
	else if (grilleHex->tableau[(caseVerifiee + 1)] == 'W' && hub != 0 && hub != 4 && hub != 5 && hub != 6) {
		markerCase2(grilleHex, (caseVerifiee + 1));
		verifCase1(grilleHex, (caseVerifiee + 1), tailleLigne, j);
		verifCase2(grilleHex, (caseVerifiee + 1), tailleLigne, j);
	}
	else if (grilleHex->tableau[(caseVerifiee - tailleLigne) + 1] == 'W' && hub != 0 && hub != 1 && hub != 4 && hub != 5 && hub != 6 && hub != 7) {
		markerCase2(grilleHex, ((caseVerifiee - tailleLigne) + 1));
		verifCase1(grilleHex, ((caseVerifiee - tailleLigne) + 1), tailleLigne, j);
		verifCase2(grilleHex, ((caseVerifiee - tailleLigne) + 1), tailleLigne, j);
	}
}

void afficherTableau(Hex *grilleHex, unsigned int tailleLigne)
{
	unsigned int ligne = 0, caseTableau = 0, compteurContour = 0;

	afficherChaineCaractere("\n");

	afficherChaineCaractere("X "); //On affiche le coin supérieur gauche, valable pour les 2 joueurs (lettre X)
	for (compteurContour = 0; compteurContour < tailleLigne; ++compteurContour) {
		afficherChaineCaractere("B ");//On affiche la première ligne de 'B' pour le joueur B
	}
	afficherChaineCaractere("X\n");//On affiche le coin supérieur droit, valable pour les 2 joueurs (lettre X)

	for (ligne = 1; ligne <= tailleLigne; ++ligne) {
		espaceParLigne(ligne); // On fait un espace supplémentaire par numéro de ligne, la ligne 0 etant la première ligne de 'B', pour donner la struction hexagonale aux cases
		afficherChaineCaractere("R "); //On affiche le R de la colonne de gauche, ligne 1 puis +1 jusque tailleLigne compris
		for (caseTableau = (ligne*tailleLigne) - tailleLigne; caseTableau < ligne*tailleLigne; ++caseTableau) { //On affiche les cases d'une ligne
			printf("%c ", grilleHex->tableau[caseTableau]);
		}
		afficherChaineCaractere("R"); //On affiche le R de la colonne de droite, ligne 1 puis +1 jusque tailleLigne compris
		afficherChaineCaractere("\n");
	}
	espaceParLigne(ligne); 

	afficherChaineCaractere("X ");//On affiche le coin inférieur gauche, valable pour les 2 joueurs (lettre X)

	for (compteurContour = 0; compteurContour < tailleLigne; ++compteurContour) {
		afficherChaineCaractere("B "); //On affiche la dernière ligne de 'B'
	}
	afficherChaineCaractere("X\n"); //On affiche le coin inférieur droit, valable pour les 2 joueurs (lettre X)
	afficherChaineCaractere("\n");

}

void espaceParLigne(int numeroLigne) {

	for (int i = 0; i < numeroLigne; ++i)
		printf(" ");
}

int declarerVictoireJoueurB(Hex *grilleHex, int tailleLigne, Joueur *j) {

	for (int a = 0; a < tailleLigne; ++a)
		if (grilleHex->tableau[((tailleLigne - 1)*(tailleLigne)+a)] == 'W' || grilleHex->tableau[((tailleLigne - 1)*(tailleLigne)+a)] == '@') // Si une case de la ligne la plus en bas est marquée
			return 1; // Le joueur 1 ( 'B' ) a gagné

		return 0;
}

int declarerVictoireJoueurR(Hex *grilleHex, int tailleLigne, Joueur *j) {

	for (int a = tailleLigne - 1; a < tailleLigne*tailleLigne; a = (a + tailleLigne)) 
		if (grilleHex->tableau[a] == 'W' || grilleHex->tableau[a] == '@') // Si une case de la colonne la plus a droite est marquée
			return 2; // Le joueur 2 ( 'R' ) a gagné

		return 0;
}

void remettreLettreJoueurTableau(Hex *grilleHex, int tailleLigne, Joueur *j) {

	for (int b = 0; b < (tailleLigne*tailleLigne); ++b) {
		if (grilleHex->tableau[b] == 'W' || grilleHex->tableau[b] == '@') // Une fois vérification et marquages effectués pour le joueur J
			grilleHex->tableau[b] = j->lettreJoueur; // On remet sur les cases marquées le pion du joueur J (B ou R)
	}
}