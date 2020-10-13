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
}

