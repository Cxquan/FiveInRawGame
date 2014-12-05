#include "Judger.h"

using namespace std;

Judger::Judger()
{
}

Judger::~Judger()
{
}

bool Judger::isValidPosition(Chessboard& board, Piece& piece)
{
	if (piece.x < 0 || piece.x >= CHESS_SIZE || piece.y < 0 || piece.y >= CHESS_SIZE
		|| board.getType(piece.x, piece.y) != 0)
	{
		return false;
	}
	return true;
}

//黑子(type = 1)先下，仅判断黑子禁手
bool Judger::isForbidden(Chessboard& board, Piece& piece)
{
	//棋盘全局的禁手情况，以数字表示：10为成三，100为成四，1000为长连
	int forbid[CHESS_SIZE][CHESS_SIZE] = { 0 };//从forbid34/44/6汇总

	//int forbid3[CHESS_SIZE][CHESS_SIZE] = { 0 };//记录棋盘成三情况,从forbid34汇总
	//int forbid4[CHESS_SIZE][CHESS_SIZE] = { 0 };//记录棋盘成四情况,从forbid44汇总

	//四个方向成三情况：行0，列1，左斜2，右斜3
	int forbid34[4][CHESS_SIZE][CHESS_SIZE] = { 0 };
	//四个方向成四情况：行0，列1，左斜2，右斜3
	int forbid44[4][CHESS_SIZE][CHESS_SIZE] = { 0 };
	//记录棋盘长连情况
	int forbid6[CHESS_SIZE][CHESS_SIZE] = { 0 };

	//遍历棋盘
	for (int i = 0; i < CHESS_SIZE; i++)
	{
		for (int j = 0; j < CHESS_SIZE; j++)
		{
			//==========第一种情况：成三==========
			//行方向
			if ((board.getType(i, j - 4) == 0) && (board.getType(i, j + 2) == 0) 
				&& ((board.getType(i, j - 3) == 1) + (board.getType(i, j - 2) == 1) + (board.getType(i, j - 1) == 1) + (board.getType(i, j) == 1) + (board.getType(i, j + 1) == 1) == 2)
				&& ((board.getType(i, j - 3) == 0) + (board.getType(i, j - 2) == 0) + (board.getType(i, j - 1) == 0) + (board.getType(i, j) == 0) + (board.getType(i, j + 1) == 0) == 3))
			{
				if (j - 3 >= 0){ forbid34[0][i][j - 3] += 10; }
				if (j - 2 >= 0){ forbid34[0][i][j - 2] += 10; }
				if (j - 1 >= 0){ forbid34[0][i][j - 1] += 10; }
				forbid34[0][i][j] += 10;
				if (j + 1 < CHESS_SIZE){ forbid34[0][i][j + 1] += 10; }
			}
			//列方向
			if ((board.getType(i-4, j) == 0) && (board.getType(i+2, j) == 0)
				&& ((board.getType(i - 3, j) == 1) + (board.getType(i - 2, j) == 1) + (board.getType(i - 1, j) == 1) + (board.getType(i, j) == 1) + (board.getType(i + 1, j) == 1) == 2)
				&& ((board.getType(i - 3, j) == 0) + (board.getType(i - 2, j) == 0) + (board.getType(i - 1, j) == 0) + (board.getType(i, j) == 0) + (board.getType(i + 1, j) == 0) == 3))
			{
				if (i - 3 >= 0){ forbid34[1][i - 3][j] += 10; }
				if (i - 2 >= 0){ forbid34[1][i - 2][j] += 10; }
				if (i - 1 >= 0){ forbid34[1][i - 1][j] += 10; }
				forbid34[1][i][j] += 10;
				if (i + 1 < CHESS_SIZE){ forbid34[1][i + 1][j] += 10; }
			}
			//左斜线方向
			if ((board.getType(i - 4, j - 4) == 0) && (board.getType(i + 2, j +2) == 0)
				&& ((board.getType(i - 3, j - 3) == 1) + (board.getType(i - 2, j - 2) == 1) + (board.getType(i - 1, j - 1) == 1) + (board.getType(i, j) == 1) + (board.getType(i + 1, j + 1) == 1) == 2)
				&& ((board.getType(i - 3, j - 3) == 0) + (board.getType(i - 2, j - 2) == 0) + (board.getType(i - 1, j - 1) == 0) + (board.getType(i, j) == 0) + (board.getType(i + 1, j + 1) == 0) == 3))
			{
				if (i - 3 >= 0 && j - 3 >= 0){ forbid34[2][i - 3][j - 3] += 10; }
				if (i - 2 >= 0 && j - 2 >= 0){ forbid34[2][i - 2][j - 2] += 10; }
				if (i - 1 >= 0 && j - 1 >= 0){ forbid34[2][i - 1][j + 1] += 10; }
				forbid34[2][i][j] += 10;
				if (i + 1 < CHESS_SIZE && j + 1 < CHESS_SIZE){ forbid34[3][i + 1][j + 1] += 10; }
			}
			//右斜线方向
			if ((board.getType(i - 4, j + 4) == 0) && (board.getType(i + 2, j - 2) == 0)
				&& ((board.getType(i - 3, j + 3) == 1) + (board.getType(i - 2, j + 2) == 1) + (board.getType(i - 1, j + 1) == 1) + (board.getType(i, j) == 1) + (board.getType(i + 1, j - 1) == 1) == 3)
				&& ((board.getType(i - 3, j + 3) == 0) + (board.getType(i - 2, j + 2) == 0) + (board.getType(i - 1, j + 1) == 0) + (board.getType(i, j) == 0) + (board.getType(i + 1, j - 1) == 0) == 2))
			{
				if (i - 3 >= 0 && j + 3 < CHESS_SIZE){ forbid34[3][i - 3][j + 3] += 10; }
				if (i - 2 >= 0 && j + 2 < CHESS_SIZE){ forbid34[3][i - 2][j + 2] += 10; }
				if (i - 1 >= 0 && j + 1 < CHESS_SIZE){ forbid34[3][i - 1][j + 1] += 10; }
				forbid34[3][i][j] += 100;
				if (i + 1 < CHESS_SIZE && j - 1 >= 0){ forbid34[3][i + 1][j - 1] += 10; }
			}
			
			//==========第二种情况：成四==========
			//行方向
			if (((board.getType(i, j - 3) == 1) + (board.getType(i, j - 2) == 1) + (board.getType(i, j - 1) == 1) + (board.getType(i, j) == 1) + (board.getType(i, j + 1) == 1) == 3)
				&& ((board.getType(i, j - 3) == 0) + (board.getType(i, j - 2) == 0) + (board.getType(i, j - 1) == 0) + (board.getType(i, j) == 0) + (board.getType(i, j + 1) == 0) == 2))
			{
				if (j - 3 >= 0){ forbid44[0][i][j - 3] += 100; }
				if (j - 2 >= 0){ forbid44[0][i][j - 2] += 100; }
				if (j - 1 >= 0){ forbid44[0][i][j - 1] += 100; }
				forbid44[0][i][j] += 100;
				if (j + 1 < CHESS_SIZE){ forbid44[0][i][j + 1] += 100; }
			}
			//列方向
			if (((board.getType(i - 3, j) == 1) + (board.getType(i - 2, j) == 1) + (board.getType(i - 1, j) == 1) + (board.getType(i, j) == 1) + (board.getType(i + 1, j) == 1) == 3)
				&& ((board.getType(i - 3, j) == 0) + (board.getType(i - 2, j) == 0) + (board.getType(i - 1, j) == 0) + (board.getType(i, j) == 0) + (board.getType(i + 1, j) == 0) == 2))
			{
				if (i - 3 >= 0){ forbid44[1][i - 3][j] += 100; }
				if (i - 2 >= 0){ forbid44[1][i - 2][j] += 100; }
				if (i - 1 >= 0){ forbid44[1][i - 1][j] += 100; }
				forbid44[1][i][j] += 100;
				if (i + 1 < CHESS_SIZE){ forbid44[1][i + 1][j] += 100; }
			}
			//左斜线方向
			if (((board.getType(i - 3, j - 3) == 1) + (board.getType(i - 2, j - 2) == 1) + (board.getType(i - 1, j - 1) == 1) + (board.getType(i, j) == 1) + (board.getType(i + 1, j + 1) == 1) == 3)
				&& ((board.getType(i - 3, j - 3) == 0) + (board.getType(i - 2, j - 2) == 0) + (board.getType(i - 1, j - 1) == 0) + (board.getType(i, j) == 0) + (board.getType(i + 1, j + 1) == 0) == 2))
			{
				if (i - 3 >= 0 && j - 3 >= 0){ forbid44[2][i - 3][j - 3] += 100; }
				if (i - 2 >= 0 && j - 2 >= 0){ forbid44[2][i - 2][j - 2] += 100; }
				if (i - 1 >= 0 && j - 1 >= 0){ forbid44[2][i - 1][j + 1] += 100; }
				forbid44[2][i][j] += 100;
				if (i + 1 < CHESS_SIZE && j + 1 < CHESS_SIZE){ forbid44[3][i + 1][j + 1] += 100; }
			}
			//右斜线方向
			if (((board.getType(i - 3, j + 3) == 1) + (board.getType(i - 2, j + 2) == 1) + (board.getType(i - 1, j + 1) == 1) + (board.getType(i, j) == 1) + (board.getType(i + 1, j - 1) == 1) == 3)
				&& ((board.getType(i - 3, j + 3) == 0) + (board.getType(i - 2, j + 2) == 0) + (board.getType(i - 1, j + 1) == 0) + (board.getType(i, j) == 0) + (board.getType(i + 1, j - 1) == 0) == 2))
			{
				if (i - 3 >= 0 && j + 3 < CHESS_SIZE){ forbid44[3][i - 3][j + 3] += 100; }
				if (i - 2 >= 0 && j + 2 < CHESS_SIZE){ forbid44[3][i - 2][j + 2] += 100; }
				if (i - 1 >= 0 && j + 1 < CHESS_SIZE){ forbid44[3][i - 1][j + 1] += 100; }
				forbid44[3][i][j] += 100;
				if (i + 1 < CHESS_SIZE && j - 1 >= 0){ forbid44[3][i + 1][j - 1] += 100; }
			}

			//==========第三种情况：长连==========
			//行方向
			if (((board.getType(i, j) == 1) + (board.getType(i, j + 1) == 1) + (board.getType(i, j + 2) == 1) + (board.getType(i, j + 3) == 1) + (board.getType(i, j + 4) == 1) + (board.getType(i, j + 5) == 1) == 5)
				&& ((board.getType(i, j) == 0) + (board.getType(i, j + 1) == 0) + (board.getType(i, j + 2) == 0) + (board.getType(i, j + 3) == 0) + (board.getType(i, j + 4) == 0) + (board.getType(i, j + 5) == 0) == 1))
			{
				forbid6[i][j] += 1000;
				if (j + 1 < CHESS_SIZE){ forbid6[i][j + 1] += 1000; }
				if (j + 2 < CHESS_SIZE){ forbid6[i][j + 2] += 1000; }
				if (j + 3 < CHESS_SIZE){ forbid6[i][j + 3] += 1000; }
				if (j + 4 < CHESS_SIZE){ forbid6[i][j + 4] += 1000; }
				if (j + 5 < CHESS_SIZE){ forbid6[i][j + 5] += 1000; }
			}
			//列方向
			if (((board.getType(i, j) == 1) + (board.getType(i + 1, j) == 1) + (board.getType(i + 2, j) == 1) + (board.getType(i + 3, j) == 1) + (board.getType(i + 4, j) == 1) + (board.getType(i + 5, j) == 1) == 5)
				&& ((board.getType(i, j) == 0) + (board.getType(i + 1, j) == 0) + (board.getType(i + 2, j) == 0) + (board.getType(i + 3, j) == 0) + (board.getType(i + 4, j) == 0) + (board.getType(i + 5, j) == 0) == 1))
			{
				forbid6[i][j] += 1000;
				if (i + 1 < CHESS_SIZE){ forbid6[i + 1][j] += 1000; }
				if (i + 2 < CHESS_SIZE){ forbid6[i + 2][j] += 1000; }
				if (i + 3 < CHESS_SIZE){ forbid6[i + 3][j] += 1000; }
				if (i + 4 < CHESS_SIZE){ forbid6[i + 4][j] += 1000; }
				if (i + 5 < CHESS_SIZE){ forbid6[i + 5][j] += 1000; }
			}
			//左斜线
			if (((board.getType(i, j) == 1) + (board.getType(i + 1, j + 1) == 1) + (board.getType(i + 2, j + 2) == 1) + (board.getType(i + 3, j + 3) == 1) + (board.getType(i + 4, j + 4) == 1) + (board.getType(i + 5, j + 5) == 1) == 5)
				&& ((board.getType(i, j) == 0) + (board.getType(i + 1, j + 1) == 0) + (board.getType(i + 2, j + 2) == 0) + (board.getType(i + 3, j + 3) == 0) + (board.getType(i + 4, j + 4) == 0) + (board.getType(i + 5, j + 5) == 0) == 1))
			{
				forbid6[i][j] += 1000;
				if (i + 1 < CHESS_SIZE && j + 1 < CHESS_SIZE){ forbid6[i + 1][j + 1] += 1000; }
				if (i + 2 < CHESS_SIZE && j + 2 < CHESS_SIZE){ forbid6[i + 2][j + 2] += 1000; }
				if (i + 3 < CHESS_SIZE && j + 3 < CHESS_SIZE){ forbid6[i + 3][j + 3] += 1000; }
				if (i + 4 < CHESS_SIZE && j + 4 < CHESS_SIZE){ forbid6[i + 4][j + 4] += 1000; }
				if (i + 5 < CHESS_SIZE && j + 5 < CHESS_SIZE){ forbid6[i + 5][j + 5] += 1000; }
			}
			//右斜线
			if (((board.getType(i, j) == 1) + (board.getType(i + 1, j - 1) == 1) + (board.getType(i + 2, j - 2) == 1) + (board.getType(i + 3, j - 3) == 1) + (board.getType(i + 4, j - 4) == 1) + (board.getType(i + 5, j - 5) == 1) == 5)
				&& ((board.getType(i, j) == 0) + (board.getType(i + 1, j - 1) == 0) + (board.getType(i + 2, j - 2) == 0) + (board.getType(i + 3, j - 3) == 0) + (board.getType(i + 4, j - 4) == 0) + (board.getType(i + 5, j - 5) == 0) == 1))
			{
				forbid6[i][j] += 1000;
				if (i + 1 < CHESS_SIZE && j - 1 >= 0){ forbid6[i + 1][j - 1] += 1000; }
				if (i + 2 < CHESS_SIZE && j - 2 >= 0){ forbid6[i + 2][j - 2] += 1000; }
				if (i + 3 < CHESS_SIZE && j - 3 >= 0){ forbid6[i + 3][j - 3] += 1000; }
				if (i + 4 < CHESS_SIZE && j - 4 >= 0){ forbid6[i + 4][j - 4] += 1000; }
				if (i + 5 < CHESS_SIZE && j - 5 >= 0){ forbid6[i + 5][j - 5] += 1000; }
			}
		}
	}

	//汇总
	for (int i = 0; i < CHESS_SIZE; i++)
	{
		for (int j = 0; j < CHESS_SIZE; j++)
		{
			//成三去冗余
			if (forbid34[0][i][j] > 0){ forbid34[0][i][j] = 10; }
			if (forbid34[1][i][j] > 0){ forbid34[1][i][j] = 10; }
			if (forbid34[2][i][j] > 0){ forbid34[2][i][j] = 10; }
			if (forbid34[3][i][j] > 0){ forbid34[3][i][j] = 10; }
			//成四去冗余
			if (forbid44[0][i][j] > 0){ forbid44[0][i][j] = 100; }
			if (forbid44[1][i][j] > 0){ forbid44[1][i][j] = 100; }
			if (forbid44[2][i][j] > 0){ forbid44[2][i][j] = 100; }
			if (forbid44[3][i][j] > 0){ forbid44[3][i][j] = 100; }
			//汇总
			forbid[i][j] = forbid34[0][i][j] + forbid34[1][i][j] + forbid34[2][i][j] + forbid34[3][i][j]
				+ forbid44[0][i][j] + forbid44[1][i][j] + forbid44[2][i][j] + forbid44[3][i][j]
				+ forbid6[i][j];
		}
	}

	//计算结束，下面判断是否禁手
	int fbd = forbid[piece.x][piece.y];
	if (fbd == 20 || fbd == 30)
	{
		cout << "====!黑方不能落子于【三三】禁手点!====" << endl;
		return true;
	}
	else if (fbd == 200 || fbd == 300)
	{
		cout << "====!黑方不能落子于【四四】禁手点!====" << endl;
		return true;
	}
	else if (fbd == 120)
	{
		cout << "====!黑方不能落子于【四三三】禁手点!====" << endl;
		return true;
	}
	else if (fbd >= 1000)
	{
		cout << "====!黑方不能落子于【长连】禁手点!====" << endl;
		return true;
	}
	return false;
}

