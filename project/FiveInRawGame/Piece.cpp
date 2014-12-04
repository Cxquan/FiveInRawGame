#include "Piece.h"

using namespace std;

Piece::Piece(int x, int y, int type)
{
	this->x = x;
	this->y = y;
	this->type = type;
	if (type == 1)
	{
		symble = 10;
	}
	else if (type == 2)
	{
		symble = 11;
	}
}

Piece::Piece(int x, int y, int type, int symble)
{
	this->x = x;
	this->y = y;
	this->type = type;
	this->symble = symble;
}