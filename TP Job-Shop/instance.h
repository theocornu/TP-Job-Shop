#include <string>
#pragma once

const int NMAX = 30;
const int MMAX = 20;

typedef struct t_instance {
	int n; // nombre de pi�ces
	int m; // nombre de machines
	int machine[NMAX + 1][MMAX + 1]; 
	// machine[i][j] = j-i�me machine sur laquelle
	// passe la pi�ce i
	int p[NMAX + 1][MMAX + 1];
	// p[i][j] = dur�e de traitement de la pi�ce i
	// par la j-i�me machine
}t_instance;

typedef struct t_vecteur {
	int v[(NMAX + 1) * (MMAX + 1)]; // vecteur
	int st[NMAX + 1][MMAX + 1]; // starting times
	int cout; // makespan
	int pere[NMAX + 1][MMAX + 1]; // liste des p�res de chaque sommet
}t_vecteur;

void lecture(std::string nomFichier, t_instance& instance);
void evaluer(t_instance& instance, t_vecteur& vecteur);
void genererVecteur(t_instance& instance, t_vecteur& vecteur);
void rechercheLocale(t_instance& instance, t_vecteur vecteur, int nbmaxIter);