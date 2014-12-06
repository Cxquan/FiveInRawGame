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
	for (int i = 0; i < CHESS_SIZE; i++)
	{
		for (int j = 0; j < CHESS_SIZE; j++)
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

	//便利棋盘，构建各点得分,每种情况都需对黑子(1)&白子(2)进行评分
	for (int i = 0; i < CHESS_SIZE; i++)
	{
		for (int j = 0; j < CHESS_SIZE; j++)
		{
			//情况一： ●●●●
			four(board, score, 1, i, j, 1000000);
			four(board, score, 2, i, j, 5000000);

			//情况二： ●●  ●●  或 ●  ●●● 或 ●●●  ●
			twoBtwo(board, score, 1, i, j, 1000000);
			twoBtwo(board, score, 2, i, j, 5000000);

			//情况三： ●●●
			three(board, score, 1, i, j, 30000);
			three(board, score, 2, i, j, 100000);

			//情况四： ●●  ●或●  ●●
			twoBone(board, score, 1, i, j, 30000);
			twoBone(board, score, 2, i, j, 100000);

			for (int k = 0; k <= 3; k++)
			{
				//情况五： ○●空●评定处●
				twoBonePone(board, score, 1, 2, i, j, k);
				twoBonePone(board, score, 2, 1, i, j, k);

				//情况六： ○空● 评定处●●
				oneBonePtwo(board, score, 1, 2, i, j, k);
				oneBonePtwo(board, score, 2, 1, i, j, k);

				//情况七： ○●评定处●空●
				twoPoneBone(board, score, 1, 2, i, j, k);
				twoPoneBone(board, score, 2, 1, i, j, k);

				//情况八： ○评定处●空●●
				onePoneBtwo(board, score, 1, 2, i, j, k);
				onePoneBtwo(board, score, 2, 1, i, j, k);
			}

			//情况九： ●●
			two(board, score, 1, i, j);
			two(board, score, 2, i, j);

			//情况十： ●  ● 
			oneBone(board, score, 1, i, j);
			oneBone(board, score, 2, i, j);

			//情况十一： ●
			one(board, score, 1, i, j);
			one(board, score, 2, i, j);
		}
	}
	
	//获取得分最大的点
	Piece piece;
	int maxScore = -1;
	for (int i = 0; i < CHESS_SIZE;i++)
	{
		for (int j = 0; j < CHESS_SIZE;j++)
		{
			//如果该点已经有棋子，则得分置零
			if (board.getType(i, j) != 0) { score[i][j] = 0; }
			if (score[i][j] > maxScore)
			{
				maxScore = score[i][j];
				piece.setVal(i, j, 2);//type为白色
			}
		}
	}
	return piece;
}

//情况一： ●●●●
void AIPlayer::four(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade)
{
	if (board.getType(i, j) == type && board.getType(i, j + 1) == type && board.getType(i, j + 2) == type && board.getType(i, j + 3) == type && board.getType(i, j + 4) == 0)
	{//行
		if (j + 4 < CHESS_SIZE)	{ score[i][j + 4] += grade; }
	}
	if (board.getType(i, j) == 0 && board.getType(i, j + 1) == type && board.getType(i, j + 2) == type && board.getType(i, j + 3) == type && board.getType(i, j + 4) == type)
	{//行
		score[i][j] += grade;
	}
	if (board.getType(i, j) == type && board.getType(i + 1, j) == type && board.getType(i + 2, j) == type && board.getType(i + 3, j) == type && board.getType(i + 4, j) == 0)
	{//列
		if (i + 4 < CHESS_SIZE)	{ score[i + 4][j] += grade; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j) == type && board.getType(i + 2, j) == type && board.getType(i + 3, j) == type && board.getType(i + 4, j) == type)
	{//列
		score[i][j] += grade;
	}
	if (board.getType(i, j) == type && board.getType(i + 1, j + 1) == type && board.getType(i + 2, j + 2) == type && board.getType(i + 3, j + 3) == type && board.getType(i + 4, j + 4) == 0)
	{//左斜线
		if (i + 4 < CHESS_SIZE && j + 4 < CHESS_SIZE)	{ score[i + 4][j + 4] += grade; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j + 1) == type && board.getType(i + 2, j + 2) == type && board.getType(i + 3, j + 3) == type && board.getType(i + 4, j + 4) == type)
	{//左斜线
		score[i][j] += grade;
	}
	if (board.getType(i, j) == type && board.getType(i + 1, j - 1) == type && board.getType(i + 2, j - 2) == type && board.getType(i + 3, j - 3) == type && board.getType(i + 4, j - 4) == 0)
	{//右斜线
		if (i + 4 < CHESS_SIZE && j - 4 >= 0)	{ score[i + 4][j - 4] += grade; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j - 1) == type && board.getType(i + 2, j - 2) == type && board.getType(i + 3, j - 3) == type && board.getType(i + 4, j - 4) == type)
	{//右斜线
		score[i][j] += grade;
	}
}

