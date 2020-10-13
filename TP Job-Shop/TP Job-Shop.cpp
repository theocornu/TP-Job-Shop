// TP Job-Shop.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "instance.h"

int main()
{
	t_instance instance = { 0 };
	t_vecteur vecteur = { 0 };
	t_vecteur vecteur_test = { 0, 1, 1, 2, 1, 3, 2, 2, 3, 3 };

	lecture("LA01.txt", instance);
	genererVecteur(instance, vecteur);
	evaluer(instance, vecteur);

	// affichage plus long chemin
	int pc = vecteur.PUIT.piece, pm = vecteur.PUIT.machine;
	std::cout << "puit / makespan = " << vecteur.makespan << std::endl;
	while (vecteur.pere[pc][pm].piece != 0) {
		t_operation& op = vecteur.pere[pc][pm];
		std::cout << "piece " << op.piece
			<< " : machine " << op.machine
			<< " : debut = " << vecteur.st[pc][pm] << std::endl;
		pc = op.piece;
		pm = op.machine;
	}
}