bool Judger::isaDraw(Chessboard& board)
{
	//判断是否棋盘已下满
	for (int i = 0; i < CHESS_SIZE; i++)
	{
		for (int j = 0; j < CHESS_SIZE; j++)
		{
			if (board.getType(i, j)==0)
			{
				return false;
			}
		}
	}
	return true;
}

bool Judger::isWin(Chessboard& board, Player& player)
{
	int type = player.getType();
	for (int i = 0; i < CHESS_SIZE;i++)
	{
		for (int j = 0; j < CHESS_SIZE;j++)
		{
			//是否一行出现五连子
			if (board.getType(i, j) == type && board.getType(i, j + 1) == type && board.getType(i, j + 2) == type && board.getType(i, j + 3) == type && board.getType(i, j + 4) == type)
			{
				return true;
			}
			//是否一列出现五连子
			else if (board.getType(i, j) == type && board.getType(i + 1, j) == type && board.getType(i + 2, j) == type && board.getType(i + 3, j) == type && board.getType(i + 4, j) == type)
			{
				return true;
			}
			//是否左斜线出现五连子
			else if (board.getType(i, j) == type && board.getType(i + 1, j + 1) == type && board.getType(i + 2, j + 2) == type && board.getType(i + 3, j + 3) == type && board.getType(i + 4, j + 4) == type)
			{
				return true;
			}
			//是否右斜线出现五连子
			else if (board.getType(i, j) == type && board.getType(i + 1, j - 1) == type && board.getType(i + 2, j - 2) == type && board.getType(i + 3, j - 3) == type && board.getType(i + 4, j - 4) == type)
			{
				return true;
			}
		}
	}
	return false;
}