//情况二： ●●  ●●  或 ●  ●●● 或 ●●●  ●
void AIPlayer::twoBtwo(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade)
{
	if (((board.getType(i, j) == type) + (board.getType(i, j + 1) == type) + (board.getType(i, j + 2) == type) + (board.getType(i, j + 3) == type) + (board.getType(i, j + 4) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i, j + 1) == 0) + (board.getType(i, j + 2) == 0) + (board.getType(i, j + 3) == 0) + (board.getType(i, j + 4) == 0)) == 1)
	{//行
		score[i][j] += grade;
		if (j + 1 < CHESS_SIZE){ score[i][j + 1] += grade; }
		if (j + 2 < CHESS_SIZE){ score[i][j + 2] += grade; }
		if (j + 3 < CHESS_SIZE){ score[i][j + 3] += grade; }
		if (j + 4 < CHESS_SIZE){ score[i][j + 4] += grade; }
	}
	if (((board.getType(i, j) == type) + (board.getType(i + 1, j) == type) + (board.getType(i + 2, j) == type) + (board.getType(i + 3, j) == type) + (board.getType(i + 4, j) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i + 1, j) == 0) + (board.getType(i + 2, j) == 0) + (board.getType(i + 3, j) == 0) + (board.getType(i + 4, j) == 0)) == 1)
	{//列
		score[i][j] += grade;
		if (i + 1 < CHESS_SIZE){ score[i + 1][j] += grade; }
		if (i + 2 < CHESS_SIZE){ score[i + 2][j] += grade; }
		if (i + 3 < CHESS_SIZE){ score[i + 3][j] += grade; }
		if (i + 4 < CHESS_SIZE){ score[i + 4][j] += grade; }
	}
	if (((board.getType(i, j) == type) + (board.getType(i + 1, j + 1) == type) + (board.getType(i + 2, j + 2) == type) + (board.getType(i + 3, j + 3) == type) + (board.getType(i + 4, j + 4) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i + 1, j + 1) == 0) + (board.getType(i + 2, j + 2) == 0) + (board.getType(i + 3, j + 3) == 0) + (board.getType(i + 4, j + 4) == 0)) == 1)
	{//左斜线
		score[i][j] += grade;
		if (i + 1 < CHESS_SIZE && j + 1 < CHESS_SIZE){ score[i + 1][j + 1] += grade; }
		if (i + 2 < CHESS_SIZE && j + 2 < CHESS_SIZE){ score[i + 2][j + 2] += grade; }
		if (i + 3 < CHESS_SIZE && j + 3 < CHESS_SIZE){ score[i + 3][j + 3] += grade; }
		if (i + 4 < CHESS_SIZE && j + 4 < CHESS_SIZE){ score[i + 4][j + 4] += grade; }
	}
	if (((board.getType(i, j) == type) + (board.getType(i + 1, j - 1) == type) + (board.getType(i + 2, j - 2) == type) + (board.getType(i + 3, j - 3) == type) + (board.getType(i + 4, j - 4) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i + 1, j - 1) == 0) + (board.getType(i + 2, j - 2) == 0) + (board.getType(i + 3, j - 3) == 0) + (board.getType(i + 4, j - 4) == 0)) == 1)
	{//右斜线
		score[i][j] += grade;
		if (i + 1 < CHESS_SIZE && j - 1 >= 0){ score[i + 1][j - 1] += grade; }
		if (i + 2 < CHESS_SIZE && j - 2 >= 0){ score[i + 2][j - 2] += grade; }
		if (i + 3 < CHESS_SIZE && j - 3 >= 0){ score[i + 3][j - 3] += grade; }
		if (i + 4 < CHESS_SIZE && j - 4 >= 0){ score[i + 4][j - 4] += grade; }
	}
}

