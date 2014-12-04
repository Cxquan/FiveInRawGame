#include "AIPlayer.h"

using namespace std;

AIPlayer::AIPlayer(int type)
{
	this->type = type;
}

AIPlayer::~AIPlayer()
{
}

int AIPlayer::getType()
{
	return type;
}