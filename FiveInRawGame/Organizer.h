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
	int mode;//����ģʽ��0���ˣ�1�˻���
	int turn;//��ǰ���巽:1�ڷ���2�׷���
	int winer;//ʤ��
};

#endif