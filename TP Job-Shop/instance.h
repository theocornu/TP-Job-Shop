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

typedef struct t_operation {
	int piece;
	int machine;
}t_operation;

typedef struct t_vecteur {
	int v[(NMAX + 1) * (MMAX + 1)]; // vecteur
	int st[NMAX + 1][MMAX + 1]; // starting times
	int makespan;
	static const t_operation PUIT;
	t_operation pere[NMAX + 1][MMAX + 1]; // liste des p�res de chaque sommet
}t_vecteur;

void lecture(std::string nomFichier, t_instance& instance);
void evaluer(t_instance& instance, t_vecteur& vecteur);
void genererVecteur(t_instance& instance, t_vecteur& vecteur);
t_vecteur rechercheLocale(t_instance& instance, t_vecteur vecteur, int nbmaxIter);
void permutation(t_vecteur& vecteur, t_operation t1, t_operation t2);
void GRASP(t_instance& instance, int nbmaxIter);