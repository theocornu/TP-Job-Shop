#include "instance.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

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
				int num_machine, duree;
				fichier >> num_machine >> duree;
				instance.machine[i][j] = num_machine + 1;
				instance.p[i][j] = duree;
			}
		}

		fichier.close();
	}
	else {
		std::cerr << "Erreur : nom de fichier invalide" << std::endl;
	}
}

void evaluer(t_instance & instance, t_vecteur & vecteur)
{
	int n = instance.n, m = instance.m;
	int np[NMAX + 1] = { 0 }; // compteur de machine courante par pi�ce
	t_couple mp[MMAX + 1] = { 0 };
	// St d�j� initialis� � 0
	for (int i = 1; i <= m; i++) {
		mp[i] = { -1,-1 };
	}
	for (int i = 1, taille = n*m; i <= taille; i++) {
		int j = vecteur.v[i]; // valeur courante dans le vecteur de Bierwirth
		np[j]++;
 		int mc = instance.machine[j][np[j]]; // machine courante

		// 1) Ajout de l'arc de la position actuelle
		// vers la prochaine position qui fait r�f�rence � j
		// 2) Ajout de l'arc de la position actuelle
		// � la prochaine position qui utilise la m�me machine

		// MAJ cout et pere

		if (np[j] > 1) {
			int deb = vecteur.st[i][np[j] - 1];
			int fin = deb + instance.p[j][np[j] - 1];
			if (fin > vecteur.st[j][np[j]]) {
				vecteur.st[j][np[j]] = fin;
			}
		}
		if (mp[mc].piece != -1 && mp[mc].machine != -1) {
			int pc = mp[mc].piece;
			int nc = mp[mc].machine;
			if (vecteur.st[pc][nc] + instance.p[pc][nc] > vecteur.st[j][np[j]]) {
				vecteur.st[j][np[j]] = vecteur.st[pc][nc] + instance.p[pc][nc];
			}
		}
		mp[mc] = { j, np[j] };
		// stocker mp dans pere

	}

	/* TESTS */
	for (int i = 1; i <= m; i++) {
		std::cout << i-1 << " " << mp[i].piece << " " << mp[i].machine << std::endl;
	}
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
	
	//std::srand(std::time(NULL));
	std::srand(2);
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
