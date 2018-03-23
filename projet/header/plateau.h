#ifndef PLATEAU_H
#define PLATEAU_H

#include <cstdlib>

#include <stdio.h>


#include "pion.h"
#include "pile.h"



class Plateau
{
	Pion *** plat;
	int len;
	Pile *p;

public:

	Plateau ();
	Plateau (int);

	Plateau(int, Pion***);

	~Plateau();

	void supprPionDead();

	void affiche();

	void initialise();

	void move(int, int, int, int);

	bool canMove(int a, int b, int x, int y,int numPlayer);

	bool deplace(int a, int b, int x, int y,int);

	bool deplacerKing(int, int ,int ,int ,int);

	bool deplacerPion(int, int ,int ,int ,int);

	int typeMove(int a, int b, int x, int y);
	bool logicMove(int a, int b, int x, int y);
	
	void test();

	int bestEatby(int numPlayer);

	int howManEat(int x, int y,int numPlayer,bool isKing);
	int howManEatPion(int i, int j, int numPlayer);
	int howManEatKing(int i, int j, int numPlayer);

	int getPileSize(){return p->size();};

	bool playerAlive(int);
	int playerCount(int numPlayer);
	int eval(int numPlayer);

	Pion*** copy();

	void replacePlat(Pion***);

	int length();

	int platPlayer(int x, int y);
	bool platKing(int x,int y);

	void searchPlayer(int &x,int &y, int numPlayer);

	void afficheTest();
	void afficheTestBis();
};



#endif