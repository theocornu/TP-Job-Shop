#include <string>
#pragma once

const int NMAX = 30;
const int MMAX = 20;

typedef struct t_instance {
	int n; // nombre de pièces
	int m; // nombre de machines
	int machine[NMAX + 1][MMAX + 1]; 
	// machine[i][j] = j-ième machine sur laquelle
	// passe la pièce i
	int p[NMAX + 1][MMAX + 1];
	// p[i][j] = durée de traitement de la pièce i
	// par la j-ième machine
}t_instance;

typedef struct t_vecteur {
	int v[(NMAX + 1) * (MMAX + 1)]; // vecteur
	int st[NMAX + 1][MMAX + 1]; // starting times
	int cout; // makespan
	int pere[NMAX + 1][MMAX + 1]; // liste des pères de chaque sommet
}t_vecteur;

void lecture(std::string nomFichier, t_instance& instance);
void evaluer(t_instance& instance, t_vecteur& vecteur);
void genererVecteur(t_instance& instance, t_vecteur& vecteur);
void rechercheLocale(t_instance& instance, t_vecteur vecteur, int nbmaxIter);