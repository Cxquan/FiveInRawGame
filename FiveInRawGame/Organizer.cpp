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
	turn = 1;//�ڷ�����
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
			Player currentPlayer;
			Piece currentPiece(-1, -1, 2);
			//��ʼ����
			while (true)//
			{
				//�ڷ�����1
				if (turn == 1)
				{
					currentPiece = getPieceInput(screener, board, judger, currentPiece);
					bPlayer.placePiece(board, currentPiece);
				}
				//�׷�����2
				else
				{
					currentPiece = getPieceInput(screener, board, judger, currentPiece);
					wPlayer.placePiece(board, currentPiece);
				}
				//�ж��Ƿ�ʤ��/ƽ��
				currentPlayer = turn == 1 ? bPlayer : wPlayer;
				if (judger.isWin(board, currentPlayer))
				{
					screener.showWinerBoard(board, currentPlayer);
					break;
				}
				else if (judger.isaDraw(board))
				{
					screener.showDrawBoard(board);
					break;
				}
				turn = ++turn % 2;//��������
			}			
		}

		//�˻���ս
		else
		{
			Player hmPlayer(1);//�˺ڷ�
			AIPlayer aiPlayer(2);//���԰׷�
			Piece currentPiece(-1, -1, 2);
			//��ʼ����
			while (true)//
			{
				//�ڷ�����1
				if (turn == 1)
				{
					currentPiece = getPieceInput(screener, board, judger, currentPiece);
					hmPlayer.placePiece(board, currentPiece);
				}
				//�׷�(����)����2
				else
				{
					currentPiece = aiPlayer.getMaxScorePiece(board, judger);
					aiPlayer.placePiece(board, currentPiece);
				}
				//�ж��Ƿ�ʤ��/ƽ��
				if (judger.isWin(board, turn))
				{
					screener.showWinerBoard(board, turn);
					break;
				}
				else if (judger.isaDraw(board))
				{
					screener.showDrawBoard(board);
					break;
				}
				turn = ++turn % 2;//��������
			}
		}
		//�Ƿ�����һ��
		if (!isPlayAgain(screener, board))
		{
			//showGoodBye();
			break;
		}
	}
}

Piece Organizer::getPieceInput(Screener& screener, Chessboard& board, Judger& judger, const Piece& lastPiece)
{
	system("cls");
	screener.showBoard(board);
	
	string opo, name;
	int type;
	if (lastPiece.type == 1)
	{
		opo = "�ڷ�";
		name = "�׷�";
		type = 2;
	}
	else
	{
		if (mode == 1)
		{
			opo = "����";
			name = "��";
			type = 1;
		}
		else
		{
			opo = "�׷�";
			name = "�ڷ�";
			type = 1;
		}
	}
	if (lastPiece.x != -1)
	{
		cout << "��" << opo << "��������: " << lastPiece.x << " " << lastPiece.y << endl;
	}	
	cout << "�롾" << name << "�������������꣺";
	
	int x, y;
	cin >> x >> y;
	Piece piece(x, y, type);

	//�ж�λ�úϹ��ԡ��Լ����ӷ����
	while (cin.fail() || !judger.isValidPosition(board, piece)
		|| ((1 == type) ? judger.isForbidden(board, piece) : false))
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//���Ի������еĶ�������

		cout << "==== ����������������� ====" << endl;
		cout << "�롾" << name << "�������������꣺";
		cin >> x >> y;
		piece.setVal(x, y, type);
	}

	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//���Ի������еĶ�������
	return piece;
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
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//���Ի������еĶ�������

		cout << endl;
		cout << "==== ����������������� ====" << endl;
		cout << "�Ƿ�����һ�̣�" << endl;
		cout << "��(y)/��(n):";
		cin >> c;
	}
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//���Ի������еĶ�������
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
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~~~ ��ӭ�����������ս ~~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "��������ĸ���սģʽ��" << endl;
	cout << "˫�˶�սģʽ(0)/�˻���սģʽ(1)��";

	int m;
	cin >> m;
	while (cin.fail() || (m != 0 && m != 1))
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//���Ի������еĶ�������

		cout << "==== ����������������� ====" << endl;
		cout << "��������ĸ���սģʽ��" << endl;
		cout << "˫�˶�սģʽ(0)/�˻���սģʽ(1)��";
		cin >> m;
	}

	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//���Ի������еĶ�������
	mode = m;
}