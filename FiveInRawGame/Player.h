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
	int type;//�ڷ�or�׷�
	//��¼������
	//��¼�����������֣���

};

#endif