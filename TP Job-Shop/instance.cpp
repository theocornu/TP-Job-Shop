#include "instance.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

void lecture(std::string nomFichier, t_instance & instance)
{
	std::ifstream fichier(nomFichier);
	int n = 0, m = 0;

	if (fichier) {
		fichier >> n >> m;
		instance.n = n;
		instance.m = m;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				fichier >> instance.machine[i][j] >> instance.p[i][j];
			}
		}

		fichier.close();
	}
}

void evaluer(t_instance & instance, t_vecteur & vecteur)
{

}

void genererVecteur(t_instance & instance, t_vecteur & vecteur)
{
	int n = instance.n;
	int m = instance.m;
	int nbPiece[NMAX + 1] = { 0 };
	int numPiece[NMAX + 1] = { 0 };
	int nbc = n;

	for (int i = 1; i <= n; i++) {
		nbPiece[i] = m;
		numPiece[i] = i;
	}
	
	std::srand(std::time(NULL));
	int taille = n * m;
	for (int i = 1; i <= taille; i++) {
		int j = rand() % nbc + 1;
		vecteur.v[i] = numPiece[j];
		nbPiece[j]--;
		if (nbPiece[j] == 0) {
			nbPiece[j] = nbPiece[nbc];
			numPiece[j] = numPiece[nbc];
			nbc--;
		}
	}
}

void rechercheLocale(t_instance & instance, t_vecteur vecteur, int nbmaxIter)
{
}
