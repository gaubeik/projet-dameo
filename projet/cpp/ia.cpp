#include "../header/jeux.h"

using namespace std;

bool Jeux::minmax(int numPlayer, int profondeur)
{
	string test;

	Plateau* pia;
	int len=p->length();

	Pion*** plaTmpReset;
	plaTmpReset = p->copy();
	
	pia = new Plateau(len,plaTmpReset);

	int max = -100000;

	int maxTmp=0;

	int maxEat=p->bestEatby(numPlayer);
	int maxEaTmp=maxEat;

	int x=-1;
	int y=-1;
	int a=-1;
	int b=-1;


	int maxx=-1;
	int maxy=-1;
	int maxa=-1;
	int maxb=-1;


	while(maxEat==0)
	{
		if(a<0 || b<0)
		{
			pia->searchPlayer(x,y,numPlayer);
		}
		pia->searchPlayer(a,b,-1);
	
	cout<<"minmax in:"<<x<<":"<<y<<":"<<a<<":"<<b<<endl;
		
		if(x<0 || y<0)
		{
			cout<<"minmax :"<<maxx<<":"<<maxy<<":"<<maxa<<":"<<maxb<<endl;
			if(p->deplace(maxx,maxy,maxa,maxb,numPlayer))
			{
				return true;
			}
			return false;
		}
		if(pia->deplace(x,y,a,b,numPlayer))
		{
			
		//	plaTmp=pia->copy();

			maxTmp= min(numPlayer,profondeur-1, len, pia);
				cout<<"maxTmp :"<<maxTmp<<endl;
			if(maxTmp>max)
			{
				pia->afficheTest();
				cout<<"************************************"<<endl;
				max=maxTmp;
				maxx=x;
				maxy=y;
				maxa=a;
				maxb=b;
			}
			
			pia->afficheTest();

			pia->replacePlat(plaTmpReset);
			
			pia->afficheTest();

/*			for (int i = 0; i < len; i++)
			{
				for(int j=0; j<len; j++)
				{
					cout<<"|"<<plaTmpReset[i][j];
				}
				cout<<endl;
			}

			pia->afficheTestBis();
*/			cin>>test;

		}
	}

	int xtmp=-1;
	int ytmp=-1;

	bool newStart=true;
	bool stop=false;

	while(true)
	{
		cerr<<"boucle"<<endl;
		if(newStart)
		{
			pia->searchPlayer(x,y,numPlayer);
			xtmp=x;
			ytmp=y;
		//	newStart=false;
		}
		pia->searchPlayer(a,b,-1);

		if(!newStart && (a<0 || b<0))
		{
			newStart=true;
		}

		if((x<0 || y<0) || (maxEat==0 && (a<0 || b<0)))
		{
			if(p->deplace(maxx,maxy,maxa,maxb,numPlayer))
			{
				return true;
			}
			return false;
		}

		if(p->canMove(x,y,a,b,numPlayer)  && pia->howManEat(x, y,numPlayer,pia->platKing(x,y))==maxEat && pia->howManEat(a,b,numPlayer,pia->platKing(x,y))==maxEat-1 && pia->deplace(x,y,a,b,numPlayer))
		{
			if (maxEat==0)
			{

				maxTmp= min(numPlayer,profondeur-1, len, pia);

				if(maxTmp>max)
				{
					max=maxTmp;
					maxx=x;
					maxy=y;
					maxa=a;
					maxb=b;
				}
				newStart=true;
				x=xtmp;
				y=ytmp;
				a=-1;
				b=-1;
				pia->replacePlat(plaTmpReset);
				maxEat=maxEaTmp;
			}
			else
			{
				maxEat-=1;
				x=a;
				y=b;
				a=-1;
				b=-1;
				newStart=false;
			}
		}
	}
}

