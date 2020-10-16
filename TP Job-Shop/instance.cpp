#include "instance.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

const t_operation t_vecteur::PUIT = { 0, MMAX };

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
	int np[NMAX + 1] = { 0 }; // compteur de machine courante par pièce
	int& makespan = vecteur.makespan;
	const t_operation& puit = vecteur.PUIT;
	t_operation mp[MMAX + 1] = { 0 };
	// St déjà initialisé à 0
	for (int i = 1; i <= m; i++) {
		mp[i] = { -1,-1 };
	}
	for (int i = 1, taille = n*m; i <= taille; i++) {
		int j = vecteur.v[i]; // valeur courante dans le vecteur de Bierwirth
		np[j]++;
  		int mc = instance.machine[j][np[j]]; // machine courante
		// comparaison job
		if (np[j] > 1) {
			int deb = vecteur.st[j][np[j] - 1];
			int fin = deb + instance.p[j][np[j] - 1];
			if (fin > vecteur.st[j][np[j]]) {
				vecteur.st[j][np[j]] = fin;
				vecteur.pere[j][np[j]] = { j, np[j] - 1 };
			}
		}
		// comparaison machine 
		if (mp[mc].piece != -1 && mp[mc].machine != -1) {
			int pc = mp[mc].piece;
			int nc = mp[mc].machine;
			if (vecteur.st[pc][nc] + instance.p[pc][nc] > vecteur.st[j][np[j]]) {
				vecteur.st[j][np[j]] = vecteur.st[pc][nc] + instance.p[pc][nc];
				vecteur.pere[j][np[j]] = mp[mc];
			}
		}
		mp[mc] = { j, np[j] };
		if (vecteur.st[j][np[j]] + instance.p[j][np[j]] >= makespan) {
			vecteur.pere[puit.piece][puit.machine] = { j, np[j] };
			makespan = vecteur.st[j][np[j]] + instance.p[j][np[j]];
		}
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
	
	//srand(time(NULL));
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

t_vecteur rechercheLocale(t_instance & instance, t_vecteur vecteur, int nbmaxIter)
{
	evaluer(instance, vecteur);
	int nbIter = 0;
	// i : piece , j : numéro machine
	int i = t_vecteur::PUIT.piece, j = t_vecteur::PUIT.machine,
		ipere = vecteur.pere[i][j].piece, jpere = vecteur.pere[i][j].machine;
	t_vecteur nouveauVecteur;
	while (ipere != 0 && nbIter < nbmaxIter) {
		nouveauVecteur = vecteur;
		if (i != t_vecteur::PUIT.piece)
			permutation(nouveauVecteur, { i, j }, { ipere, jpere });
		// permutation des deux jobs dans le vecteur de Bierwirth
		evaluer(instance, nouveauVecteur);
		// si meilleure solution trouvée
		if (nouveauVecteur.makespan < vecteur.makespan) {
			vecteur = nouveauVecteur;
			i = t_vecteur::PUIT.piece, j = t_vecteur::PUIT.machine;
			ipere = vecteur.pere[i][j].piece, jpere = vecteur.pere[i][j].machine;
			nbIter = 0;
		}
		else {
			i = ipere, j = jpere;
			ipere = vecteur.pere[ipere][jpere].piece, jpere = vecteur.pere[ipere][jpere].machine;
			nbIter++;
		}
	}
	return vecteur;
}

void permutation(t_vecteur& vecteur, t_operation t1, t_operation t2) {
	int i = t1.piece, j = t1.machine,
		ipere = t2.piece, jpere = t2.machine;
	int cpt_i = 0, cpt_ipere = 0;
	int index_i = 0, index_ipere = 0;
	for (int k = 1, taille = (NMAX + 1)*(MMAX + 1); k < taille; k++) {
		if (cpt_i < j && vecteur.v[k] == i) {
			cpt_i++;
			index_i = k;
		}
		if (cpt_ipere < jpere && vecteur.v[k] == ipere) {
			cpt_ipere++;
			index_ipere = k;
		}	
	}
	// recherche dans le vecteur
	/*while (cpt_i != j && cpt_ipere != jpere) {
		index_i++, index_ipere++;
		if (vecteur.v[index_i] == i) 
			cpt_i++;
		if (vecteur.v[index_ipere] == ipere)
			cpt_ipere++;
	}*/
	// permutation
	int tmp = vecteur.v[index_i];
	vecteur.v[index_i] = vecteur.v[index_ipere];
	vecteur.v[index_ipere] = tmp;
}