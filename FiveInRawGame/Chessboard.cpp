#include "Chessboard.h"
#include <iostream>

using namespace std;

int initSymble[CHESS_SIZE][CHESS_SIZE] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,  //空棋盘
3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8
};

Chessboard::Chessboard()
{
	//初始化棋盘落子
	pieceBoard = new Piece*[CHESS_SIZE];

	for (int i = 0; i < CHESS_SIZE; i++)
	{
		pieceBoard[i] = new Piece[CHESS_SIZE];
	}

	for (int i = 0; i < CHESS_SIZE; i++)
	{
		for (int j = 0; j < CHESS_SIZE; j++)
		{
			Piece piece(i, j, 0, initSymble[i][j]);
			pieceBoard[i][j] = piece;
		}
	}
}

void Chessboard::setPiece(const Piece& piece)
{
	pieceBoard[piece.x][piece.y] = piece;
}

int Chessboard::getType(const int x, const int y)
{
	return pieceBoard[x][y].type;
}

int Chessboard::getSymble(const int x, const int y)
{
	return pieceBoard[x][y].symble;
}

Chessboard::~Chessboard()
{
	for (int i = 0; i < CHESS_SIZE; i++)
	{
		delete[] pieceBoard[i]; //先撤销指针元素所指向的数组
	}
	delete[] pieceBoard;

}