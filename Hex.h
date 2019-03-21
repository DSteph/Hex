#include "Joueur.h"

#pragma once
struct Hex {
	char *tableau;
};

void lancerPartieHex();
Hex creerPlateau(int tailleLigne);
void libererPlateau(Hex *grilleHex);
void initCaseTableauEnPoint(Hex *creerGrille, int tailleLigne);
void defCoordoneePion(Hex *grilleHex, unsigned int tailleLigne, Joueur *j);
bool placerUnPion(Hex *grilleHex, unsigned int tailleLigne, unsigned int ligne, unsigned colonne, Joueur *j);
unsigned int creationValeurHub(int caseVerifiee, unsigned int tailleLigne);
int verificationVictoire(Hex *grilleHex, int tailleLigne, int valeurVictoire, Joueur *j);
int declarerVictoireJoueurB(Hex *grilleHex, int tailleLigne, Joueur *j);
int declarerVictoireJoueurR(Hex *grilleHex, int tailleLigne, Joueur *j);
void remettreLettreJoueurTableau(Hex *grilleHex,int tailleLigne,Joueur *j);
void verifCase1(Hex *grilleHex, int caseVerifiee, unsigned int tailleLigne, Joueur *j);
void verifCase2(Hex *grilleHex, int caseVerifiee, unsigned int tailleLigne, Joueur *j);
void markerCase1(Hex *grilleHex, int caseVerifiee);
void markerCase2(Hex *grilleHex, int caseVerifiee);
void verifPremiereLigneJoueurB(Hex *grilleHex, unsigned int tailleLigne, Joueur *j);
void verifPremiereColonneJoueurR(Hex *grilleHex, unsigned int tailleLigne, Joueur *j);
void afficherTableau(Hex *grilleHex, unsigned int tailleLigne);
void espaceParLigne(int numeroLigne);