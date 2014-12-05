#include "Screener.h" 

using namespace std;

Screener::Screener()
{	
}

Screener::~Screener()
{
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

void Screener::showWinByForbidBoard(Chessboard& board, Player& player)
{
	showBoard(board);
	cout << "！！！黑方将棋子落于禁手点！！！" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~| 本次对战【白方】胜出 |~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system("pause");
}

void Screener::showWinerBoard(Chessboard& board, Player& player)
{
	system("cls");
	showBoard(board);
	string winner = player.getType() == 1 ? "黑方" : "白方";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~| 本次对战【" << winner << "】胜出 |~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system("pause");
}

void Screener::showWinerBoard(Chessboard& board, const int turn)
{
	system("cls");
	showBoard(board);
	string winner = turn == 1 ? "黑方" : "白方";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~| 本次对战【" << winner << "】胜出 |~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system("pause");
}

void Screener::showDrawBoard(Chessboard& board)
{
	system("cls");
	showBoard(board);

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~| 本次对战【不分胜负】 |~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system("pause");
}