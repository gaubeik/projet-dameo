#ifndef PILE_H
#define PILE_H

#include <iostream>

struct Noeud
{
	int x;
	int y;

	Noeud * suiv;

	
};

void supprime(Noeud*n);
Noeud* newNoeud();
Noeud* newNoeud(int a, int b, Noeud*n);

class Pile
{
	Noeud* tete;
	
	public :
		Pile() ;
		Pile(int);
		~Pile() ;
		
		bool vide();
		void empile(int x, int y);
		void depile(int& x, int& y);
		void look(int& x, int& y);
		void affiche();
		void afficheTete();

		void supprTete();

		int size();

		void empty();
};



#endif