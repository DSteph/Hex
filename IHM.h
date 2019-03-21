#pragma once


int lireInt();
int lire(char *chaine, int longueur);
void viderBuffer();
void afficherChaineCaractere(char *chaineAAafficher);
void afficherEcranTitre();
void demanderARejouer(int *valeurRejouer);
int reinitValeurVictoire();
int defCoordoneeLigne(unsigned int);
int defCoordoneeColonne(unsigned int);
int defTailleLigne();
void afficherVainqueur(int valeurVictoire);
int choixPartieOuTest();
void lancerPartieOuTest();