bool Judger::isWin(Chessboard& board, const int turn)
{
	int type = turn == 0 ? 2 : 1;
	for (int i = 0; i < CHESS_SIZE; i++)
	{
		for (int j = 0; j < CHESS_SIZE; j++)
		{
			//是否一行出现五连子
			if (board.getType(i, j) == type && board.getType(i, j + 1) == type && board.getType(i, j + 2) == type && board.getType(i, j + 3) == type && board.getType(i, j + 4) == type)
			{
				return true;
			}
			//是否一列出现五连子
			else if (board.getType(i, j) == type && board.getType(i + 1, j) == type && board.getType(i + 2, j) == type && board.getType(i + 3, j) == type && board.getType(i + 4, j) == type)
			{
				return true;
			}
			//是否左斜线出现五连子
			else if (board.getType(i, j) == type && board.getType(i + 1, j + 1) == type && board.getType(i + 2, j + 2) == type && board.getType(i + 3, j + 3) == type && board.getType(i + 4, j + 4) == type)
			{
				return true;
			}
			//是否右斜线出现五连子
			else if (board.getType(i, j) == type && board.getType(i + 1, j - 1) == type && board.getType(i + 2, j - 2) == type && board.getType(i + 3, j - 3) == type && board.getType(i + 4, j - 4) == type)
			{
				return true;
			}
		}
	}
	return false;
}