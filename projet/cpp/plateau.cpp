#include "../header/plateau.h"

using namespace std;

Plateau::Plateau ()
{
	len=0;
	plat=NULL;
	p=NULL;
}

Plateau::Plateau (int l)
{
	if (l<4)
		l=4;
	else if (l>26)
		l=26;

	len=l;

	plat= new Pion **[len];

	for(int i=0;i<len;i++)
	{
		plat[i]= new Pion *[len];
		for (int j=0; j<len; j++)
		{
			plat[i][j]=NULL;
		}
	}

	p=new Pile;
}

Plateau::Plateau(int l, Pion*** pl)
{
	len=l;
	p=new Pile;

	plat= new Pion **[len];
	cerr<<"mais vas y"<<endl;
	for(int i=0;i<len;i++)
	{
		plat[i]= new Pion *[len];
		for (int j=0; j<len; j++)
		{
			if(pl[i][j])
			{
				plat[i][j]= new Pion (pl[i][j]->isDead(),pl[i][j]->isKing(),pl[i][j]->getPlayer());
			}
			else
			{
				plat[i][j]=NULL;
			}
		}
	}
	cerr<<"dans ton luc"<<endl;
}

Plateau::~Plateau()
{
	for (int i=0;i<len; i++)
	{
		for (int j=0;j<len;j++)
		{
			delete [] plat[i][j];
		}
		delete [] plat[i];
	}
	delete [] plat;
}

int Plateau::length()
{
	return len;
}

void Plateau::supprPionDead()
{
	int x=0;
	int y=0;


	while(!p->vide())
	{
		p->depile(x,y);
		plat[x][y]=NULL;
	}

}



void Plateau::affiche()
{
//	system("clear");

	printf("\033[H\033[2J");

	for (int i=0;i<len; i++)
	{
		cout<<" ";
		for (int j=0;j<len;j++)
		{
			if(plat[i][j])
			{
				cout<<"|";//<<plat[i][j]->getPlayer();
				if (plat[i][j]->getPlayer()==1)
				{
					if (plat[i][j]->isDead())
						printf("\033[%sm","41");
					else
						printf("\033[%sm","47");
					printf("\033[%sm","30");
					if (plat[i][j]->isKing())
						cout<<"K";
					else
						cout<<"P";
					printf("\033[%sm","0");
				}
				else
				{	
					if (plat[i][j]->isDead())
						printf("\033[%sm","44");
					else
					printf("\033[%sm","40");
					if (plat[i][j]->isKing())
						cout<<"K";
					else
						cout<<"P";
					printf("\033[%sm","0");
				}
			}
			else
				cout<<"| ";
		}
		cout<<"| : "<<i<<endl;
	}

	for (int i=0;i<len+2;i++)
		cout<<"--";
	cout<<endl<<" |";
	for (int i='A';i<'A'+len;i++)
	{
		cout<<(char) i<<"|";
	}
	cout<<endl;
}


void Plateau::initialise()
{
	Pion*p;
	for (int i=0;i<len; i++)
	{
		for (int j=0;j<len;j++)
		{
			if (i+1<(len)/2 && (j>=i && j<len-i))
			{
				p= new Pion;
				p->changePlayer(1);
				plat[i][j]= p;
			}
			else if (i>((len-1)/2)+1  && (j<=i && j>=len-i-1))
			{
				p= new Pion;
				p->changePlayer(2);
				plat[i][j]= p;
			}
		}
	}
}


void Plateau::move(int a, int b, int x, int y)
{
	Pion * tmp = plat[a][b];
	plat[a][b]=plat[x][y];
	plat[x][y]=tmp;
}

bool Plateau::deplace(int a, int b, int x, int y,int numPlayer)
{
	if (!logicMove(a, b,x,y ))
		return false;

	if(!plat[a][b] || plat[a][  b ]->getPlayer()!=numPlayer)
		return false;

	if(plat[x][y])
		return false;

	if (plat[a][ b ]->isKing())
	{
		if( deplacerKing(a, b ,x, y ,numPlayer))
		{
			move(a, b ,x, y );
			return true;
		}
		return false;
	}
	if( deplacerPion(a, b ,x, y ,numPlayer))
	{
		move(a, b ,x, y );
		if(numPlayer==1 && x==len-1)
		{
			plat[x][y]->toKing();
		}
		else if (numPlayer==2 && x==0)
		{
			plat[x][y]->toKing();
		}


		return true;
	}
	return false;

}

