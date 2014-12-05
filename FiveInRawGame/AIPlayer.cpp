#include "AIPlayer.h"

using namespace std;

AIPlayer::AIPlayer(int type)
{
	this->type = type;
}

AIPlayer::~AIPlayer()
{
}

void AIPlayer::placePiece(Chessboard& board, Piece& piece)
{
	board.setPiece(piece);
}

Piece AIPlayer::getMaxScorePiece(Chessboard& board, Judger& judger)
{
	//���̸���÷�
	int score[CHESS_SIZE][CHESS_SIZE] = { 0 };

	//====��ʼ���÷֣�Խ���м�÷�Խ��====
	for (int i = 0; i < CHESS_SIZE;i++)
	{
		for (int j = 0; j < CHESS_SIZE;j++)
		{
			//��Ե
			if (i < 3 || i >= CHESS_SIZE - 2 || j < 3 || j >= CHESS_SIZE - 2){ score[i][j] = 1; }
			//�α�Ե
			if (i >= 3 && i < CHESS_SIZE - 2 && j >= 3 && j < CHESS_SIZE - 2){ score[i][j] = 10; }
			//�м�
			if (i >= 5 && i < CHESS_SIZE - 4 && j >= 5 && j < CHESS_SIZE - 4){ score[i][j] = 100; }
		}
	}
	score[7][7] = 1000;

	//�������̣���������÷�
	for (int i = 0; i < CHESS_SIZE;i++)
	{
		for (int j; j < CHESS_SIZE;j++)
		{

			//���һ�� �����
			//������� ���  ���  �� ��  ���� �� ����  ��
			//������� ����
			//����ģ� ���  ����  ���

			for (int k = 0; k <= 3;k++)
			{
				//����壺 ���ա���������
				//������� ��ա� ���������
				//����ߣ� �����������ա�
				//����ˣ� ����������ա��
				//����ţ� ���
				//���ʮ�� ��  �� 
				//���ʮһ�� ��
			}
		}
	}

	Piece piece;
	return piece;
}