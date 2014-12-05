#ifndef Judger_H
#define Judger_H

#include "Piece.h"
#include "Chessboard.h"
#include "Player.h"
#include <iostream>

class Judger {
public:
	Judger();
	~Judger();

	//判断落子位置是否合规：界内、空位
	bool isValidPosition(Chessboard& board, Piece& piece);
	bool isWin(Chessboard& board, Player& player);
	bool isWin(Chessboard& board, const int turn);
	bool isForbidden(Chessboard& board, Piece& piece);
	bool isaDraw(Chessboard& board);

};

#endif