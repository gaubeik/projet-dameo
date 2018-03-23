#ifndef PION_H
#define PION_H

#include <iostream>

class Pion
{
	bool dead;
	bool king;

	int player;

	public:
		Pion();
		Pion( int );
		Pion(bool, bool, int);

		bool isDead();
		bool isKing();
		int getPlayer();

		void kill();
		void revive();
		void toKing();

		void changePlayer (int);
		void changeDead (bool);
		void changeKing (bool);


};


#endif