#include "Organizer.h"
#include "AIPlayer.h"
#include "Judger.h"
#include "Chessboard.h"
#include "Screener.h"
#include "Piece.h"
#include "Player.h"

using namespace std;

Organizer::Organizer()
{
	turn = 1;
}

Organizer::~Organizer()
{
}

void Organizer::startGame()
{
	while (true)
	{
		Chessboard board;
		Screener screener;
		Judger judger;

		//ѡ��ģʽ
		getModeInput(screener, board);

		//˫�˶�ս
		if (mode == 0)
		{
			Player bPlayer(1);//�ڷ�
			Player wPlayer(2);//�׷�

			//��ʼ����
			while (true)//
			{
				//�ڷ�����
				if (turn == 1)
				{
					//getPieceInput();
					//bPlayer.placePiece();
				}
				//�׷�����
				else
				{
					//getPieceInput();
					//wPlayer.placePiece();
				}
				
				//judger.isForbidden();

				//judger.isWin//ƽ���жϣ�

			}
			
		}
		//�˻���ս
		else
		{
			Player hmPlayer(1);//�˺ڷ�
			AIPlayer aiPlayer(2);//���԰׷�
			
			//�ڷ�����
			if (true == 1)
			{
				//getPieceInput();
				//hmPlayer.placePiece();
			}
			//�׷�����
			else
			{
				//getPieceInput();
				//aiPlayer.placePiece();
			}

			//judger.isForbidden();

			//judger.isWin//ƽ���жϣ�
		}

		//�Ƿ�����һ��
		if (!isPlayAgain(screener, board))
		{
			//showGoodBye();
			break;
		}
	}
}

bool Organizer::isPlayAgain(Screener& screener, Chessboard& board)
{
	system("cls");
	screener.showBoard(board);
	cout << "�Ƿ�����һ�̣�" << endl;
	cout << "��(y)/��(n):";
	char c;
	cin >> c;
	while (cin.fail() || (c != 'y' && c != 'n'))
	{
		cin.clear();
		cin.ignore();

		cout << endl;
		cout << "!!!�����������������!!!" << endl;
		cout << "�Ƿ�����һ�̣�" << endl;
		cout << "��(y)/��(n):";
		cin >> c;
	}
	if (c == 'y')
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Organizer::getModeInput(Screener& screener, Chessboard& board)
{
	system("cls");
	screener.showBoard(board);
	cout << "˫�˶�սģʽ(0);�˻���սģʽ(1)" << endl;
	cout << "��ѡ����Ϸģʽ��";

	int m;
	cin >> m;
	while (cin.fail() || (m != 0 && m != 1))
	{
		cin.clear();
		cin.ignore();

		cout << "!!!�����������������!!!" << endl;
		cout << "˫�˶�սģʽ(0);�˻���սģʽ(1)" << endl;
		cout << "��ѡ����Ϸģʽ��";
		cin >> m;
	}
	mode = m;
}