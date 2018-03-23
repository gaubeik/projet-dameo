#include "plateau.h"

#include <string> 

using namespace std;

class Jeux
{
	Plateau *p;

	bool isIa[2];
	int profondeurIa[2];

	public:
		Jeux();

		void start();

		void play();

		void playerTurn(int);

		bool input(int);

		void test();

		bool cancelMove(int numPlayer);

		bool minmax(int,int);
		int min(int,int,int,Plateau*);
		int max(int,int,int,Plateau*);

};

bool isNumb (string s);