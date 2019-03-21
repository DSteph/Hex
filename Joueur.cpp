#include "Joueur.h"

Joueur creerJoueur() {

	Joueur j;
	j.lettreJoueur = 'B';
	return j;
}

void changerJoueur(Joueur *j) { // On permute le joueur quand la fonction est appelée

	if (j->lettreJoueur == 'R')
		j->lettreJoueur = 'B';
	else  j->lettreJoueur = 'R';
}
