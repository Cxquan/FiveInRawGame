#include "Screener.h" 

using namespace std;

Screener::Screener()
{	
}

Screener::~Screener()
{
}

void Screener::showBoard(Chessboard& board){
	//��ʾ������
	cout << " 0 1 2 3 4 5 6 7 8 9 10 1 2 3 4" << endl;
	for (int i = 0; i < CHESS_SIZE; i++)
	{
		if (i != 0)
		{
			cout << endl;
		}
		//��ʾ������
		cout << i % 10;
		for (int j = 0; j < CHESS_SIZE; j++)
		{
			cout << symble[board.getSymble(i, j)];
		}
	}
	cout << endl;
}