#include "Piece.h"

using namespace std;


Piece::Piece()
{
}

Piece::~Piece()
{

}

Piece::Piece(int x, int y, int type)
{
	this->x = x;
	this->y = y;
	this->type = type;
	if (type == 1)//黑子
	{
		symble = 9;
	}
	else if (type == 2)//白子
	{
		symble = 10;
	}
}

Piece::Piece(int x, int y, int type, int symble)
{
	this->x = x;
	this->y = y;
	this->type = type;
	this->symble = symble;
}

void Piece::setVal(int x, int y, int type)
{
	this->x = x;
	this->y = y;
	this->type = type;
	if (type == 1)//黑子
	{
		symble = 9;
	}
	else if (type == 2)//白子
	{
		symble = 10;
	}
}

