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

	int x=0;
	int y=0;
	int a=0;
	int b=0;

	bool fini=false;

	bool onemove=false;

	while (!fini)
	{
		if (pia->platPlayer(x,y)==numPlayer &&pia->howManEat(x, y,numPlayer)==maxEat && pia->howManEat(a,b,numPlayer)>=maxEat-1 && pia->deplace(x,y,a,b,numPlayer))
		{
			pia->afficheTest();
			maxEat-=1;
			x=a;
			y=b;
			a=0;
			b=0;

			onemove=true;
		}
		else if(pia->platPlayer(x,y)==numPlayer)
		{
			b+=1;
			if(b>=len)
			{
				a+=1;
				b=0;
			}
			if(a>=len)
			{
				a=0;
				b=0;

				y+=1;
				if(y>=len)
				{
					x+=1;
					y=0;
				}
				if(x>=len)
				{
					break;
				}
			}
		}
		else
		{
			y+=1;
			if(y>=len)
			{
				x+=1;
				y=0;
			}
			if(x>=len)
			{
				break;
			}
		}

		if(maxEat<=0 && onemove)
		{


			pia->supprPionDead();
			cerr<<"minmax x:"<<x<<" y:"<<y<<" a:"<<a<<" b:"<<b<<endl;
			maxTmp= min(numPlayer,profondeur-1, len,pia);

			if(maxTmp>max)
			{
				max=maxTmp;
				maxPlat=pia->copy();
			}
			pia->replacePlat(plaTmp);
			maxEat=pia->bestEatby(numPlayer);

			a=0;
			b=0;

			y+=1;
			if(y>=len)
			{
				x+=1;
				y=0;
			}
			if(x>=len)
			{
				break;
			}
		}
	}

	p->replacePlat(maxPlat);
}


int Jeux::min(int numPlayer, int profondeur, int len, Plateau * pia)
{
	cerr<<"min pro:"<<profondeur<<endl;

	
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

	int x=0;
	int y=0;
	int a=0;
	int b=0;
	
	bool fini=false;

	bool onemove=false;

	while (!fini)
	{
		if (pia->platPlayer(x,y)==numPlayer &&pia->howManEat(x, y,numPlayer)==maxEat && pia->howManEat(a,b,numPlayer)>=maxEat-1 && pia->deplace(x,y,a,b,numPlayer))
		{
			pia->afficheTest();
			maxEat-=1;
			x=a;
			y=b;
			a=0;
			b=0;

			onemove=true;
			
		}
		else if(pia->platPlayer(x,y)==numPlayer)
		{
			b+=1;
			if(b>=len)
			{
				a+=1;
				b=0;
			}
			if(a>=len)
			{
				a=0;
				b=0;

				y+=1;
				if(y>=len)
				{
					x+=1;
					y=0;
				}
				if(x>=len)
				{
					break;
				}
			}
		}
		else
		{
			y+=1;
			if(y>=len)
			{
				x+=1;
				y=0;
			}
			if(x>=len)
			{
				break;
			}
		}

		if(maxEat<=0 && onemove)
		{


			pia->supprPionDead();
			cerr<<"min x:"<<x<<" y:"<<y<<" a:"<<a<<" b:"<<b<<endl;
			minTmp= max(numPlayer,profondeur-1, len, pia);

			if(minTmp<min)
			{
				min=minTmp;
			}
			pia->replacePlat(plaTmp);
			maxEat=pia->bestEatby(numPlayer);

			a=0;
			b=0;
			
			y+=1;
			if(y>=len)
			{
				x+=1;
				y=0;
			}
			if(x>=len)
			{
				break;
			}
		}
	}

	return min;

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

	int x=0;
	int y=0;
	int a=0;
	int b=0;
	
	bool fini=false;

	bool onemove=false;

	while (!fini)
	{
		if (pia->platPlayer(x,y)==numPlayer &&pia->howManEat(x, y,numPlayer)==maxEat && pia->howManEat(a,b,numPlayer)>=maxEat-1 && pia->deplace(x,y,a,b,numPlayer))
		{

			pia->afficheTest();
			maxEat-=1;
			x=a;
			y=b;
			a=0;
			b=0;

			onemove=true;
		}
		else if(pia->platPlayer(x,y)==numPlayer)
		{
			b+=1;
			if(b>=len)
			{
				a+=1;
				b=0;
			}
			if(a>=len)
			{
				a=0;
				b=0;

				y+=1;
				if(y>=len)
				{
					x+=1;
					y=0;
				}
				if(x>=len)
				{
					break;
				}
			}
		}
		else
		{
			y+=1;
			if(y>=len)
			{
				x+=1;
				y=0;
			}
			if(x>=len)
			{
				break;
			}
		}


		if(maxEat<=0 && onemove)
		{


			pia->supprPionDead();

			cerr<<"max x:"<<x<<" y:"<<y<<" a:"<<a<<" b:"<<b<<endl;
			maxTmp= min(numPlayer,profondeur-1, len,pia);
			cerr<<"return min:"<<maxTmp<<endl;
			if(maxTmp>max)
			{
				max=maxTmp;
				cerr<<"new max:"<<max<<endl;
			}
			pia->replacePlat(plaTmp);
			maxEat=p->bestEatby(numPlayer);

			a=0;
			b=0;
			
			y+=1;
			if(y>=len)
			{
				x+=1;
				y=0;
			}
			if(x>=len)
			{
				break;
			}

		}
	

	}

	return max;
}