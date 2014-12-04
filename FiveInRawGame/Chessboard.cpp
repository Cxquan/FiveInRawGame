#include "Chessboard.h"
#include <iostream>

using namespace std;

int initSymble[CHESS_SIZE][CHESS_SIZE] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,  //������
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
	//pieceBoard = { 0 };//0��ʾ��Ӧλ��������
	memset(pieceBoard, 0, sizeof(pieceBoard));
	symbleBoard = initSymble;
}

Chessboard::~Chessboard()
{
	delete[] pieceBoard;
	delete[] symbleBoard;
}

void Chessboard::setPiece(const int x, const int y, const int type)
{
	//check(x, y);
	pieceBoard[x][y] = type;
	symbleBoard[x][y] = (type == 2) ? 10 : 11;//������Ӧλ�õķ���λ������
}

int Chessboard::getType(const int x, const int y)
{
	//check(x, y);
	return pieceBoard[x][y];
}

int Chessboard::getSymble(const int x, const int y)
{
	//check(x, y);
	return symbleBoard[x][y];
}