//情况三： ●●●
void AIPlayer::three(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade)
{
	if ((board.getType(i, j) == 0) && (board.getType(i, j + 1) == type) && (board.getType(i, j + 2) == type) && (board.getType(i, j + 3) == type) && (board.getType(i, j + 4) == 0))
	{//行
		score[i][j] += grade;
		if (j + 4 < CHESS_SIZE) { score[i][j + 4] += grade; }
	}
	if ((board.getType(i, j) == 0) && (board.getType(i + 1, j) == type) && (board.getType(i + 2, j) == type) && (board.getType(i + 3, j) == type) && (board.getType(i + 4, j) == 0))
	{//列
		score[i][j] += grade;
		if (i + 4 < CHESS_SIZE) { score[i + 4][j] += grade; }
	}
	if ((board.getType(i, j) == 0) && (board.getType(i + 1, j + 1) == type) && (board.getType(i + 2, j + 2) == type) && (board.getType(i + 3, j + 3) == type) && (board.getType(i + 4, j + 4) == 0))
	{//左斜线
		score[i][j] += grade;
		if (i + 4 < CHESS_SIZE && j + 4 < CHESS_SIZE) { score[i + 4][j + 4] += grade; }
	}
	if ((board.getType(i, j) == 0) && (board.getType(i + 1, j - 1) == type) && (board.getType(i + 2, j - 2) == type) && (board.getType(i + 3, j - 3) == type) && (board.getType(i + 4, j - 4) == 0))
	{//右斜线
		score[i][j] += grade;
		if (i + 4 < CHESS_SIZE && j - 4 >= 0) { score[i + 4][j - 4] += grade; }
	}
}

//情况四： ●●  ●或●  ●●
void AIPlayer::twoBone(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade)
{
	if (board.getType(i, j - 1) == 0 && board.getType(i, j + 4) == 0
		&& ((board.getType(i, j) == type) + (board.getType(i, j + 1) == type) + (board.getType(i, j + 2) == type) + (board.getType(i, j + 3) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i, j + 1) == 0) + (board.getType(i, j + 2) == 0) + (board.getType(i, j + 3) == 0)) == 1)
	{//行
		score[i][j] += grade;
		if (j + 1 < CHESS_SIZE) { score[i][j + 1] += grade; }
		if (j + 2 < CHESS_SIZE) { score[i][j + 2] += grade; }
		if (j + 3 < CHESS_SIZE) { score[i][j + 3] += grade; }
	}
	if (board.getType(i - 1, j) == 0 && board.getType(i + 4, j) == 0
		&& ((board.getType(i, j) == type) + (board.getType(i + 1, j) == type) + (board.getType(i + 2, j) == type) + (board.getType(i + 3, j) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i + 1, j) == 0) + (board.getType(i + 2, j) == 0) + (board.getType(i + 3, j) == 0)) == 1)
	{//列
		score[i][j] += grade;
		if (i + 1 < CHESS_SIZE) { score[i + 1][j] += grade; }
		if (i + 2 < CHESS_SIZE) { score[i + 2][j] += grade; }
		if (i + 3 < CHESS_SIZE) { score[i + 3][j] += grade; }

	}
	if (board.getType(i - 1, j - 1) == 0 && board.getType(i + 4, j + 4) == 0
		&& ((board.getType(i, j) == type) + (board.getType(i + 1, j + 1) == type) + (board.getType(i + 2, j + 2) == type) + (board.getType(i + 3, j + 3) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i + 1, j + 1) == 0) + (board.getType(i + 2, j + 2) == 0) + (board.getType(i + 3, j + 3) == 0)) == 1)
	{//左斜线
		score[i][j] += grade;
		if (i + 1 < CHESS_SIZE && j + 1 < CHESS_SIZE) { score[i + 1][j + 1] += grade; }
		if (i + 2 < CHESS_SIZE && j + 1 < CHESS_SIZE) { score[i + 2][j + 2] += grade; }
		if (i + 3 < CHESS_SIZE && j + 1 < CHESS_SIZE) { score[i + 3][j + 3] += grade; }

	}
	if (board.getType(i - 1, j + 1) == 0 && board.getType(i + 4, j - 4) == 0
		&& ((board.getType(i, j) == type) + (board.getType(i + 1, j - 1) == type) + (board.getType(i + 2, j - 2) == type) + (board.getType(i + 3, j - 3) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i + 1, j - 1) == 0) + (board.getType(i + 2, j - 2) == 0) + (board.getType(i + 3, j - 3) == 0)) == 1)
	{//右斜线
		score[i][j] += grade;
		if (i + 1 < CHESS_SIZE && j - 1 >= 0) { score[i + 1][j - 1] += grade; }
		if (i + 2 < CHESS_SIZE && j - 2 >= 0) { score[i + 2][j - 2] += grade; }
		if (i + 3 < CHESS_SIZE && j - 3 >= 0) { score[i + 3][j - 3] += grade; }

	}
}