int Jeux::min( int numPlayer, int profondeur, int len,Plateau* pia)
{

	string test;
//	cout<<"min"<<endl;

	if(numPlayer+1==2 && !pia->playerAlive(numPlayer) || numPlayer-1==1 && !pia->playerAlive(numPlayer-1))
	{
		return 10000;
	}
	else if (!pia->playerAlive(numPlayer))
	{
		return -10000;
	}
	else if(profondeur==0)
	{
		return pia->eval(numPlayer);	
	}

	if(numPlayer==1)
	{
		numPlayer=2;
	}
	else
		numPlayer=1;

	Pion*** plaTmpReset;
	plaTmpReset = pia->copy();

	Pion*** plaTmp=NULL;

	int min = 100000;

	int minTmp=0;

	int maxEat=pia->bestEatby(numPlayer);
	int maxEaTmp=maxEat;

	int x=-1;
	int y=-1;
	int a=-1;
	int b=-1;

	cout<<"min :"<<maxEat<<endl;
//	cin>>test;

	while(maxEat==0)
	{
		if(a<0 || b<0)
		{
			pia->searchPlayer(x,y,numPlayer);
		}
		pia->searchPlayer(a,b,-1);

		if(x<0 || y<0)
		{
			return min;
		}
		if(pia->deplace(x,y,a,b,numPlayer))
		{
			plaTmp=pia->copy();

			minTmp= max(numPlayer,profondeur-1, len, pia);

			if(minTmp<min)
			{
				min=minTmp;
			}
			pia->replacePlat(plaTmpReset);
		}
	}

	int xtmp=-1;
	int ytmp=-1;

	bool newStart=true;
	while(true)
	{
		cerr<<"min boucle"<<endl;
		if(newStart)
		{
			pia->searchPlayer(x,y,numPlayer);
			xtmp=x;
			ytmp=y;
		//	newStart=false;
		}
		pia->searchPlayer(a,b,-1);
	

		if((x<0 || y<0) || (maxEat==0 && (a<0 || b<0)))
		{
			return min;
		}

		if(!newStart && (a<0 || b<0))
		{
			newStart=true;
		}

		if(p->canMove(x,y,a,b,numPlayer)  && pia->howManEat(x, y,numPlayer,pia->platKing(x,y))==maxEat && pia->howManEat(a,b,numPlayer,pia->platKing(x,y))==maxEat-1 && pia->deplace(x,y,a,b,numPlayer))
		{
			if (maxEat==0)
			{
				plaTmp=pia->copy();

				minTmp= max(numPlayer,profondeur-1, len, pia);

				if(minTmp<min)
				{
					min=minTmp;
				}
				newStart=true;
				x=xtmp;
				y=ytmp;
				a=-1;
				b=-1;
				pia->replacePlat(plaTmpReset);
				maxEat=maxEaTmp;
			}
			else
			{
				maxEat-=1;
				x=a;
				y=b;
				a=-1;
				b=-1;
				newStart=false;
			}
		}
	}
}

int Jeux::max( int numPlayer, int profondeur, int len,Plateau* pia)
{
	if(numPlayer==1)
	{
		numPlayer=2;
	}
	else
		numPlayer=1;

		string test;
//	cout<<"max"<<endl;
	if(numPlayer+1==2 && !pia->playerAlive(numPlayer) || numPlayer-1==1 && !pia->playerAlive(numPlayer-1))
	{ 
		return 10000;
	}
	else if (!pia->playerAlive(numPlayer))
	{
		return -10000;
	}
	else if(profondeur==0)
	{
		return pia->eval(numPlayer); 
	}




	Pion*** plaTmpReset;
	plaTmpReset = pia->copy();


	Pion*** plaTmp=NULL;

	int max = -100000;

	int maxTmp=0;

	int maxEat=pia->bestEatby(numPlayer);
	int maxEaTmp=maxEat;

	int x=-1;
	int y=-1;
	int a=-1;
	int b=-1;

	cout<<"max :"<<maxEat<<endl;
//	cin>>test;


	while(maxEat==0)
	{
		if(a<0 || b<0)
		{
			pia->searchPlayer(x,y,numPlayer);
		}
		pia->searchPlayer(a,b,-1);

		if(x<0 || y<0)
		{
			return max;
		}
		
		if(pia->deplace(x,y,a,b,numPlayer))
		{
			plaTmp=pia->copy();

			maxTmp= min(numPlayer,profondeur-1, len, pia);

			if(maxTmp>max)
			{
				max=maxTmp;
			}
			pia->replacePlat(plaTmpReset);
		}
	}

	int xtmp=-1;
	int ytmp=-1;

	bool newStart=true;
	while(true)
	{
		cerr<<"max boucle :"<<x<<":"<<y<<":"<<a<<":"<<b<<"      :"<<maxEat<<endl;
		if(newStart)
		{
			pia->searchPlayer(x,y,numPlayer);
			xtmp=x;
			ytmp=y;
			newStart=false;
		}
		pia->searchPlayer(a,b,-1);

		if((x<0 || y<0) || (maxEat==0 && (a<0 || b<0)))
		{
			return max;
		}


		if(!newStart && (a<0 || b<0))
		{
			newStart=true;
		}

		if(p->canMove(x,y,a,b,numPlayer)  && pia->howManEat(x, y,numPlayer,pia->platKing(x,y))==maxEat && pia->howManEat(a,b,numPlayer,pia->platKing(x,y))==maxEat-1 && pia->deplace(x,y,a,b,numPlayer))
		{
			if (maxEat==0)
			{
				plaTmp=pia->copy();

				maxTmp= min(numPlayer,profondeur-1, len, pia);
				cerr<<"maxTmp :"<<maxTmp<<"-------------"<<endl;
				if(maxTmp>max)
				{
					max=maxTmp;
				}
				newStart=true;
				x=xtmp;
				y=ytmp;
				a=-1;
				b=-1;
				pia->replacePlat(plaTmpReset);
				maxEat=maxEaTmp;
			}
			else
			{
				maxEat-=1;
				x=a;
				y=b;
				a=-1;
				b=-1;
				newStart=false;
			}
		}
	}
}