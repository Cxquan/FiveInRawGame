#ifndef AIPlayer_H
#define AIPlayer_H

#include "Chessboard.h"
#include "Judger.h"
#include "Piece.h"

class AIPlayer {
public:
	AIPlayer(int type);
	~AIPlayer();

	//���Ӻ���
	void placePiece(Chessboard& board, Piece& piece);
	//�������̷���������Ϊ����ܵ����
	Piece getMaxScorePiece(Chessboard& board, Judger& judger);

private:
	int type;//�׷�
};

#endif