#include "../header/jeux.h"

using namespace std;

void Jeux::minmax(int numPlayer, int profondeur)
{
	string test;


	Plateau* pia;
	int len=p->length();

	Pion*** plaTmpReset;
	plaTmpReset = p->copy();
	pia = new Plateau(len,plaTmpReset);

	Pion*** plaTmp=NULL;

	Pion*** maxPlat;
	maxPlat=p->copy();

	int max = -100000;

	int maxTmp=0;

	int maxEat=p->bestEatby(numPlayer);

	int x=-1;
	int y=-1;
	int a=-1;
	int b=-1;

	bool selectPion=true;
	if (maxEat==0)
	{
		while(true)
		{
			if(selectPion)
			{
				pia->searchPlayer(x,y,numPlayer);
			}
			pia->searchPlayer(a,b,-1);

			if(x<0 || y<0 || a<0 || b<0)
			{
				pia->replacePlat(maxPlat);
			//	pia->afficheTest();

				p->replacePlat(maxPlat);
				return;
			}
			
			if (pia->deplace(x,y,a,b,numPlayer))
			{
				
				plaTmp=pia->copy();
				pia->supprPionDead();
				maxTmp= min(numPlayer,profondeur-1, len, pia);

				if(maxTmp>=max)
				{
					max=maxTmp;
					maxPlat=plaTmp;
				}
				pia->replacePlat(plaTmpReset);

				selectPion=true;
			}
			else
			{
				selectPion=false;
			}
		}
	}
	else
	{
		int xtmp=-1;
		int ytmp=-1;

		while(true)
		{
			
			if (selectPion)
			{
				pia->searchPlayer(x,y,numPlayer);
				xtmp=x;
				ytmp=y;
			}
			pia->searchPlayer(a,b,-1);
		
			if(x<0 || y<0 || a<0 || b<0)
			{
				p->replacePlat(maxPlat);
				return;
			}
			
			if (pia->howManEat(x, y,numPlayer,pia->platKing(x,y))==maxEat && pia->howManEat(a,b,numPlayer,pia->platKing(x,y))>=maxEat-1 && pia->deplace(x,y,a,b,numPlayer))
			{
				if(maxEat==0)
				{
					plaTmp=pia->copy();
					pia->supprPionDead();
					maxTmp= min(numPlayer,profondeur-1, len, pia);

					if(maxTmp>=max)
					{
						max=maxTmp;
						maxPlat=plaTmp;
					}
					pia->replacePlat(plaTmpReset);
					maxEat=pia->bestEatby(numPlayer);
					selectPion=true;
				}
				else
				{
					x=a;
					y=b;
					a=-1;
					b=-1;

					selectPion=false;
				}
			}
		}
	}

}

