#include "../header/pile.h"


using namespace std;

Pile::Pile()
{
	tete=NULL;
}

Pile::~Pile()
{
	supprime (tete);
	delete[] tete;
}



void supprime(Noeud*n)
{
	if (n->suiv)
		supprime(n->suiv);
	delete[] n;
}

Noeud* newNoeud()
{
	Noeud*n = new Noeud;
	n->x=-1;
	n->y=-1;
	n->suiv=NULL;
	return n;
}

Noeud* newNoeud(int a, int b, Noeud*m)
{
	Noeud*n = new Noeud;
	n->x=a;
	n->y=b;
	n->suiv=m;

	return n;
}

bool Pile::vide()
{
	if (tete)
		return false;
	return true;
}

void Pile::empile( int x, int y)
{
	tete=newNoeud(x,y,tete);
}

void Pile::supprTete()
{
	Noeud*n=tete;
	tete=tete->suiv;

	delete n;
}

void Pile::depile(int &a, int &b)
{
	a=tete->x;
	b=tete->y;
	supprTete();
}

void Pile::look(int &a, int &b)
{
	a=tete->x;
	b=tete->y;
}


void Pile::affiche()
{
	Noeud*n=tete;
	while(n)
	{
		cout<<n->x<<":"<<n->y<<"|";
		n=n->suiv;
	}
	cout<<endl;
}

void Pile::afficheTete()
{
	if(tete)
	{
		cout<<tete->x<<":"<<tete->y<<endl;
	}
	else
	{
		cout<<"pile vide"<<endl;
	}
}

int Pile::size()
{
	Noeud*n=tete;
	int cmp=0;

	while (n)
	{
		cmp+=1;
		n=n->suiv;
	}
	return cmp;
}


void Pile::empty()
{
	while(!vide())
	{
		supprTete();
	}
}