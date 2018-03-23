#include "../header/jeux.h"

using namespace std;

void Jeux::minmax(int numPlayer, int profondeur)
{
	cerr<<"minmax"<<endl;
	Plateau* pia;
	int len=p->length();

	Pion*** plaTmp;
	plaTmp = p->copy();
	pia = new Plateau(len,plaTmp);

	Pion*** maxPlat;
	int max = -100000;

	int maxTmp=0;

	int maxEat=p->bestEatby(numPlayer);

	int xtmp=0;
	int ytmp=0;
	int a=0;
	int b=-1;

	bool inpu=false;

	cerr<<"for 0"<<endl;


	for (int x = 0; x < len; x++)
	{
		for (int y = 0; y < len; y++)
		{
		xtmp=x;
		ytmp=y;

		inpu=false;

		while(!inpu)
		{
			b+=1;
			if (b>=len)
			{
				a+=1;
				b=0;
			}
			if(a>=len)
			{
				p->replacePlat(maxPlat);
				return;
			}

			if (pia->howManEat(xtmp, ytmp,numPlayer)==maxEat && pia->howManEat(a,b,numPlayer)>=maxEat-1)
			{
				if (pia->deplace(xtmp,ytmp,a,b,numPlayer))
				{
					maxEat-=1;
					inpu=true;

					xtmp=a;
					ytmp=b;
					b=-1;
					a=0;
				}
			}

		}

		if(maxEat<=0)
		{
			pia->supprPionDead();

			pia->affiche();

			maxTmp= min(numPlayer,profondeur-1, len,pia);

			if(maxTmp>max)
			{
				max=maxTmp;
			
				maxPlat=pia->copy();
			}
			pia->replacePlat(plaTmp);
			maxEat=p->bestEatby(numPlayer);
		}

	

		}
	}
	cerr<<"replace"<<endl;
	p->replacePlat(maxPlat);
	cerr<<"fin replace"<<endl;

}


int Jeux::min(int numPlayer, int profondeur, int len, Plateau * pia)
{
	cerr<<"min"<<endl;
	if(!pia->playerAlive((numPlayer+1)%2))
	{ 
		return 100000;
	}
	else if(profondeur==0)
	{
		return pia->playerCount(numPlayer)-pia->playerCount((numPlayer+1)%2);
	}

	Pion*** plaTmp = pia->copy();

	int min = 100000;

	int minTmp=0;

	int maxEat=p->bestEatby(numPlayer);

	int xtmp=0;
	int ytmp=0;
	int a=0;
	int b=-1;

	bool inpu=false;

	for (int x = 0; x < len; x++)
	{
		for (int y = 0; y < len; y++)
		{
		xtmp=x;
		ytmp=y;

		inpu=false;

		while(!inpu)
		{
			b+=1;
			if (b>=len)
			{
				a+=1;
				b=0;
			}
			if(a>=len)
			{
				return min;
			}

			if (pia->howManEat(xtmp, ytmp,numPlayer)==maxEat && pia->howManEat(a,b,numPlayer)>=maxEat-1)
			{
				if (pia->deplace(xtmp,ytmp,a,b,numPlayer))
				{
					maxEat-=1;
					inpu=true;

					xtmp=a;
					ytmp=b;
					b=-1;
					a=0;
				}
			}
			pia->affiche();
		}

		if(maxEat<=0)
		{
			pia->supprPionDead();
			minTmp= max(numPlayer,profondeur-1, len,pia);

			if(minTmp<min)
			{
				min=minTmp;
			}
			pia->replacePlat(plaTmp);
			maxEat=p->bestEatby(numPlayer);
		}

	

		}
	}

}

int Jeux::max(int numPlayer, int profondeur, int len, Plateau * pia)
{
	cerr<<"max"<<endl;
	if(!pia->playerAlive(numPlayer))
	{ 
		return -100000;	
	}
	else if(profondeur==0)
	{
		return pia->playerCount((numPlayer+1)%2)- pia->playerCount(numPlayer);
	}

	Pion*** plaTmp = pia->copy();

	int max = -100000;

	int maxTmp=0;

	int maxEat=p->bestEatby(numPlayer);

	int xtmp=0;
	int ytmp=0;
	int a=0;
	int b=-1;

	bool inpu=false;

	for (int x = 0; x < len; x++)
	{
		for (int y = 0; y < len; y++)
		{
		xtmp=x;
		ytmp=y;

		inpu=false;

		while(!inpu)
		{
			b+=1;
			if (b>=len)
			{
				a+=1;
				b=0;
			}
			if(a>=len)
			{
				return max;
			}

			if (pia->howManEat(xtmp, ytmp,numPlayer)==maxEat && pia->howManEat(a,b,numPlayer)>=maxEat-1)
			{
				if (pia->deplace(xtmp,ytmp,a,b,numPlayer))
				{
					maxEat-=1;
					inpu=true;

					xtmp=a;
					ytmp=b;
					b=-1;
					a=0;
				}
			}

		}

		if(maxEat<=0)
		{
			pia->supprPionDead();
			maxTmp= min(numPlayer,profondeur-1, len,pia);

			if(maxTmp>max)
			{
				max=maxTmp;
			
			}
			pia->replacePlat(plaTmp);
			maxEat=p->bestEatby(numPlayer);
		}

	

		}
	}


}




