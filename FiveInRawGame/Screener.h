#ifndef Screener_H
#define Screener_H

#include "Chessboard.h"
#include "Player.h"
#include <iostream>

using namespace std;

static const char symble[11][4] = { "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘", "●", "○" };  //可供选用的字符，输出棋盘或者棋子用

class Screener {
public:
	Screener();
	~Screener();

	void showChoseBoard(Chessboard& board);
	void showWinerBoard(Chessboard& board, Player& player);
	void showForbiddenBoard(Chessboard& board, Player& player);
	void showGamingBoard(Chessboard& board);

	void showBoard(Chessboard& board);
};

#endif