#ifndef AIPlayer_H
#define AIPlayer_H

#include "Chessboard.h"
#include "Judger.h"
#include "Piece.h"

class AIPlayer {
public:
	AIPlayer(int type);
	~AIPlayer();

	//落子函数
	void placePiece(Chessboard& board, Piece& piece);
	//计算棋盘分数，最大的为最可能的落点
	Piece getMaxScorePiece(Chessboard& board, Judger& judger);

private:
	int type;//白方
};

#endif