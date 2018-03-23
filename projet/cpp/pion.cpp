#include "../header/pion.h"

using namespace std;

Pion::Pion()
{
	dead=false;
	king=false;
	player=0;
}

Pion::Pion(int p)
{
	dead=false;
	king=false;
	player=p;
}

Pion::Pion(bool d, bool k, int p)
{
	dead=d;
	king=k;
	player=p;
}

bool Pion::isDead() { return dead;}
bool Pion::isKing() { return king;}
int Pion::getPlayer() { return player;}

void Pion::toKing()
{
	king=true;
}


void Pion::changeDead (bool d)
{
	dead=d;
}

void Pion::changeKing (bool k)
{
	king=k;
}

void Pion::changePlayer (int p)
{
	player =p;
}

void Pion::kill()
{
	dead=true;
}

void Pion::revive()
{
	dead=false;
}
