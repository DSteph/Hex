#include "IHM.h"
#include "Hex.h"
#include "Joueur.h"
#include "Test.h"
#include "unittest.h"

void tester() {

	unsigned int tailleLigne = 5, valeurVictoire = 0;
	afficherChaineCaractere("On a tailleLigne = 5");
	Joueur j = creerJoueur();
	assertTrue(j.lettreJoueur == 'B', "Le joueur est cree avec la lettre 'B'");
	Hex grilleHex = creerPlateau(tailleLigne);
	assertEquals(0, declarerVictoireJoueurB(&grilleHex, tailleLigne, &j),"Le joueur 'B' n'a pas gagne au debut de la partie");
	assertEquals(0, declarerVictoireJoueurR(&grilleHex, tailleLigne, &j), "Le joueur 'R' n'a pas gagne au debut de la partie");
	assertEquals(0u, creationValeurHub(-5, tailleLigne), "pour caseverifiee = -5, creationValeurHub renvoie 0, on est hors du tableau, rien ne sera verifie");
	assertEquals(0u, creationValeurHub(26, tailleLigne), "pour caseverifiee = 26, creationValeurHub renvoie 0, on est hors du tableau, rien ne sera verifie");
	assertEquals(1u, creationValeurHub(0, tailleLigne), "pour caseverifiee = 0,creationValeurHub renvoie 1, on est en haut a gauche du tableau, seules les cases existantes autour seront verifiees");
	assertEquals(2u, creationValeurHub((2 * tailleLigne), tailleLigne), "pour caseverifiee = 2*tailleLigne, creationValeurHub renvoie 2, on est sur la colonne la plus a gauche du tableau, seules les cases existantes autour seront verifiees");
	assertEquals(3u, creationValeurHub((tailleLigne - 1)*tailleLigne, tailleLigne), "pour caseverifiee = (tailleLigne-1)*tailleLigne,creationValeurHub renvoie 3, on est en bas a gauche du tableau, seules les cases existantes autour seront verifiees");
	assertEquals(4u, creationValeurHub(tailleLigne - 1, tailleLigne), "pour caseverifiee = tailleLigne-1,creationValeurHub renvoie 4, on est en haut a droite du tableau, seules les cases existantes autour seront verifiees");
	assertEquals(5u, creationValeurHub(((2 * tailleLigne) - 1), tailleLigne), "pour caseverifiee = (2*tailleLigne)-1,creationValeurHub renvoie 5, on est sur la colonne la plus a droite, seules les cases existantes autour seront verifiees");
	assertEquals(6u, creationValeurHub((tailleLigne*tailleLigne) - 1, tailleLigne), "pour caseverifiee = (tailleLigne*tailleLigne)-1,creationValeurHub renvoie 6, on est en bas a droite du tableau, seules les cases existantes autour seront verifiees");
	assertEquals(7u, creationValeurHub(1, tailleLigne), "pour caseverifiee = 1,creationValeurHub renvoie 7, on est sur la ligne la plus en haut du tableau, seules les cases existantes autour seront verifiees");
	assertEquals(8u, creationValeurHub((((tailleLigne - 1)*tailleLigne) + 1), tailleLigne), "pour caseverifiee = ((tailleLigne-1)*tailleLigne)+1,creationValeurHub renvoie 8, on est sur la ligne la plus en bas du tableau, seules les cases existantes autour seront verifiees");
	assertEquals(9u, creationValeurHub(13, tailleLigne), "pour caseverifiee = 13,creationValeurHub renvoie 7, nous ne sommes dans aucun cas particuliers, toutes les cases autour seront verifiees");
	placerUnPion(&grilleHex, tailleLigne, 1, 1, &j);
	assertTrue(grilleHex.tableau[(1 * tailleLigne) - (tailleLigne - (1 - 1))] == j.lettreJoueur, "La case aux coordonees 1.1 est maintenant 'B' apres placerUnPion");
	changerJoueur(&j);
	assertTrue(j.lettreJoueur == 'R', "Le joueur est maintenant 'R' apres changerJoueur");
	placerUnPion(&grilleHex, tailleLigne, 1, 1, &j);
	assertFalse(grilleHex.tableau[(1 * tailleLigne) - (tailleLigne - (1 - 1))] == j.lettreJoueur, "La case aux coordonees 1.1 n'est pas 'R' apres placerUnPion car elle est deja 'B'");
	placerUnPion(&grilleHex, tailleLigne, 2, 2, &j);
	assertTrue(grilleHex.tableau[(2 * tailleLigne) - (tailleLigne - (2 - 1))] == j.lettreJoueur, "La case aux coordonees 2.2 est maintenant 'R' apres placerUnPion");
	placerUnPion(&grilleHex, tailleLigne, 2, 1, &j);
	markerCase1(&grilleHex, 5);
	assertTrue(grilleHex.tableau[(2 * tailleLigne) - (tailleLigne - (1 - 1))] == 'W', "La case aux coordonees 2.1 est maintenant 'W' apres markerCase1");
	markerCase2(&grilleHex, 6);
	assertTrue(grilleHex.tableau[(2 * tailleLigne) - (tailleLigne - (2 - 1))] == '@', "La case aux coordonees 2.2 est maintenant '@' apres markerCase1");
	remettreLettreJoueurTableau(&grilleHex, tailleLigne, &j);
	assertTrue(grilleHex.tableau[(2 * tailleLigne) - (tailleLigne - (1 - 1))] == j.lettreJoueur, "La case aux coordonees 2.1 est de nouveau 'R' apres remettreLettreJoueurTableau");
	assertTrue(grilleHex.tableau[(2 * tailleLigne) - (tailleLigne - (2 - 1))] == j.lettreJoueur, "La case aux coordonees 2.2 est de nouveau 'R' apres remettreLettreJoueurTableau");
	doCase1(&grilleHex, tailleLigne, valeurVictoire, &j);
	doCase2(&grilleHex, tailleLigne, valeurVictoire, &j);
	doCase3(&grilleHex, tailleLigne, valeurVictoire, &j);
	doCase4(&grilleHex, tailleLigne, valeurVictoire, &j);

}

