#ifndef Organizer_H
#define Organizer_H

#include "Judger.h"
#include "Screener.h"
#include "AIPlayer.h"
#include "Player.h"

#include "Chessboard.h"
#include "Piece.h"

class Organizer {
public:
	Organizer();
	~Organizer();

	void startGame();
	Piece& receiveInput();
	bool isPlayAgain();

private:
	bool isValidInput(const char& x, const char& y);
};

#endif