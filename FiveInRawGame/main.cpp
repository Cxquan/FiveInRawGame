#include "Chessboard.h"
#include "Screener.h"
#include "Organizer.h"
#include <iostream>

using namespace std;

void main()
{
	/*Chessboard board;
	Screener screener;
	screener.showBoard(board);*/
	Organizer org;
	org.startGame();
	cout << "...end..." << endl;
}