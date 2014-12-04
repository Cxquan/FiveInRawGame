#include "Chessboard.h"
#include <iostream>

using namespace std;

int initSymble[CHESS_SIZE][CHESS_SIZE] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,  //ø’∆Â≈Ã
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
	//≥ı ºªØ∆Â≈Ã¬‰◊”
	for (int i = 0; i < CHESS_SIZE; i++)
	{
		for (int j = i; j < CHESS_SIZE; j++)
		{
			Piece piece(i, j, 0, initSymble[i][j]);
			pieceBoard[i][j] = piece;
		}
	}

}

void Chessboard::setPiece(Piece& piece)
{
	//check(x, y);
	pieceBoard[piece.x][piece.y] = piece;
}

int Chessboard::getType(const int x, const int y)
{
	//check(x, y);
	return pieceBoard[x][y].type;
}

int Chessboard::getSymble(const int x, const int y)
{
	//check(x, y);
	return pieceBoard[x][y].symble;
}

Chessboard::~Chessboard()
{
	delete[] pieceBoard;
}