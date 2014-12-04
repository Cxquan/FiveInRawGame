#include "Screener.h" 

using namespace std;

Screener::Screener()
{	
}

Screener::~Screener()
{
}

void Screener::showChoseBoard(Chessboard& board)
{
	system("cls");
	showBoard(board);
	cout << "双人对战模式(0);人机对战模式(1)" << endl;
	cout << "请选择游戏模式：";
}

void Screener::showBoard(Chessboard& board)
{
	//显示列坐标
	cout << " 0 1 2 3 4 5 6 7 8 9 10 1 2 3 4" << endl;
	for (int i = 0; i < CHESS_SIZE; i++)
	{
		if (i != 0)
		{
			cout << endl;
		}
		//显示行坐标
		cout << i % 10;
		for (int j = 0; j < CHESS_SIZE; j++)
		{
			cout << symble[board.getSymble(i, j)];
		}
	}
	cout << endl;
	cout << endl;
}