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
	cout << endl;
}

void Screener::showWinByForbidBoard(Chessboard& board, Player& player)
{
	showBoard(board);
	cout << "�������ڷ����������ڽ��ֵ㣡����" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~| ���ζ�ս���׷���ʤ�� |~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system("pause");
}

void Screener::showWinerBoard(Chessboard& board, Player& player)
{
	system("cls");
	showBoard(board);
	string winner = player.getType() == 1 ? "�ڷ�" : "�׷�";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~| ���ζ�ս��" << winner << "��ʤ�� |~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system("pause");
}

void Screener::showWinerBoard(Chessboard& board, const int turn)
{
	system("cls");
	showBoard(board);
	string winner = turn == 1 ? "�ڷ�" : "�׷�";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~| ���ζ�ս��" << winner << "��ʤ�� |~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system("pause");
}

void Screener::showDrawBoard(Chessboard& board)
{
	system("cls");
	showBoard(board);

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~| ���ζ�ս������ʤ���� |~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system("pause");
}