int Jeux::min(int numPlayer, int profondeur, int len, Plateau * pia)
{
	cerr<<"min"<<endl;
	pia->afficheTest();
	cerr<<"----------------------------------------------------------"<<endl;
	if(!pia->playerAlive((numPlayer+1)%2))
	{ 
		//		cerr<<"in dead :"<<(numPlayer+1)%2<<endl;
		return 100000;
	}
	else if(profondeur==0)
	{
		//		cerr<<"min prof 0 :"<<pia->playerCount(numPlayer)-pia->playerCount((numPlayer+1)%2)<<endl;
		return pia->playerCount(numPlayer)-pia->playerCount((numPlayer+1)%2);
	}

	Pion*** plaTmpReset;
	plaTmpReset = p->copy();
	pia = new Plateau(len,plaTmpReset);

	int min = 100000;

	int minTmp=0;

	int maxEat=pia->bestEatby(numPlayer);

	int x=-1;
	int y=-1;
	int a=-1;
	int b=-1;

	if (maxEat==0)
	{
		while(true)
		{
			pia->searchPlayer(x,y,numPlayer);
			pia->searchPlayer(a,b,-1);
		
			if(x<0 || y<0 || a<0 || b<0)
			{
				return min;
			}
			
			if (pia->howManEat(x, y,numPlayer,pia->platKing(x, y))==maxEat && pia->howManEat(a,b,numPlayer,pia->platKing(x, y))>=maxEat-1 && pia->deplace(x,y,a,b,numPlayer))
			{
				pia->supprPionDead();
				minTmp= max(numPlayer,profondeur-1, len, pia);

				if(minTmp>min)
				{
					min=minTmp;
				}
				pia->replacePlat(plaTmpReset);
				maxEat=pia->bestEatby(numPlayer);
			}
		}
	}
	else
	{
		while(true)
		{
			
			if (x==-1)
			{
				pia->searchPlayer(x,y,numPlayer);
			}
			pia->searchPlayer(a,b,-1);
		
			if(x<0 || y<0 || a<0 || b<0)
			{
				return min;
			}
			
			if (pia->howManEat(x, y,numPlayer,pia->platKing(x, y))==maxEat && pia->howManEat(a,b,numPlayer,pia->platKing(x, y))>=maxEat-1 && pia->deplace(x,y,a,b,numPlayer))
			{
				if(maxEat==0)
				{
					pia->supprPionDead();
					minTmp= max(numPlayer,profondeur-1, len, pia);

					if(minTmp<min)
					{
						min=minTmp;
					}
					pia->replacePlat(plaTmpReset);
					maxEat=pia->bestEatby(numPlayer);
				}
				else
				{
					x=a;
					y=b;
					a=-1;
					b=-1;
				}
			}
		}
	}

}

int Jeux::max(int numPlayer, int profondeur, int len, Plateau * pia)
{
	cerr<<"max"<<endl;
	pia->afficheTest();
	cerr<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	if(!pia->playerAlive(numPlayer))
	{ 
		//		cerr<<"max dead"<<endl;
		return 100000;	
	}
	else if(profondeur==0)
	{
		//		cerr<<"max prof 0 :"<<pia->playerCount(numPlayer)-pia->playerCount((numPlayer+1)%2)<<endl;
		return pia->playerCount(numPlayer)-pia->playerCount((numPlayer+1)%2);
	}

	Pion*** plaTmpReset;
	plaTmpReset = p->copy();
	pia = new Plateau(len,plaTmpReset);

	int max = -100000;

	int maxTmp=0;

	int maxEat=p->bestEatby(numPlayer);

	
	int x=-1;
	int y=-1;
	int a=-1;
	int b=-1;

	if (maxEat==0)
	{
		while(true)
		{
			pia->searchPlayer(x,y,numPlayer);
			pia->searchPlayer(a,b,-1);
		
			if(x<0 || y<0 || a<0 || b<0)
			{
				return max;
			}
			
			if (pia->howManEat(x, y,numPlayer,pia->platKing(x, y))==maxEat && pia->howManEat(a,b,numPlayer,pia->platKing(x, y))>=maxEat-1 && pia->deplace(x,y,a,b,numPlayer))
			{
				pia->supprPionDead();
				maxTmp= min(numPlayer,profondeur-1, len, pia);

				if(maxTmp>=max)
				{
					max=maxTmp;
				}
				pia->replacePlat(plaTmpReset);
			}
		}
	}
	else
	{
		while(true)
		{
			
			if (x==-1)
			{
				pia->searchPlayer(x,y,numPlayer);
			}
			pia->searchPlayer(a,b,-1);
		
			if(x<0 || y<0 || a<0 || b<0)
			{
				return max;
			}
			
			if (pia->howManEat(x, y,numPlayer,pia->platKing(x, y))==maxEat && pia->howManEat(a,b,numPlayer,pia->platKing(x, y))>=maxEat-1 && pia->deplace(x,y,a,b,numPlayer))
			{
				if(maxEat==0)
				{
					pia->supprPionDead();
					maxTmp= min(numPlayer,profondeur-1, len, pia);

					if(maxTmp>=max)
					{
						max=maxTmp;
					}
					pia->replacePlat(plaTmpReset);
					maxEat=pia->bestEatby(numPlayer);
				}
				else
				{
					x=a;
					y=b;
					a=-1;
					b=-1;
				}
			}
		}
	}
}