bool Plateau::canMove(int a, int b, int x, int y,int numPlayer)
{
	if (!logicMove(a, b,x,y ))
		return false;

	if(!plat[a][b] || plat[a][  b ]->getPlayer()!=numPlayer)
		return false;

	if(plat[x][y])
		return false;

	if (plat[a][ b ]->isKing())
	{
		if( deplacerKing(a, b ,x, y ,numPlayer))
		{
			return true;
		}
		return false;
	}
	if( deplacerPion(a, b ,x, y ,numPlayer))
	{
		if(numPlayer==1 && x==len-1)
		{
			plat[x][y]->toKing();
		}
		else if (numPlayer==2 && x==0)
		{
			plat[x][y]->toKing();
		}


		return true;
	}
	return false;

}



bool Plateau::deplacerKing(int a,int b,int x,int y,int numPlayer)
{
	int tym=typeMove(a,b,x,y);

	Pion* P;
	P=NULL;
	bool onePion=false;

	if (tym==1)
	{
		if (b<y)
		{
			if(b==y-1)
			{
				if(plat[x][y])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			for (int i=b+1;i<y;i++)
			{
				if (plat[a][i])
				{

					if(onePion)
					{
						p->supprTete();
						return false;
					}
					P=plat[a][i];
					
					if(P->getPlayer()==numPlayer || P->isDead())
					{
						return false;
					}
					p->empile(a,i);
					onePion=true;
				}
			}
		}
		else
		{
			if(b==y+1)
			{
				if(plat[x][y])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			for(int i=b-1;i>y;i--)
			{
				if (plat[a][i])
				{
					if(onePion)
					{
						p->supprTete();
						return false;
					}
					P=plat[a][i];
					if(P->getPlayer()==numPlayer || P->isDead())
					{
						return false;
					}
					p->empile(a,i);
					onePion=true;
				}
			}
		}
	}

	else if (tym==2)
	{
		if (a<x)
		{
			if(a==x-1)
			{
				if(plat[x][y])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			for (int i=a+1;i<x;i++)
			{
				if (plat[i][b])
				{
					if(onePion)
					{
						p->supprTete();
						return false;
					}
					P=plat[i][b];
					if(P->getPlayer()==numPlayer || P->isDead())
					{
						return false;
					}
					p->empile(i,b);
					onePion=true;
				}
			}
		}
		else
		{	
			if(a==x+1)
			{
				if(plat[x][y])
				{
					return false;
				}
				else
				{
					return true;
				}
			}

			for(int i=a-1;i>x;i--)
			{
				if (plat[i][b])
				{
					if(onePion)
					{
						p->supprTete();
						return false;
					}
					P=plat[i][b];
					if(P->getPlayer()==numPlayer || P->isDead())
					{
						return false;
					}
					p->empile(i,b);
					onePion=true;
				}
			}
		}
	}

	else if (tym==3)
	{
		int j=b;
		if (a<x)
		{
			if(a==x-1)
			{
				if(plat[x][y])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			for (int i=a+1;i<x;i++)
			{
				if (plat[i][j])
				{
					if(onePion)
					{
						p->supprTete();
						return false;
					}
					P=plat[i][j];
					if(P->getPlayer()==numPlayer || P->isDead())
					{
						return false;
					}
					p->empile(i,j);
					onePion=true;
				}
				j++;
			}
		}
		else
		{
			if(a==x+1)
			{
				if(plat[x][y])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			for(int i=a-1;i>x;i--)
			{
				if (plat[i][j])
				{
					if(onePion)
					{
						p->supprTete();
						return false;
					}
					P=plat[i][j];
					if(P->getPlayer()==numPlayer || P->isDead())
					{
						return false;
					}
					p->empile(i,j);
					onePion=true;
				}
				j++;
			}
		}
	}

	else if (tym==4)
	{
		int j=b;
		if (a<x)
		{
			if(a==x-1)
			{
				if(plat[x][y])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			for (int i=a+1;i<x;i++)
			{
				if (plat[i][j])
				{
					if(onePion)
					{
						p->supprTete();
						return false;
					}
					P=plat[i][j];
					if(P->getPlayer()==numPlayer || P->isDead())
					{
						return false;
					}
					p->empile(i,j);
					onePion=true;
				}
				j--;
			}
		}
		else
		{
			if(a==x+1)
			{
				if(plat[x][y])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			for(int i=a-1;i>x;i--)
			{
				if (plat[i][j])
				{
					if(onePion)
					{
						p->supprTete();
						return false;
					}
					P=plat[i][j];
					if(P->getPlayer()==numPlayer || P->isDead())
					{
						return false;
					}
					p->empile(i,j);
					onePion=true;
				}
				j++;
			}
		}
	}

	//	p->afficheTete();
	if(P)
	{
		P->kill();
	}
	return true;
}

bool Plateau::deplacerPion(int a,int b,int x,int y,int numPlayer)
{
	int tym=typeMove(a,b,x,y);

	Pion* P;
	bool onePion=false;

	if (tym==1)
	{
		if (b<y)
		{
			if(plat[a][b+1] && (plat[a][b+1]->getPlayer()!=numPlayer  || !P->isDead()))
			{
				if(y==b+2)
				{
					if(plat[a][b+1]->isDead())
					{
						return false;
					}
					p->empile(x,b+1);
					plat[a][b+1]->kill();
					return true;
				}
				return false;
			}
			return false;
		}
		else
		{

			if(plat[a][b-1] && (plat[a][b-1]->getPlayer()!=numPlayer  || !P->isDead()))
			{
				if(y==b-2)
				{
					if(plat[a][b-1]->isDead())
					{
						return false;
					}
					p->empile(x,b-1);
					plat[a][b-1]->kill();
					return true;
				}
				return false;
			}
			return false;
		}
	}

	if (numPlayer==1)
	{
		if (tym==2)
		{	if(a<x)
			{
				if (!plat[a+1][b])
				{
					if(a+1==x)
						return true;
					return false;
				}
				if(plat[a+1][b]->isDead())
				{
					return false;
				}
				if(plat[a+1][b]->getPlayer()!=numPlayer)
				{
					if(x==a+2)
					{
						p->empile(a+1,y);
						plat[a+1][b]->kill();
						return true;
					}
					return false;
				}
				for (int i=a;i<x;i++)
				{
					if(!plat[i][b] || plat[i][b]->getPlayer()!=numPlayer || plat[i][b]->isKing())
						return false;
				}
				return true;

			}
			else
			{
				if (!plat[a-1][b] || plat[a-1][b]->isDead())
				{
					return false;
				}

				if(plat[a-1][b]->getPlayer()!=numPlayer)
				{
					if(x==a-2)
					{
						p->empile(a-1,y);
						plat[a-1][b]->kill();
						return true;
					}
					return false;
				}
				for (int i=a;i>x;i--)
				{
					if(!plat[i][b] || plat[i][b]->getPlayer()!=numPlayer || plat[i][b]->isKing())
						return false;
				}
				return true;

			}
		}
		if (tym==3)
		{
			if(a<x)
			{
				if (!plat[a+1][b+1])
				{
					if(a+1==x && b+1==y)
						return true;
					return false;
				}

				if(plat[a+1][b+1]->isDead())
				{
					return false;
				}

				if (plat[a+1][b+1]->getPlayer()!=numPlayer)
				{
					return false;
				}
				int i=a;int j=b;
				while(i<x)
				{
					if(!plat[i][j] || plat[i][j]->getPlayer()!=numPlayer || plat[i][j]->isKing())
						return false;
					i++;j++;
				}
				return true;
			}
			else
				return false;
		}


		if (tym==4)
		{
			if(a<x)
			{
				if (!plat[a+1][b-1])
				{
					if(a+1==x && b-1==y)
						return true;
					return false;
				}

				if(plat[a+1][b-1]->isDead())
				{
					return false;
				}

				if (plat[a+1][b-1]->getPlayer()!=numPlayer)
				{
					return false;
				}
				int i=a;int j=b;
				while(i<x)
				{
					if(!plat[i][j] || plat[i][j]->getPlayer()!=numPlayer || plat[i][j]->isKing())
						return false;
					i++;j--;
				}
				return true;
			}
			else
				return false;
		}
	}




	if (numPlayer==2)
	{
		if (tym==2)
		{	
			if(a>x)
			{
				if (!plat[a-1][b])
				{
					if(a-1==x)
						return true;
					return false;
				}

				if(plat[a-1][b]->isDead())
				{
					return false;
				}

				if(plat[a-1][b]->getPlayer()!=numPlayer)
				{
					if(x==a-2)
					{
						p->empile(a-1,y);
						plat[a-1][b]->kill();
						return true;
					}
					return false;
				}
				for (int i=a;i>x;i--)
				{
					if(!plat[i][b] || plat[i][b]->getPlayer()!=numPlayer || plat[i][b]->isKing())
						return false;
				}
				return true;

			}
			else
			{
				if (!plat[a+1][b] || plat[a+1][b]->isDead())
				{
					return false;
				}

				if(plat[a+1][b]->getPlayer()!=numPlayer)
				{
					if(x==a+2)
					{
						p->empile(a+1,y);
						plat[a+1][b]->kill();
						return true;
					}
					return false;
				}
				for (int i=a;i<x;i++)
				{
					if(!plat[i][b] || plat[i][b]->getPlayer()!=numPlayer || plat[i][b]->isKing())
						return false;
				}
				return true;

			}
		}
		if (tym==3)
		{
			if(a>x)
			{
				if (!plat[a-1][b-1])
				{
					if(a-1==x && b-1==y)
						return true;
					return false;
				}

				if(plat[a-1][b-1]->isDead())
				{
					return false;
				}

				if (plat[a-1][b-1]->getPlayer()!=numPlayer)
				{
					return false;
				}
				int i=a;int j=b;
				while(i>x)
				{
					if(!plat[i][j] || plat[i][j]->getPlayer()!=numPlayer || plat[i][j]->isKing())
						return false;
					i--;j--;
				}
				return true;
			}
			else
				return false;
		}


		if (tym==4)
		{
			if(a>x)
			{
				if (!plat[a-1][b+1])
				{
					if(a-1==x && b+1==y)
						return true;
					return false;
				}
				
				if(plat[a-1][b+1]->isDead())
				{
					return false;
				}

				if (plat[a-1][b+1]->getPlayer()!=numPlayer)
				{
					return false;
				}
				int i=a;int j=b;
				while(i>x)
				{
					if(!plat[i][j] || plat[i][j]->getPlayer()!=numPlayer || plat[i][j]->isKing())
						return false;
					i--;j++;
				}
				return true;
			}
			else
				return false;
		}
	}

	
}

bool Plateau::logicMove(int a, int b, int x, int y)
{
	if(a>=len || b>=len || x>=len || y>=len)
		return false;
	
	if(a<0 || b<0 || x<0 || y<0)
		return false;

	if(a==x)
	{
		if(b==y)
			return false;
		return true;
	}	
	if(b==y)
	{	if(a==x)
			return false;
		return true;
	}
	if(a-x==b-y || a-x==y-b)
		return true;

	return false;
}

int Plateau::typeMove(int a, int b, int x, int y)
{	
	if(a==x)
		return 1;
	if(b==y)
		return 2;

	if(a-x==b-y)
		return 3;
	if(a-x==y-b)
		return 4;

}

void Plateau::test()
{
//	cout<<"test"<<plat[5][ 'F' ]->isDead()<<endl;
}


int Plateau::bestEatby(int numPlayer)
{
	int nbr=0;
	int tmp=0;
	for (int i=0;i<len; i++)
	{
		for (int j=0;j<len;j++)
		{
			if(plat[i][j] && plat[i][j]->getPlayer()==numPlayer)
			{
				tmp=howManEat(i,j,numPlayer,plat[i][j]->isKing());
				
				if(tmp>nbr)
				{
					nbr=tmp;

				}
			}
		}
	}

	return nbr;
}


int Plateau::howManEat(int x, int y,int numPlayer, bool isKing)
{
	if(isKing)
	{
		return howManEatKing(x,y,numPlayer);
	}
	else
	{
		return howManEatPion(x,y,numPlayer);
	}
}


int Plateau::howManEatPion(int i, int j, int numPlayer)
{
	int tmp=0;
	int cpt=0;

	if(i>1 && plat[i-1][j] && plat[i-1][j]->getPlayer()!=numPlayer && !plat[i-1][j]->isDead() && !plat[i-2][j])
	{
		plat[i-1][j]->kill();
		if(numPlayer==2 && i-2==0)
		{
			tmp=howManEatKing(i-2,j,numPlayer);
		}
		else
		{
			tmp=howManEatPion(i-2,j,numPlayer);
		}
		plat[i-1][j]->revive();
		if (tmp>=cpt)
			cpt=tmp+1;
	}


	if(i<len-2 && plat[i+1][j] && plat[i+1][j]->getPlayer()!=numPlayer  && !plat[i+1][j]->isDead() && !plat[i+2][j])
	{
		plat[i+1][j]->kill();
		if(numPlayer==1 && i+2==len-1)
		{
			tmp=howManEatKing(i+2,j,numPlayer);
		}
		else
		{
			tmp=howManEatPion(i+2,j,numPlayer);
			plat[i+1][j]->revive();
		}
		if (tmp>=cpt)
			cpt=tmp+1;
	}

	if(j>1 && plat[i][j-1] && plat[i][j-1]->getPlayer()!=numPlayer && !plat[i][j-1]->isDead() && !plat[i][j-2])
	{
		plat[i][j-1]->kill();
		tmp=howManEatPion(i,j-2,numPlayer);
		plat[i][j-1]->revive();
		if (tmp>=cpt)
			cpt=tmp+1;
	}


	if(j<len-2 && plat[i][j+1] && plat[i][j+1]->getPlayer()!=numPlayer && !plat[i][j+1]->isDead() && !plat[i][j+2])
	{
		plat[i][j+1]->kill();
		tmp=howManEatPion(i,j+2,numPlayer);
		plat[i][j+1]->revive();
		if (tmp>=cpt)
			cpt=tmp+1;
	}

	return cpt;
}

int Plateau::howManEatKing(int i, int j, int numPlayer)
{
	int tmp=0;
	int cpt=0;
	for(int x=0; x<=i; x++)
	{
		if(x>1 && plat[x-1][j] && plat[x-1][j]->getPlayer()!=numPlayer && !plat[x-1][j]->isDead() && !plat[x-2][j])
		{
			plat[x-1][j]->kill();
			tmp=howManEatKing(x-2,j,numPlayer);
			plat[x-1][j]->revive();
			if (tmp>=cpt)
				cpt=tmp+1;
		}
	}

	for(int x=i; x<len; x++)
	{
		if(x<len-2 && plat[x+1][j] && plat[x+1][j]->getPlayer()!=numPlayer  && !plat[x+1][j]->isDead() && !plat[x+2][j])
		{
			plat[x+1][j]->kill();
			tmp=howManEatKing(x+2,j,numPlayer);
			plat[x+1][j]->revive();
			if (tmp>=cpt)
				cpt=tmp+1;
		}
	}

	for(int x=0; x<=j; x++)
	{
		if(x>1 && plat[i][x-1] && plat[i][x-1]->getPlayer()!=numPlayer && !plat[i][x-1]->isDead() && !plat[i][x-2])
		{
			plat[i][x-1]->kill();
			tmp=howManEatKing(i,x-2,numPlayer);
			plat[i][x-1]->revive();
			if (tmp>=cpt)
				cpt=tmp+1;
		}
	}

	for(int x=j; x<len; x++)
	{
		if(x<len-2 && x<len-2 && plat[i][x+1] && plat[i][x+1]->getPlayer()!=numPlayer && !plat[i][x+1]->isDead() && !plat[i][x+2])
		{
			plat[i][x+1]->kill();
			tmp=howManEatKing(i,x+2,numPlayer);
			plat[i][x+1]->revive();
			if (tmp>=cpt)
				cpt=tmp+1;
		}
	}


	return cpt;
}

bool Plateau::playerAlive(int numPlayer)
{
	for (int i=0;i<len;i++)
	{
		for (int j = 0; j < len; j++)
		{
			if(plat[i][j] && plat[i][j]->getPlayer()==numPlayer)
			{
					return true;
			}
		}
	}

	return false;
}

int Plateau::playerCount(int numPlayer)
{
	int cpt=0;
	for (int i=0;i<len;i++)
	{
		for (int j = 0; j < len; j++)
		{
			if(plat[i][j])
			{
				if (plat[i][j]->getPlayer()==numPlayer)
				{
					cpt+=1;
				}
			}
		}
	}
	return cpt;
}

int Plateau::eval(int numPlayer)
{
	if (numPlayer==1)
		return playerCount(numPlayer)-playerCount(numPlayer+1);
	else
		return  playerCount(numPlayer)-playerCount(numPlayer-1);
}

Pion*** Plateau::copy()
{
	Pion*** platCopy ;
	platCopy= new Pion **[len];

	for(int i=0;i<len;i++)
	{
		platCopy[i]= new Pion *[len];
		for (int j=0; j<len; j++)
		{
			if (plat[i][j])
			{	
				platCopy[i][j]=new Pion (plat[i][j]->isDead(),plat[i][j]->isKing(),plat[i][j]->getPlayer());
			}
			else
			{
				platCopy[i][j]=NULL;
			}
		}
	}

	return platCopy;
}

void Plateau::replacePlat(Pion*** platCopy)
{
	for(int i=0;i<len;i++)
	{
		for (int j=0; j<len; j++)
		{
			if (platCopy[i][j]==0)
			{	
				plat[i][j]=NULL;

			}
			else
			{
				plat[i][j]=new Pion (platCopy[i][j]->isDead(),platCopy[i][j]->isKing(),platCopy[i][j]->getPlayer());
			}
		}
	}
}


int Plateau::platPlayer(int x, int y)
{
	if (plat[x][y])
		return plat[x][y]->getPlayer();
	else
		return -1;
}

bool Plateau::platKing(int x, int y)
{
	if (plat[x][y])
		return plat[x][y]->isKing();
	else
		return 0;
}


void Plateau::searchPlayer(int& x,int& y, int numPlayer)
{
//	cerr<<"searchPlayer :"<<x<<":"<<y<<":"<<numPlayer<<endl;
	if(x<0)
	{
		x+=1;
	}
	while (x<len)
	{
		y+=1;
		if(y>=len)
		{
			y=0;
			x+=1;
		}
		if(x>=len)
		{
			break;
		}
		if(platPlayer(x,y)==numPlayer)
		{
	//		cerr<<"searchPlayer good :"<<x<<":"<<y<<":"<<platPlayer(x,y)<<endl;
			return;
		}
/*		else
		{
			cerr<<"searchPlayer else :"<<x<<":"<<y<<":"<<platPlayer(x,y)<<endl;
		}
*/	}


//	cerr<<"searchPlayer wrong :"<<x<<":"<<y<<":"<<numPlayer<<endl;
	x=-1;
	y=-1;

}
































void Plateau::afficheTest()
{
//	system("clear");
	
//	printf("\033[H\033[2J");
	cout<<"------------------------------------------------------------------------------------------------"<<endl;
	for (int i=0;i<len; i++)
	{
		cout<<" ";
		for (int j=0;j<len;j++)
		{
			if(plat[i][j])
			{
				cout<<"|";//<<plat[i][j]->getPlayer();
				if (plat[i][j]->getPlayer()==1)
				{
					if (plat[i][j]->isDead())
						printf("\033[%sm","41");
					else
						printf("\033[%sm","47");
					printf("\033[%sm","30");
					if (plat[i][j]->isKing())
						cout<<"K";
					else
						cout<<"P";
					printf("\033[%sm","0");
				}
				else
				{	
					if (plat[i][j]->isDead())
						printf("\033[%sm","44");
					else
					printf("\033[%sm","40");
					if (plat[i][j]->isKing())
						cout<<"K";
					else
						cout<<"P";
					printf("\033[%sm","0");
				}
			}
			else
				cout<<"| ";
		}
		cout<<"| : "<<i<<endl;
	}

	for (int i=0;i<len+2;i++)
		cout<<"--";
	cout<<endl<<" |";
	for (int i='A';i<'A'+len;i++)
	{
		cout<<(char) i<<"|";
	}
	cout<<endl;
}


void Plateau::afficheTestBis()
{
	cout<<"+++++++++++++++++++++++++++++++++++++++++++++"<<endl;

	for (int i = 0; i < len; i++)
	{
		for(int j=0; j<len; j++)
		{
			cout<<"|"<<plat[i][j];
		}
		cout<<endl;
	}
	cout<<"+++++++++++++++++++++++++++++++++++++++++++++"<<endl;

}