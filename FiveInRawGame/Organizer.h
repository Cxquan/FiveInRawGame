#ifndef Organizer_H
#define Organizer_H

#include "Judger.h"
#include "Screener.h"
#include "AIPlayer.h"
#include "Player.h"

#include "Chessboard.h"
#include "Piece.h"
#include <string>

class Organizer {
public:
	Organizer();
	~Organizer();

	void startGame();

	void getModeInput(Screener& screener, Chessboard& board);
	Piece getPieceInput(Screener& screener, Chessboard& board, Player& player, Judger& judger);

	bool isPlayAgain(Screener& screener, Chessboard& board);

private:
	int mode;//下棋模式：0人人；1人机；
	int turn;//当前下棋方:1黑方；2白方；
	int winer;//胜者
};

#endif