// TP Job-Shop.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <sstream>
#include "instance.h"

void afficherPlusLongChemin(t_vecteur& vecteur) {
	int pc = vecteur.PUIT.piece, pm = vecteur.PUIT.machine;
	t_operation& op = vecteur.pere[pc][pm];
	std::string chemin[NMAX*MMAX];
	int iChemin = 0;
	while (vecteur.pere[pc][pm].piece != 0) {
		pc = op.piece;
		pm = op.machine;
		std::ostringstream ss;
		ss << "( " << op.piece << " , " << op.machine << " ) : " << vecteur.st[pc][pm] << std::endl;
		chemin[iChemin++] = ss.str();
		op = vecteur.pere[pc][pm];
	}
	for (--iChemin; iChemin >= 0; iChemin--) {
		std::cout << chemin[iChemin];
	}
	std::cout << "makespan = " << vecteur.makespan << std::endl;
}

int main()
{
	t_instance instance = { 0 };
	
	t_vecteur vecteur = { 0 };

	lecture("LA01.txt", instance);
	genererVecteur(instance, vecteur);
	evaluer(instance, vecteur);
	afficherPlusLongChemin(vecteur);
	std::cout << std::endl;
	t_vecteur min = rechercheLocale(instance, vecteur, 100);
	for (int i = 1; i <= 100; i++) {
		t_vecteur vec = { 0 };
		genererVecteur(instance, vec);
		min = rechercheLocale(instance, vec, 100);
	}
	afficherPlusLongChemin(min);

	/*t_vecteur vecteur_test = { 0, 1, 1, 2, 1, 3, 2, 2, 3, 3 };

	lecture("job_test.txt", instance);
	evaluer(instance, vecteur_test);
	afficherPlusLongChemin(vecteur_test);
	std::cout << std::endl;
	t_vecteur min = rechercheLocale(instance, vecteur_test, 100);
	afficherPlusLongChemin(min);*/
}

