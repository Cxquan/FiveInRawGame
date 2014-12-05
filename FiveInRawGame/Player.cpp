#include "Player.h"

using namespace std;

Player::Player(int type)
{
	this->type = type;
}

Player::Player()
{
}

Player::~Player()
{
}

int Player::getType()
{
	return type;
}

void Player::placePiece(Chessboard& board, Piece& piece)
{
	board.setPiece(piece);
}