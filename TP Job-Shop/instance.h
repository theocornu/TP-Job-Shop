#include <string>
#pragma once

const int NMAX = 30;
const int MMAX = 20;

typedef struct t_instance {
	int n; // nombre de pièces
	int m; // nombre de machines
	int machine[NMAX + 1][MMAX + 1];
	int p[NMAX + 1][MMAX + 1];
}t_instance;

typedef struct t_vecteur {
	int v[(NMAX + 1) * (MMAX + 1)];
	int st[NMAX + 1][MMAX + 1];
	int cout;
	int pere[NMAX + 1][MMAX + 1];
}t_vecteur;

void lecture(std::string nomFichier, t_instance& instance);
void evaluer(t_instance& instance, t_vecteur& vecteur);
void genererVecteur(t_instance& instance, t_vecteur& vecteur);
void rechercheLocale(t_instance& instance, t_vecteur vecteur, int nbmaxIter);