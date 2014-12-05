#ifndef Player_H
#define Player_H

#include "Chessboard.h"
#include "Piece.h"

class Player {
public:
	Player();
	Player(int type);
	~Player();

	int getType();
	void placePiece(Chessboard& board, Piece& piece);

private:
	int type;//黑方or白方
	//记录悔棋数
	//记录下子数（禁手？）

};

#endif