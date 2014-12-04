#include "Player.h"

using namespace std;

Player::Player(int type)
{
	this->type = type;
}

Player::~Player()
{
}

int Player::getType()
{
	return type;
}