//情况五： ○●空●评定处●
void AIPlayer::twoBonePone(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k)
{
	if (board.getType(i, j - 4) == aType //行
		&& ((board.getType(i, j - 3) == bType) + (board.getType(i, j - 2) == bType) + (board.getType(i, j - 1) == bType) + (board.getType(i, j + 1) == bType)) == k
		&& ((board.getType(i, j - 3) == 0) + (board.getType(i, j - 2) == 0) + (board.getType(i, j - 1) == 0) + (board.getType(i, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i, j + 4) == aType //行
		&& ((board.getType(i, j + 3) == bType) + (board.getType(i, j + 2) == bType) + (board.getType(i, j + 1) == bType) + (board.getType(i, j - 1) == bType)) == k
		&& ((board.getType(i, j + 3) == 0) + (board.getType(i, j + 2) == 0) + (board.getType(i, j + 1) == 0) + (board.getType(i, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 4, j) == aType //列
		&& ((board.getType(i - 3, j) == bType) + (board.getType(i - 2, j) == bType) + (board.getType(i - 1, j) == bType) + (board.getType(i + 1, j) == bType)) == k
		&& ((board.getType(i - 3, j) == 0) + (board.getType(i - 2, j) == 0) + (board.getType(i - 1, j) == 0) + (board.getType(i + 1, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 4, j) == aType //列
		&& ((board.getType(i + 3, j) == bType) + (board.getType(i + 2, j) == bType) + (board.getType(i + 1, j) == bType) + (board.getType(i - 1, j) == bType)) == k
		&& ((board.getType(i + 3, j) == 0) + (board.getType(i + 2, j) == 0) + (board.getType(i + 1, j) == 0) + (board.getType(i - 1, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 4, j - 4) == aType //左斜线
		&& ((board.getType(i - 3, j - 3) == bType) + (board.getType(i - 2, j - 2) == bType) + (board.getType(i - 1, j - 1) == bType) + (board.getType(i + 1, j + 1) == bType)) == k
		&& ((board.getType(i - 3, j - 3) == 0) + (board.getType(i - 2, j - 2) == 0) + (board.getType(i - 1, j - 1) == 0) + (board.getType(i + 1, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 4, j + 4) == aType //左斜线
		&& ((board.getType(i + 3, j + 3) == bType) + (board.getType(i + 2, j + 2) == bType) + (board.getType(i + 1, j + 1) == bType) + (board.getType(i - 1, j - 1) == bType)) == k
		&& ((board.getType(i + 3, j + 3) == 0) + (board.getType(i + 2, j + 2) == 0) + (board.getType(i + 1, j + 1) == 0) + (board.getType(i - 1, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 4, j + 4) == aType //右斜线
		&& ((board.getType(i - 3, j + 3) == bType) + (board.getType(i - 2, j + 2) == bType) + (board.getType(i - 1, j + 1) == bType) + (board.getType(i + 1, j - 1) == bType)) == k
		&& ((board.getType(i - 3, j + 3) == 0) + (board.getType(i - 2, j + 2) == 0) + (board.getType(i - 1, j + 1) == 0) + (board.getType(i + 1, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 4, j - 4) == aType //右斜线
		&& ((board.getType(i + 3, j - 3) == bType) + (board.getType(i + 2, j - 2) == bType) + (board.getType(i + 1, j - 1) == bType) + (board.getType(i - 1, j + 1) == bType)) == k
		&& ((board.getType(i + 3, j - 3) == 0) + (board.getType(i + 2, j - 2) == 0) + (board.getType(i + 1, j - 1) == 0) + (board.getType(i - 1, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
}

//情况六： ○空● 评定处●●
void AIPlayer::oneBonePtwo(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k)
{
	if (board.getType(i, j - 3) == aType //行
		&& ((board.getType(i, j - 1) == bType) + (board.getType(i, j - 2) == bType) + (board.getType(i, j + 2) == bType) + (board.getType(i, j + 1) == bType)) == k
		&& ((board.getType(i, j - 1) == 0) + (board.getType(i, j - 2) == 0) + (board.getType(i, j + 2) == 0) + (board.getType(i, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i, j + 3) == aType //行
		&& ((board.getType(i, j + 1) == bType) + (board.getType(i, j + 2) == bType) + (board.getType(i, j - 2) == bType) + (board.getType(i, j - 1) == bType)) == k
		&& ((board.getType(i, j + 1) == 0) + (board.getType(i, j + 2) == 0) + (board.getType(i, j - 2) == 0) + (board.getType(i, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 3, j) == aType //列
		&& ((board.getType(i - 1, j) == bType) + (board.getType(i - 2, j) == bType) + (board.getType(i + 2, j) == bType) + (board.getType(i + 1, j) == bType)) == k
		&& ((board.getType(i - 1, j) == 0) + (board.getType(i - 2, j) == 0) + (board.getType(i + 2, j) == 0) + (board.getType(i + 1, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 3, j) == aType //列
		&& ((board.getType(i + 1, j) == bType) + (board.getType(i + 2, j) == bType) + (board.getType(i - 2, j) == bType) + (board.getType(i - 1, j) == bType)) == k
		&& ((board.getType(i + 1, j) == 0) + (board.getType(i + 2, j) == 0) + (board.getType(i - 2, j) == 0) + (board.getType(i - 1, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 3, j - 3) == aType //左斜线
		&& ((board.getType(i - 1, j - 1) == bType) + (board.getType(i - 2, j - 2) == bType) + (board.getType(i + 2, j + 2) == bType) + (board.getType(i + 1, j + 1) == bType)) == k
		&& ((board.getType(i - 1, j - 1) == 0) + (board.getType(i - 2, j - 2) == 0) + (board.getType(i + 2, j + 2) == 0) + (board.getType(i + 1, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 3, j + 3) == aType //左斜线
		&& ((board.getType(i + 1, j + 1) == bType) + (board.getType(i + 2, j + 2) == bType) + (board.getType(i - 2, j - 2) == bType) + (board.getType(i - 1, j - 1) == bType)) == k
		&& ((board.getType(i + 1, j + 1) == 0) + (board.getType(i + 2, j + 2) == 0) + (board.getType(i - 2, j - 2) == 0) + (board.getType(i - 1, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 3, j + 3) == aType //右斜线
		&& ((board.getType(i - 1, j + 1) == bType) + (board.getType(i - 2, j + 2) == bType) + (board.getType(i + 2, j - 2) == bType) + (board.getType(i + 1, j - 1) == bType)) == k
		&& ((board.getType(i - 1, j + 1) == 0) + (board.getType(i - 2, j + 2) == 0) + (board.getType(i + 2, j - 2) == 0) + (board.getType(i + 1, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 3, j - 3) == aType //右斜线
		&& ((board.getType(i + 1, j - 1) == bType) + (board.getType(i + 2, j - 2) == bType) + (board.getType(i - 2, j + 2) == bType) + (board.getType(i - 1, j + 1) == bType)) == k
		&& ((board.getType(i + 1, j - 1) == 0) + (board.getType(i + 2, j - 2) == 0) + (board.getType(i - 2, j + 2) == 0) + (board.getType(i - 1, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
}

//情况七： ○●评定处●空●
void AIPlayer::twoPoneBone(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k)
{
	if (board.getType(i, j - 2) == aType //行
		&& ((board.getType(i, j + 3) == bType) + (board.getType(i, j + 2) == bType) + (board.getType(i, j + 1) == bType) + (board.getType(i, j - 1) == bType)) == k
		&& ((board.getType(i, j + 3) == 0) + (board.getType(i, j + 2) == 0) + (board.getType(i, j + 1) == 0) + (board.getType(i, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i, j + 2) == aType //行
		&& ((board.getType(i, j - 3) == bType) + (board.getType(i, j - 2) == bType) + (board.getType(i, j - 1) == bType) + (board.getType(i, j + 1) == bType)) == k
		&& ((board.getType(i, j - 3) == 0) + (board.getType(i, j - 2) == 0) + (board.getType(i, j - 1) == 0) + (board.getType(i, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 2, j) == aType //列
		&& ((board.getType(i + 3, j) == bType) + (board.getType(i + 2, j) == bType) + (board.getType(i + 1, j) == bType) + (board.getType(i - 1, j) == bType)) == k
		&& ((board.getType(i + 3, j) == 0) + (board.getType(i + 2, j) == 0) + (board.getType(i + 1, j) == 0) + (board.getType(i - 1, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 2, j) == aType //列
		&& ((board.getType(i - 3, j) == bType) + (board.getType(i - 2, j) == bType) + (board.getType(i - 1, j) == bType) + (board.getType(i + 1, j) == bType)) == k
		&& ((board.getType(i - 3, j) == 0) + (board.getType(i - 2, j) == 0) + (board.getType(i - 1, j) == 0) + (board.getType(i + 1, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 2, j - 2) == aType //左斜线
		&& ((board.getType(i + 3, j + 3) == bType) + (board.getType(i + 2, j + 2) == bType) + (board.getType(i + 1, j + 1) == bType) + (board.getType(i - 1, j - 1) == bType)) == k
		&& ((board.getType(i + 3, j + 3) == 0) + (board.getType(i + 2, j + 2) == 0) + (board.getType(i + 1, j + 1) == 0) + (board.getType(i - 1, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 2, j + 2) == aType //左斜线
		&& ((board.getType(i - 3, j - 3) == bType) + (board.getType(i - 2, j - 2) == bType) + (board.getType(i - 1, j - 1) == bType) + (board.getType(i + 1, j + 1) == bType)) == k
		&& ((board.getType(i - 3, j - 3) == 0) + (board.getType(i - 2, j - 2) == 0) + (board.getType(i - 1, j - 1) == 0) + (board.getType(i + 1, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 2, j + 2) == aType //右斜线
		&& ((board.getType(i + 3, j - 3) == bType) + (board.getType(i + 2, j - 2) == bType) + (board.getType(i + 1, j - 1) == bType) + (board.getType(i - 1, j + 1) == bType)) == k
		&& ((board.getType(i + 3, j - 3) == 0) + (board.getType(i + 2, j - 2) == 0) + (board.getType(i + 1, j - 1) == 0) + (board.getType(i - 1, j + 1) == 0)) == 4 - k)
		
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 2, j - 2) == aType //右斜线
		&& ((board.getType(i - 3, j + 3) == bType) + (board.getType(i - 2, j + 2) == bType) + (board.getType(i - 1, j + 1) == bType) + (board.getType(i + 1, j - 1) == bType)) == k
		&& ((board.getType(i - 3, j + 3) == 0) + (board.getType(i - 2, j + 2) == 0) + (board.getType(i - 1, j + 1) == 0) + (board.getType(i + 1, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
}

//情况八： ○评定处●空●●
void AIPlayer::onePoneBtwo(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k)
{
	if (board.getType(i, j - 1) == aType //行
		&& ((board.getType(i, j + 1) == bType) + (board.getType(i, j + 2) == bType) + (board.getType(i, j + 3) == bType) + (board.getType(i, j + 4) == bType)) == k
		&& ((board.getType(i, j + 1) == 0) + (board.getType(i, j + 2) == 0) + (board.getType(i, j + 3) == 0) + (board.getType(i, j + 4) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i, j + 1) == aType //行
		&& ((board.getType(i, j - 1) == bType) + (board.getType(i, j - 2) == bType) + (board.getType(i, j - 3) == bType) + (board.getType(i, j - 4) == bType)) == k
		&& ((board.getType(i, j - 1) == 0) + (board.getType(i, j - 2) == 0) + (board.getType(i, j - 3) == 0) + (board.getType(i, j - 4) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 1, j) == aType //列
		&& ((board.getType(i + 1, j) == bType) + (board.getType(i + 2, j) == bType) + (board.getType(i + 3, j) == bType) + (board.getType(i + 4, j) == bType)) == k
		&& ((board.getType(i + 1, j) == 0) + (board.getType(i + 2, j) == 0) + (board.getType(i + 3, j) == 0) + (board.getType(i + 4, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 1, j) == aType //列
		&& ((board.getType(i - 1, j) == bType) + (board.getType(i - 2, j) == bType) + (board.getType(i - 3, j) == bType) + (board.getType(i - 4, j) == bType)) == k
		&& ((board.getType(i - 1, j) == 0) + (board.getType(i - 2, j) == 0) + (board.getType(i - 3, j) == 0) + (board.getType(i - 4, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 1, j - 1) == aType //左斜线
		&& ((board.getType(i + 1, j + 1) == bType) + (board.getType(i + 2, j + 2) == bType) + (board.getType(i + 3, j + 3) == bType) + (board.getType(i + 4, j + 4) == bType)) == k
		&& ((board.getType(i + 1, j + 1) == 0) + (board.getType(i + 2, j + 2) == 0) + (board.getType(i + 3, j + 3) == 0) + (board.getType(i + 4, j + 4) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 1, j + 1) == aType //左斜线
		&& ((board.getType(i - 1, j - 1) == bType) + (board.getType(i - 2, j - 2) == bType) + (board.getType(i - 3, j - 3) == bType) + (board.getType(i - 4, j - 4) == bType)) == k
		&& ((board.getType(i - 1, j - 1) == 0) + (board.getType(i - 2, j - 2) == 0) + (board.getType(i - 3, j - 3) == 0) + (board.getType(i - 4, j - 4) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 1, j + 1) == aType //右斜线
		&& ((board.getType(i + 1, j - 1) == bType) + (board.getType(i + 2, j - 2) == bType) + (board.getType(i + 3, j - 3) == bType) + (board.getType(i + 4, j - 4) == bType)) == k
		&& ((board.getType(i + 1, j - 1) == 0) + (board.getType(i + 2, j - 2) == 0) + (board.getType(i + 3, j - 3) == 0) + (board.getType(i + 4, j - 4) == 0)) == 4 - k)

	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 1, j - 1) == aType //右斜线
		&& ((board.getType(i - 1, j + 1) == bType) + (board.getType(i - 2, j + 2) == bType) + (board.getType(i - 3, j + 3) == bType) + (board.getType(i - 4, j + 4) == bType)) == k
		&& ((board.getType(i - 1, j + 1) == 0) + (board.getType(i - 2, j + 2) == 0) + (board.getType(i - 3, j + 3) == 0) + (board.getType(i - 4, j + 4) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
}

//情况九： ●●
void AIPlayer::two(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j)
{
	if (board.getType(i, j) == 0 && board.getType(i, j + 1) == 0 && board.getType(i, j + 2) == type && board.getType(i, j + 3) == type && board.getType(i, j + 4) == 0 && board.getType(i, j + 5) == 0)
	{//行
		score[i][j] = 100;
		if (j + 1 < CHESS_SIZE)	{ score[i][j + 1] += 1000; }
		if (j + 4 < CHESS_SIZE)	{ score[i][j + 4] += 100; }
		if (j + 5 < CHESS_SIZE)	{ score[i][j + 5] += 1000; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j) == 0 && board.getType(i + 2, j) == type && board.getType(i + 3, j) == type && board.getType(i + 4, j) == 0 && board.getType(i + 5, j) == 0)
	{//列
		score[i][j] = 100;
		if (i + 1 < CHESS_SIZE)	{ score[i + 1][j] += 1000; }
		if (i + 4 < CHESS_SIZE)	{ score[i + 4][j] += 100; }
		if (i + 5 < CHESS_SIZE)	{ score[i + 5][j] += 1000; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j + 1) == 0 && board.getType(i + 2, j + 2) == type && board.getType(i + 3, j + 3) == type && board.getType(i + 4, j + 4) == 0 && board.getType(i + 5, j + 5) == 0)
	{//左斜线
		score[i][j] = 100;
		if (i + 1 < CHESS_SIZE && j + 1 < CHESS_SIZE)	{ score[i + 1][j + 1] += 1000; }
		if (i + 4 < CHESS_SIZE && j + 4 < CHESS_SIZE)	{ score[i + 4][j + 4] += 100; }
		if (i + 5 < CHESS_SIZE && j + 5 < CHESS_SIZE)	{ score[i + 5][j + 5] += 1000; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j - 1) == 0 && board.getType(i + 2, j - 2) == type && board.getType(i + 3, j - 3) == type && board.getType(i + 4, j - 4) == 0 && board.getType(i + 5, j - 5) == 0)
	{//右斜线
		score[i][j] = 100;
		if (i + 1 < CHESS_SIZE && j - 1 >= 0)	{ score[i + 1][j - 1] += 1000; }
		if (i + 4 < CHESS_SIZE && j - 4 >= 0)	{ score[i + 4][j - 4] += 100; }
		if (i + 5 < CHESS_SIZE && j - 5 >= 0)	{ score[i + 5][j - 5] += 1000; }
	}
}

//情况十： ●  ● 
void AIPlayer::oneBone(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j)
{
	if (board.getType(i, j) == 0 && board.getType(i, j + 1) == type && board.getType(i, j + 2) == 0 && board.getType(i, j + 3) == type && board.getType(i, j + 4) == 0)
	{//行
		if (j + 2 < CHESS_SIZE)	{ score[i][j + 2] += 1000; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j) == type && board.getType(i + 2, j) == 0 && board.getType(i + 3, j) == type && board.getType(i + 4, j) == 0)
	{//列
		if (i + 2 < CHESS_SIZE)	{ score[i + 2][j] += 1000; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j + 1) == type && board.getType(i + 2, j + 2) == 0 && board.getType(i + 3, j + 3) == type && board.getType(i + 4, j + 4) == 0)
	{//左斜线
		if (i + 2 < CHESS_SIZE && j + 2 < CHESS_SIZE)	{ score[i + 2][j + 2] += 1000; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j - 1) == type && board.getType(i + 2, j - 2) == 0 && board.getType(i + 3, j - 3) == type && board.getType(i + 4, j - 4) == 0)
	{//右斜线
		if (i + 1 < CHESS_SIZE && j - 1 > CHESS_SIZE)	{ score[i + 2][j - 1] += 1000; }
	}
}

//情况十一： ●
void AIPlayer::one(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j)
{
	if (board.getType(i, j) == type && ((board.getType(i, j - 1) == 0) + (board.getType(i, j + 1) == 0) + (board.getType(i - 1, j) == 0) + (board.getType(i + 1, j) == 0)
		+ (board.getType(i + 1, j - 1) == 0) + (board.getType(i -1 , j + 1) == 0) + (board.getType(i - 1, j - 1) == 0) + (board.getType(i + 1, j + 1) == 0)) != 0)
	{
		if (j - 1 >= 0)	{ score[i][j - 1] += 100; }
		if (i - 1 >= 0)	{ score[i - 1][j] += 100; }
		if (j + 1 < CHESS_SIZE)	{ score[i][j + 1] += 100; }
		if (i + 1 < CHESS_SIZE)	{ score[i + 1][j] += 100; }
		if (i + 1 < CHESS_SIZE && j + 1 < CHESS_SIZE) { score[i + 1][j + 1] += 100; }
		if (i + 1 < CHESS_SIZE && j - 1 >= 0) { score[i + 1][j - 1] += 100; }
		if (j + 1 < CHESS_SIZE && i - 1 >= 0) { score[i - 1][j + 1] += 100; }
		if (i - 1 >= 0 && j - 1 >= 0) { score[i - 1][j - 1] += 100; }
	}
}