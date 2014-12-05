#ifndef Screener_H
#define Screener_H

#include "Chessboard.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

static const char symble[11][4] = { "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘", "○", "●" };  //可供选用的字符，输出棋盘或者棋子用

class Screener {
public:
	Screener();
	~Screener();

	void showWinerBoard(Chessboard& board, Player& player);
	void showWinerBoard(Chessboard& board, const int turn);
	void showWinByForbidBoard(Chessboard& board, Player& player);
	void showDrawBoard(Chessboard& board);

	void showBoard(Chessboard& board);
};

#endif