void doCase1(Hex *grilleHex, int tailleLigne, int valeurVictoire, Joueur *j) {

	placerUnPion(grilleHex, tailleLigne, 2, 3, j);
	placerUnPion(grilleHex, tailleLigne, 2, 4, j);
	placerUnPion(grilleHex, tailleLigne, 2, 5, j);
	afficherTableau(grilleHex, tailleLigne);
	assertEquals(2, verificationVictoire(grilleHex, tailleLigne, valeurVictoire, j), "Valeur victoire = 2 apres verification car le joueur 'R' a bien gagne partie");
}

void doCase2(Hex *grilleHex, int tailleLigne, int valeurVictoire, Joueur *j) {

	initCaseTableauEnPoint(grilleHex, tailleLigne);
	valeurVictoire = reinitValeurVictoire();
	changerJoueur(j);
	placerUnPion(grilleHex, tailleLigne, 1, 1, j);
	placerUnPion(grilleHex, tailleLigne, 2, 1, j);
	placerUnPion(grilleHex, tailleLigne, 3, 1, j);
	placerUnPion(grilleHex, tailleLigne, 4, 1, j);
	placerUnPion(grilleHex, tailleLigne, 5, 1, j);
	afficherTableau(grilleHex, tailleLigne);
	assertEquals(1, verificationVictoire(grilleHex, tailleLigne, valeurVictoire, j), "Valeur victoire = 1 apres verification car le joueur 'B' a bien gagne partie");

}

void doCase3(Hex *grilleHex, int tailleLigne, int valeurVictoire, Joueur *j) {
	initCaseTableauEnPoint(grilleHex, tailleLigne);
	valeurVictoire = reinitValeurVictoire();
	changerJoueur(j);
	placerUnPion(grilleHex, tailleLigne, 1, 1, j);
	placerUnPion(grilleHex, tailleLigne, 2, 1, j);
	placerUnPion(grilleHex, tailleLigne, 2, 2, j);
	placerUnPion(grilleHex, tailleLigne, 3, 2, j);
	placerUnPion(grilleHex, tailleLigne, 3, 3, j);
	placerUnPion(grilleHex, tailleLigne, 3, 4, j);
	placerUnPion(grilleHex, tailleLigne, 4, 2, j);
	placerUnPion(grilleHex, tailleLigne, 4, 3, j);
	placerUnPion(grilleHex, tailleLigne, 4, 4, j);
	placerUnPion(grilleHex, tailleLigne, 5, 2, j);
	placerUnPion(grilleHex, tailleLigne, 5, 4, j);
	placerUnPion(grilleHex, tailleLigne, 5, 5, j);
	afficherTableau(grilleHex, tailleLigne);
	assertEquals(2, verificationVictoire(grilleHex, tailleLigne, valeurVictoire, j), "Valeur victoire = 2 apres verification car le joueur 'R' a bien gagne partie");

}

void doCase4(Hex *grilleHex, int tailleLigne, int valeurVictoire, Joueur *j) {

	initCaseTableauEnPoint(grilleHex, tailleLigne);
	valeurVictoire = reinitValeurVictoire();
	changerJoueur(j);
	placerUnPion(grilleHex, tailleLigne, 1, 3, j);
	placerUnPion(grilleHex, tailleLigne, 2, 3, j);
	placerUnPion(grilleHex, tailleLigne, 2, 2, j);
	placerUnPion(grilleHex, tailleLigne, 3, 2, j);
	placerUnPion(grilleHex, tailleLigne, 4, 1, j);
	placerUnPion(grilleHex, tailleLigne, 3, 3, j);
	placerUnPion(grilleHex, tailleLigne, 3, 4, j);
	placerUnPion(grilleHex, tailleLigne, 3, 5, j);
	placerUnPion(grilleHex, tailleLigne, 2, 5, j);
	placerUnPion(grilleHex, tailleLigne, 4, 3, j);
	placerUnPion(grilleHex, tailleLigne, 4, 5, j);
	placerUnPion(grilleHex, tailleLigne, 5, 4, j);
	afficherTableau(grilleHex, tailleLigne);
	assertEquals(1, verificationVictoire(grilleHex, tailleLigne, valeurVictoire, j), "Valeur victoire = 1 apres verification car le joueur 'B' a bien gagne partie");
}

