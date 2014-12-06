#ifndef AIPlayer_H
#define AIPlayer_H

#include "Chessboard.h"
#include "Judger.h"
#include "Piece.h"
#include <cmath>

class AIPlayer {
public:
	AIPlayer(int type);
	~AIPlayer();

	//落子函数
	void placePiece(Chessboard& board, Piece& piece);
	//计算棋盘分数，最大的为最可能的落点
	Piece getMaxScorePiece(Chessboard& board, Judger& judger);

	//情况一： ●●●●
	void four(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade);
	//情况二： ●●  ●●  或 ●  ●●● 或 ●●●  ●
	void twoBtwo(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade);
	//情况三： ●●●
	void three(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade);
	//情况四： ●●  ●或●  ●●
	void twoBone(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade);
	
	//情况五： ○●空●评定处●
	void twoBonePone(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k);
	//情况六： ○空● 评定处●●
	void oneBonePtwo(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k);
	//情况七： ○●评定处●空●
	void twoPoneBone(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k);
	//情况八： ○评定处●空●●
	void onePoneBtwo(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k);
	//情况九： ●●
	void two(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j);
	//情况十： ●  ● 
	void oneBone(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j);
	//情况十一： ●
	void one(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j);

private:
	int type;//白方
};

#endif