#include "../header/jeux.h"


using namespace std;

Jeux::Jeux()
{
	p = new Plateau ;
	isIa[0]=0;
	isIa[1]=0;

	profondeurIa[0]=3;
	profondeurIa[1]=3;
}

void Jeux::start()
{
	int taille;
	cout<<"taille :";
	cin>>taille;

	p = new Plateau (taille);

	cout<<"le Joueur 1 est il une ia (0/1) :";
	cin>>isIa[0];
	if (isIa[0])
	{
		cout<<"quel est sa profondeur:";
		cin>>profondeurIa[0];
	}

	cout<<"le Joueur 2 est il une ia (0/1) :";
	cin>>isIa[1];
	if (isIa[1])
	{
		cout<<"quel est sa profondeur:";
		cin>>profondeurIa[1];
	}

	p->initialise();
}


void Jeux::play()
{

	bool stop= false;
	int numPlayer=0;
	string test;

	while (!stop)
	{
		if (isIa[numPlayer])
		{
			minmax(numPlayer+1,profondeurIa[numPlayer]);
		}
		else
		{
			playerTurn(numPlayer+1);
		}
		p->supprPionDead();

		numPlayer=(numPlayer+1)%2;


		cout<<"change player"<<endl;
		p->affiche();
		cout<<"-";
		cin>>test;

		if(!p->playerAlive(numPlayer+1))
		{
			cout<<"Joueur "<<numPlayer+1<<" a perdu"<<endl;
			return;
		}
	}
}

void Jeux::playerTurn(int numPlayer)
{
	bool inpu=false;

	string tmpx;
	string tmpa;
	string tmpy;
	string tmpb;
	int x=0;
	char y='_';
	int a=0;
	char b='_';
	
	int maxEat=p->bestEatby(numPlayer);

	while(true)
	{
		p->affiche();

	

		inpu=false;
		while(!inpu)
		{
			cout<<"player "<<numPlayer<<" origine:"<<maxEat<<endl<<"axe x (nbr):";
			cin>>tmpx;
			cout<<"axe y (lettre):";
			cin>>tmpy;
			y=tmpy[0];
			if (y>='a' && y<='z')
			{
				y=y-'a'+'A';
			}

			cout<<"player "<<numPlayer<<" destination:"<<maxEat<<endl<<"axe x (nbr):";
			cin>>tmpa;
			cout<<"axe y (lettre):";
			cin>>tmpb;
			b=tmpb[0];

			if (b>='a' && b<='z')
			{
				b=b-'a'+'A';
			}

			if( isNumb(tmpx) && isNumb(tmpa))
			{
				x=stoi(tmpx);
				a=stoi(tmpa);
			}
			else
			{
				x=-1;
				y=-1;
			}
			if(! p->logicMove(x, (int) y-'A',a,(int) b-'A') )
			{
				cerr<<"bad input"<<endl;
			}
			else if (p->canMove(x,(int) y-'A',a,(int) b-'A',numPlayer) && p->howManEat(x,(int) y-'A',numPlayer,p->platKing(x,(int) y-'A'))==maxEat && p->howManEat(a,(int) b-'A',numPlayer,p->platKing(x,(int) y-'A'))>=maxEat-1)
			{
				if (p->deplace(x,(int) y-'A',a,(int) b-'A',numPlayer))
				{
					maxEat-=1;
					inpu=true;
				}
			}
			else
			{
				cerr<<"wrong move"<<endl;
	cerr<<"x:"<<p->howManEat(x,(int) y-'A',numPlayer,p->platKing(x,(int) y-'A'))<<endl;
	cerr<<"a:"<<p->howManEat(a,(int) b-'A',numPlayer,p->platKing(x,(int) y-'A'))<<endl;
	cerr<<"king:"<<	p->platKing(x,(int) y-'A')<<endl;

			}

		}

		if(maxEat<=0)
		{
			return;	
		}

	}
}

void Jeux::test()
{
	///cout<<input(1)<<endl;
}








bool isNumb (string s)
{
	for (int i=0; i<s.size(); i++)
	{
		if(!isdigit(s[i]))
		{
			return false;
		}
	}
	return true;
}