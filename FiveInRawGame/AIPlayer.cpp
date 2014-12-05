#include "AIPlayer.h"

using namespace std;

AIPlayer::AIPlayer(int type)
{
	this->type = type;
}

AIPlayer::~AIPlayer()
{
}

void AIPlayer::placePiece(Chessboard& board, Piece& piece)
{
	board.setPiece(piece);
}

Piece AIPlayer::getMaxScorePiece(Chessboard& board, Judger& judger)
{
	//棋盘各点得分
	int score[CHESS_SIZE][CHESS_SIZE] = { 0 };

	//====初始化得分，越往中间得分越高====
	for (int i = 0; i < CHESS_SIZE;i++)
	{
		for (int j = 0; j < CHESS_SIZE;j++)
		{
			//边缘
			if (i < 3 || i >= CHESS_SIZE - 2 || j < 3 || j >= CHESS_SIZE - 2){ score[i][j] = 1; }
			//次边缘
			if (i >= 3 && i < CHESS_SIZE - 2 && j >= 3 && j < CHESS_SIZE - 2){ score[i][j] = 10; }
			//中间
			if (i >= 5 && i < CHESS_SIZE - 4 && j >= 5 && j < CHESS_SIZE - 4){ score[i][j] = 100; }
		}
	}
	score[7][7] = 1000;

	//便利棋盘，构建各点得分
	for (int i = 0; i < CHESS_SIZE;i++)
	{
		for (int j; j < CHESS_SIZE;j++)
		{

			//情况一： ●●●●
			//情况二： ●●  ●●  或 ●  ●●● 或 ●●●  ●
			//情况三： ●●●
			//情况四： ●●  ●或●  ●●

			for (int k = 0; k <= 3;k++)
			{
				//情况五： ○●空●评定处●
				//情况六： ○空● 评定处●●
				//情况七： ○●评定处●空●
				//情况八： ○评定处●空●●
				//情况九： ●●
				//情况十： ●  ● 
				//情况十一： ●
			}
		}
	}

	Piece piece;
	return piece;
}