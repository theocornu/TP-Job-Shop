// TP Job-Shop.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "instance.h"

int main()
{
	t_instance instance = { 0 };
	t_vecteur vecteur = { 0 };

	lecture("LA01.txt", instance);
	genererVecteur(instance, vecteur);
	evaluer(instance, vecteur);
}

