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
	for (int i = 0; i < CHESS_SIZE; i++)
	{
		for (int j = 0; j < CHESS_SIZE; j++)
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

	//�������̣���������÷�,ÿ���������Ժ���(1)&����(2)��������
	for (int i = 0; i < CHESS_SIZE; i++)
	{
		for (int j = 0; j < CHESS_SIZE; j++)
		{
			//���һ�� �����
			four(board, score, 1, i, j, 1000000);
			four(board, score, 2, i, j, 5000000);

			//������� ���  ���  �� ��  ���� �� ����  ��
			twoBtwo(board, score, 1, i, j, 1000000);
			twoBtwo(board, score, 2, i, j, 5000000);

			//������� ����
			three(board, score, 1, i, j, 30000);
			three(board, score, 2, i, j, 100000);

			//����ģ� ���  ����  ���
			twoBone(board, score, 1, i, j, 30000);
			twoBone(board, score, 2, i, j, 100000);

			for (int k = 0; k <= 3; k++)
			{
				//����壺 ���ա���������
				twoBonePone(board, score, 1, 2, i, j, k);
				twoBonePone(board, score, 2, 1, i, j, k);

				//������� ��ա� ���������
				oneBonePtwo(board, score, 1, 2, i, j, k);
				oneBonePtwo(board, score, 2, 1, i, j, k);

				//����ߣ� �����������ա�
				twoPoneBone(board, score, 1, 2, i, j, k);
				twoPoneBone(board, score, 2, 1, i, j, k);

				//����ˣ� ����������ա��
				onePoneBtwo(board, score, 1, 2, i, j, k);
				onePoneBtwo(board, score, 2, 1, i, j, k);
			}

			//����ţ� ���
			two(board, score, 1, i, j);
			two(board, score, 2, i, j);

			//���ʮ�� ��  �� 
			oneBone(board, score, 1, i, j);
			oneBone(board, score, 2, i, j);

			//���ʮһ�� ��
			one(board, score, 1, i, j);
			one(board, score, 2, i, j);
		}
	}
	
	//��ȡ�÷����ĵ�
	Piece piece;
	int maxScore = -1;
	for (int i = 0; i < CHESS_SIZE;i++)
	{
		for (int j = 0; j < CHESS_SIZE;j++)
		{
			//����õ��Ѿ������ӣ���÷�����
			if (board.getType(i, j) != 0) { score[i][j] = 0; }
			if (score[i][j] > maxScore)
			{
				maxScore = score[i][j];
				piece.setVal(i, j, 2);//typeΪ��ɫ
			}
		}
	}
	return piece;
}

//���һ�� �����
void AIPlayer::four(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade)
{
	if (board.getType(i, j) == type && board.getType(i, j + 1) == type && board.getType(i, j + 2) == type && board.getType(i, j + 3) == type && board.getType(i, j + 4) == 0)
	{//��
		if (j + 4 < CHESS_SIZE)	{ score[i][j + 4] += grade; }
	}
	if (board.getType(i, j) == 0 && board.getType(i, j + 1) == type && board.getType(i, j + 2) == type && board.getType(i, j + 3) == type && board.getType(i, j + 4) == type)
	{//��
		score[i][j] += grade;
	}
	if (board.getType(i, j) == type && board.getType(i + 1, j) == type && board.getType(i + 2, j) == type && board.getType(i + 3, j) == type && board.getType(i + 4, j) == 0)
	{//��
		if (i + 4 < CHESS_SIZE)	{ score[i + 4][j] += grade; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j) == type && board.getType(i + 2, j) == type && board.getType(i + 3, j) == type && board.getType(i + 4, j) == type)
	{//��
		score[i][j] += grade;
	}
	if (board.getType(i, j) == type && board.getType(i + 1, j + 1) == type && board.getType(i + 2, j + 2) == type && board.getType(i + 3, j + 3) == type && board.getType(i + 4, j + 4) == 0)
	{//��б��
		if (i + 4 < CHESS_SIZE && j + 4 < CHESS_SIZE)	{ score[i + 4][j + 4] += grade; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j + 1) == type && board.getType(i + 2, j + 2) == type && board.getType(i + 3, j + 3) == type && board.getType(i + 4, j + 4) == type)
	{//��б��
		score[i][j] += grade;
	}
	if (board.getType(i, j) == type && board.getType(i + 1, j - 1) == type && board.getType(i + 2, j - 2) == type && board.getType(i + 3, j - 3) == type && board.getType(i + 4, j - 4) == 0)
	{//��б��
		if (i + 4 < CHESS_SIZE && j - 4 >= 0)	{ score[i + 4][j - 4] += grade; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j - 1) == type && board.getType(i + 2, j - 2) == type && board.getType(i + 3, j - 3) == type && board.getType(i + 4, j - 4) == type)
	{//��б��
		score[i][j] += grade;
	}
}

//������� ���  ���  �� ��  ���� �� ����  ��
void AIPlayer::twoBtwo(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade)
{
	if (((board.getType(i, j) == type) + (board.getType(i, j + 1) == type) + (board.getType(i, j + 2) == type) + (board.getType(i, j + 3) == type) + (board.getType(i, j + 4) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i, j + 1) == 0) + (board.getType(i, j + 2) == 0) + (board.getType(i, j + 3) == 0) + (board.getType(i, j + 4) == 0)) == 1)
	{//��
		score[i][j] += grade;
		if (j + 1 < CHESS_SIZE){ score[i][j + 1] += grade; }
		if (j + 2 < CHESS_SIZE){ score[i][j + 2] += grade; }
		if (j + 3 < CHESS_SIZE){ score[i][j + 3] += grade; }
		if (j + 4 < CHESS_SIZE){ score[i][j + 4] += grade; }
	}
	if (((board.getType(i, j) == type) + (board.getType(i + 1, j) == type) + (board.getType(i + 2, j) == type) + (board.getType(i + 3, j) == type) + (board.getType(i + 4, j) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i + 1, j) == 0) + (board.getType(i + 2, j) == 0) + (board.getType(i + 3, j) == 0) + (board.getType(i + 4, j) == 0)) == 1)
	{//��
		score[i][j] += grade;
		if (i + 1 < CHESS_SIZE){ score[i + 1][j] += grade; }
		if (i + 2 < CHESS_SIZE){ score[i + 2][j] += grade; }
		if (i + 3 < CHESS_SIZE){ score[i + 3][j] += grade; }
		if (i + 4 < CHESS_SIZE){ score[i + 4][j] += grade; }
	}
	if (((board.getType(i, j) == type) + (board.getType(i + 1, j + 1) == type) + (board.getType(i + 2, j + 2) == type) + (board.getType(i + 3, j + 3) == type) + (board.getType(i + 4, j + 4) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i + 1, j + 1) == 0) + (board.getType(i + 2, j + 2) == 0) + (board.getType(i + 3, j + 3) == 0) + (board.getType(i + 4, j + 4) == 0)) == 1)
	{//��б��
		score[i][j] += grade;
		if (i + 1 < CHESS_SIZE && j + 1 < CHESS_SIZE){ score[i + 1][j + 1] += grade; }
		if (i + 2 < CHESS_SIZE && j + 2 < CHESS_SIZE){ score[i + 2][j + 2] += grade; }
		if (i + 3 < CHESS_SIZE && j + 3 < CHESS_SIZE){ score[i + 3][j + 3] += grade; }
		if (i + 4 < CHESS_SIZE && j + 4 < CHESS_SIZE){ score[i + 4][j + 4] += grade; }
	}
	if (((board.getType(i, j) == type) + (board.getType(i + 1, j - 1) == type) + (board.getType(i + 2, j - 2) == type) + (board.getType(i + 3, j - 3) == type) + (board.getType(i + 4, j - 4) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i + 1, j - 1) == 0) + (board.getType(i + 2, j - 2) == 0) + (board.getType(i + 3, j - 3) == 0) + (board.getType(i + 4, j - 4) == 0)) == 1)
	{//��б��
		score[i][j] += grade;
		if (i + 1 < CHESS_SIZE && j - 1 >= 0){ score[i + 1][j - 1] += grade; }
		if (i + 2 < CHESS_SIZE && j - 2 >= 0){ score[i + 2][j - 2] += grade; }
		if (i + 3 < CHESS_SIZE && j - 3 >= 0){ score[i + 3][j - 3] += grade; }
		if (i + 4 < CHESS_SIZE && j - 4 >= 0){ score[i + 4][j - 4] += grade; }
	}
}

//������� ����
void AIPlayer::three(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade)
{
	if ((board.getType(i, j) == 0) && (board.getType(i, j + 1) == type) && (board.getType(i, j + 2) == type) && (board.getType(i, j + 3) == type) && (board.getType(i, j + 4) == 0))
	{//��
		score[i][j] += grade;
		if (j + 4 < CHESS_SIZE) { score[i][j + 4] += grade; }
	}
	if ((board.getType(i, j) == 0) && (board.getType(i + 1, j) == type) && (board.getType(i + 2, j) == type) && (board.getType(i + 3, j) == type) && (board.getType(i + 4, j) == 0))
	{//��
		score[i][j] += grade;
		if (i + 4 < CHESS_SIZE) { score[i + 4][j] += grade; }
	}
	if ((board.getType(i, j) == 0) && (board.getType(i + 1, j + 1) == type) && (board.getType(i + 2, j + 2) == type) && (board.getType(i + 3, j + 3) == type) && (board.getType(i + 4, j + 4) == 0))
	{//��б��
		score[i][j] += grade;
		if (i + 4 < CHESS_SIZE && j + 4 < CHESS_SIZE) { score[i + 4][j + 4] += grade; }
	}
	if ((board.getType(i, j) == 0) && (board.getType(i + 1, j - 1) == type) && (board.getType(i + 2, j - 2) == type) && (board.getType(i + 3, j - 3) == type) && (board.getType(i + 4, j - 4) == 0))
	{//��б��
		score[i][j] += grade;
		if (i + 4 < CHESS_SIZE && j - 4 >= 0) { score[i + 4][j - 4] += grade; }
	}
}

//����ģ� ���  ����  ���
void AIPlayer::twoBone(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade)
{
	if (board.getType(i, j - 1) == 0 && board.getType(i, j + 4) == 0
		&& ((board.getType(i, j) == type) + (board.getType(i, j + 1) == type) + (board.getType(i, j + 2) == type) + (board.getType(i, j + 3) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i, j + 1) == 0) + (board.getType(i, j + 2) == 0) + (board.getType(i, j + 3) == 0)) == 1)
	{//��
		score[i][j] += grade;
		if (j + 1 < CHESS_SIZE) { score[i][j + 1] += grade; }
		if (j + 2 < CHESS_SIZE) { score[i][j + 2] += grade; }
		if (j + 3 < CHESS_SIZE) { score[i][j + 3] += grade; }
	}
	if (board.getType(i - 1, j) == 0 && board.getType(i + 4, j) == 0
		&& ((board.getType(i, j) == type) + (board.getType(i + 1, j) == type) + (board.getType(i + 2, j) == type) + (board.getType(i + 3, j) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i + 1, j) == 0) + (board.getType(i + 2, j) == 0) + (board.getType(i + 3, j) == 0)) == 1)
	{//��
		score[i][j] += grade;
		if (i + 1 < CHESS_SIZE) { score[i + 1][j] += grade; }
		if (i + 2 < CHESS_SIZE) { score[i + 2][j] += grade; }
		if (i + 3 < CHESS_SIZE) { score[i + 3][j] += grade; }

	}
	if (board.getType(i - 1, j - 1) == 0 && board.getType(i + 4, j + 4) == 0
		&& ((board.getType(i, j) == type) + (board.getType(i + 1, j + 1) == type) + (board.getType(i + 2, j + 2) == type) + (board.getType(i + 3, j + 3) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i + 1, j + 1) == 0) + (board.getType(i + 2, j + 2) == 0) + (board.getType(i + 3, j + 3) == 0)) == 1)
	{//��б��
		score[i][j] += grade;
		if (i + 1 < CHESS_SIZE && j + 1 < CHESS_SIZE) { score[i + 1][j + 1] += grade; }
		if (i + 2 < CHESS_SIZE && j + 1 < CHESS_SIZE) { score[i + 2][j + 2] += grade; }
		if (i + 3 < CHESS_SIZE && j + 1 < CHESS_SIZE) { score[i + 3][j + 3] += grade; }

	}
	if (board.getType(i - 1, j + 1) == 0 && board.getType(i + 4, j - 4) == 0
		&& ((board.getType(i, j) == type) + (board.getType(i + 1, j - 1) == type) + (board.getType(i + 2, j - 2) == type) + (board.getType(i + 3, j - 3) == type)) == 4
		&& ((board.getType(i, j) == 0) + (board.getType(i + 1, j - 1) == 0) + (board.getType(i + 2, j - 2) == 0) + (board.getType(i + 3, j - 3) == 0)) == 1)
	{//��б��
		score[i][j] += grade;
		if (i + 1 < CHESS_SIZE && j - 1 >= 0) { score[i + 1][j - 1] += grade; }
		if (i + 2 < CHESS_SIZE && j - 2 >= 0) { score[i + 2][j - 2] += grade; }
		if (i + 3 < CHESS_SIZE && j - 3 >= 0) { score[i + 3][j - 3] += grade; }

	}
}

//����壺 ���ա���������
void AIPlayer::twoBonePone(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k)
{
	if (board.getType(i, j - 4) == aType //��
		&& ((board.getType(i, j - 3) == bType) + (board.getType(i, j - 2) == bType) + (board.getType(i, j - 1) == bType) + (board.getType(i, j + 1) == bType)) == k
		&& ((board.getType(i, j - 3) == 0) + (board.getType(i, j - 2) == 0) + (board.getType(i, j - 1) == 0) + (board.getType(i, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i, j + 4) == aType //��
		&& ((board.getType(i, j + 3) == bType) + (board.getType(i, j + 2) == bType) + (board.getType(i, j + 1) == bType) + (board.getType(i, j - 1) == bType)) == k
		&& ((board.getType(i, j + 3) == 0) + (board.getType(i, j + 2) == 0) + (board.getType(i, j + 1) == 0) + (board.getType(i, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 4, j) == aType //��
		&& ((board.getType(i - 3, j) == bType) + (board.getType(i - 2, j) == bType) + (board.getType(i - 1, j) == bType) + (board.getType(i + 1, j) == bType)) == k
		&& ((board.getType(i - 3, j) == 0) + (board.getType(i - 2, j) == 0) + (board.getType(i - 1, j) == 0) + (board.getType(i + 1, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 4, j) == aType //��
		&& ((board.getType(i + 3, j) == bType) + (board.getType(i + 2, j) == bType) + (board.getType(i + 1, j) == bType) + (board.getType(i - 1, j) == bType)) == k
		&& ((board.getType(i + 3, j) == 0) + (board.getType(i + 2, j) == 0) + (board.getType(i + 1, j) == 0) + (board.getType(i - 1, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 4, j - 4) == aType //��б��
		&& ((board.getType(i - 3, j - 3) == bType) + (board.getType(i - 2, j - 2) == bType) + (board.getType(i - 1, j - 1) == bType) + (board.getType(i + 1, j + 1) == bType)) == k
		&& ((board.getType(i - 3, j - 3) == 0) + (board.getType(i - 2, j - 2) == 0) + (board.getType(i - 1, j - 1) == 0) + (board.getType(i + 1, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 4, j + 4) == aType //��б��
		&& ((board.getType(i + 3, j + 3) == bType) + (board.getType(i + 2, j + 2) == bType) + (board.getType(i + 1, j + 1) == bType) + (board.getType(i - 1, j - 1) == bType)) == k
		&& ((board.getType(i + 3, j + 3) == 0) + (board.getType(i + 2, j + 2) == 0) + (board.getType(i + 1, j + 1) == 0) + (board.getType(i - 1, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 4, j + 4) == aType //��б��
		&& ((board.getType(i - 3, j + 3) == bType) + (board.getType(i - 2, j + 2) == bType) + (board.getType(i - 1, j + 1) == bType) + (board.getType(i + 1, j - 1) == bType)) == k
		&& ((board.getType(i - 3, j + 3) == 0) + (board.getType(i - 2, j + 2) == 0) + (board.getType(i - 1, j + 1) == 0) + (board.getType(i + 1, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 4, j - 4) == aType //��б��
		&& ((board.getType(i + 3, j - 3) == bType) + (board.getType(i + 2, j - 2) == bType) + (board.getType(i + 1, j - 1) == bType) + (board.getType(i - 1, j + 1) == bType)) == k
		&& ((board.getType(i + 3, j - 3) == 0) + (board.getType(i + 2, j - 2) == 0) + (board.getType(i + 1, j - 1) == 0) + (board.getType(i - 1, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
}

//������� ��ա� ���������
void AIPlayer::oneBonePtwo(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k)
{
	if (board.getType(i, j - 3) == aType //��
		&& ((board.getType(i, j - 1) == bType) + (board.getType(i, j - 2) == bType) + (board.getType(i, j + 2) == bType) + (board.getType(i, j + 1) == bType)) == k
		&& ((board.getType(i, j - 1) == 0) + (board.getType(i, j - 2) == 0) + (board.getType(i, j + 2) == 0) + (board.getType(i, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i, j + 3) == aType //��
		&& ((board.getType(i, j + 1) == bType) + (board.getType(i, j + 2) == bType) + (board.getType(i, j - 2) == bType) + (board.getType(i, j - 1) == bType)) == k
		&& ((board.getType(i, j + 1) == 0) + (board.getType(i, j + 2) == 0) + (board.getType(i, j - 2) == 0) + (board.getType(i, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 3, j) == aType //��
		&& ((board.getType(i - 1, j) == bType) + (board.getType(i - 2, j) == bType) + (board.getType(i + 2, j) == bType) + (board.getType(i + 1, j) == bType)) == k
		&& ((board.getType(i - 1, j) == 0) + (board.getType(i - 2, j) == 0) + (board.getType(i + 2, j) == 0) + (board.getType(i + 1, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 3, j) == aType //��
		&& ((board.getType(i + 1, j) == bType) + (board.getType(i + 2, j) == bType) + (board.getType(i - 2, j) == bType) + (board.getType(i - 1, j) == bType)) == k
		&& ((board.getType(i + 1, j) == 0) + (board.getType(i + 2, j) == 0) + (board.getType(i - 2, j) == 0) + (board.getType(i - 1, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 3, j - 3) == aType //��б��
		&& ((board.getType(i - 1, j - 1) == bType) + (board.getType(i - 2, j - 2) == bType) + (board.getType(i + 2, j + 2) == bType) + (board.getType(i + 1, j + 1) == bType)) == k
		&& ((board.getType(i - 1, j - 1) == 0) + (board.getType(i - 2, j - 2) == 0) + (board.getType(i + 2, j + 2) == 0) + (board.getType(i + 1, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 3, j + 3) == aType //��б��
		&& ((board.getType(i + 1, j + 1) == bType) + (board.getType(i + 2, j + 2) == bType) + (board.getType(i - 2, j - 2) == bType) + (board.getType(i - 1, j - 1) == bType)) == k
		&& ((board.getType(i + 1, j + 1) == 0) + (board.getType(i + 2, j + 2) == 0) + (board.getType(i - 2, j - 2) == 0) + (board.getType(i - 1, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 3, j + 3) == aType //��б��
		&& ((board.getType(i - 1, j + 1) == bType) + (board.getType(i - 2, j + 2) == bType) + (board.getType(i + 2, j - 2) == bType) + (board.getType(i + 1, j - 1) == bType)) == k
		&& ((board.getType(i - 1, j + 1) == 0) + (board.getType(i - 2, j + 2) == 0) + (board.getType(i + 2, j - 2) == 0) + (board.getType(i + 1, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 3, j - 3) == aType //��б��
		&& ((board.getType(i + 1, j - 1) == bType) + (board.getType(i + 2, j - 2) == bType) + (board.getType(i - 2, j + 2) == bType) + (board.getType(i - 1, j + 1) == bType)) == k
		&& ((board.getType(i + 1, j - 1) == 0) + (board.getType(i + 2, j - 2) == 0) + (board.getType(i - 2, j + 2) == 0) + (board.getType(i - 1, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
}

//����ߣ� �����������ա�
void AIPlayer::twoPoneBone(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k)
{
	if (board.getType(i, j - 2) == aType //��
		&& ((board.getType(i, j + 3) == bType) + (board.getType(i, j + 2) == bType) + (board.getType(i, j + 1) == bType) + (board.getType(i, j - 1) == bType)) == k
		&& ((board.getType(i, j + 3) == 0) + (board.getType(i, j + 2) == 0) + (board.getType(i, j + 1) == 0) + (board.getType(i, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i, j + 2) == aType //��
		&& ((board.getType(i, j - 3) == bType) + (board.getType(i, j - 2) == bType) + (board.getType(i, j - 1) == bType) + (board.getType(i, j + 1) == bType)) == k
		&& ((board.getType(i, j - 3) == 0) + (board.getType(i, j - 2) == 0) + (board.getType(i, j - 1) == 0) + (board.getType(i, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 2, j) == aType //��
		&& ((board.getType(i + 3, j) == bType) + (board.getType(i + 2, j) == bType) + (board.getType(i + 1, j) == bType) + (board.getType(i - 1, j) == bType)) == k
		&& ((board.getType(i + 3, j) == 0) + (board.getType(i + 2, j) == 0) + (board.getType(i + 1, j) == 0) + (board.getType(i - 1, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 2, j) == aType //��
		&& ((board.getType(i - 3, j) == bType) + (board.getType(i - 2, j) == bType) + (board.getType(i - 1, j) == bType) + (board.getType(i + 1, j) == bType)) == k
		&& ((board.getType(i - 3, j) == 0) + (board.getType(i - 2, j) == 0) + (board.getType(i - 1, j) == 0) + (board.getType(i + 1, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 2, j - 2) == aType //��б��
		&& ((board.getType(i + 3, j + 3) == bType) + (board.getType(i + 2, j + 2) == bType) + (board.getType(i + 1, j + 1) == bType) + (board.getType(i - 1, j - 1) == bType)) == k
		&& ((board.getType(i + 3, j + 3) == 0) + (board.getType(i + 2, j + 2) == 0) + (board.getType(i + 1, j + 1) == 0) + (board.getType(i - 1, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 2, j + 2) == aType //��б��
		&& ((board.getType(i - 3, j - 3) == bType) + (board.getType(i - 2, j - 2) == bType) + (board.getType(i - 1, j - 1) == bType) + (board.getType(i + 1, j + 1) == bType)) == k
		&& ((board.getType(i - 3, j - 3) == 0) + (board.getType(i - 2, j - 2) == 0) + (board.getType(i - 1, j - 1) == 0) + (board.getType(i + 1, j + 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 2, j + 2) == aType //��б��
		&& ((board.getType(i + 3, j - 3) == bType) + (board.getType(i + 2, j - 2) == bType) + (board.getType(i + 1, j - 1) == bType) + (board.getType(i - 1, j + 1) == bType)) == k
		&& ((board.getType(i + 3, j - 3) == 0) + (board.getType(i + 2, j - 2) == 0) + (board.getType(i + 1, j - 1) == 0) + (board.getType(i - 1, j + 1) == 0)) == 4 - k)
		
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 2, j - 2) == aType //��б��
		&& ((board.getType(i - 3, j + 3) == bType) + (board.getType(i - 2, j + 2) == bType) + (board.getType(i - 1, j + 1) == bType) + (board.getType(i + 1, j - 1) == bType)) == k
		&& ((board.getType(i - 3, j + 3) == 0) + (board.getType(i - 2, j + 2) == 0) + (board.getType(i - 1, j + 1) == 0) + (board.getType(i + 1, j - 1) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
}

//����ˣ� ����������ա��
void AIPlayer::onePoneBtwo(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k)
{
	if (board.getType(i, j - 1) == aType //��
		&& ((board.getType(i, j + 1) == bType) + (board.getType(i, j + 2) == bType) + (board.getType(i, j + 3) == bType) + (board.getType(i, j + 4) == bType)) == k
		&& ((board.getType(i, j + 1) == 0) + (board.getType(i, j + 2) == 0) + (board.getType(i, j + 3) == 0) + (board.getType(i, j + 4) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i, j + 1) == aType //��
		&& ((board.getType(i, j - 1) == bType) + (board.getType(i, j - 2) == bType) + (board.getType(i, j - 3) == bType) + (board.getType(i, j - 4) == bType)) == k
		&& ((board.getType(i, j - 1) == 0) + (board.getType(i, j - 2) == 0) + (board.getType(i, j - 3) == 0) + (board.getType(i, j - 4) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 1, j) == aType //��
		&& ((board.getType(i + 1, j) == bType) + (board.getType(i + 2, j) == bType) + (board.getType(i + 3, j) == bType) + (board.getType(i + 4, j) == bType)) == k
		&& ((board.getType(i + 1, j) == 0) + (board.getType(i + 2, j) == 0) + (board.getType(i + 3, j) == 0) + (board.getType(i + 4, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 1, j) == aType //��
		&& ((board.getType(i - 1, j) == bType) + (board.getType(i - 2, j) == bType) + (board.getType(i - 3, j) == bType) + (board.getType(i - 4, j) == bType)) == k
		&& ((board.getType(i - 1, j) == 0) + (board.getType(i - 2, j) == 0) + (board.getType(i - 3, j) == 0) + (board.getType(i - 4, j) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 1, j - 1) == aType //��б��
		&& ((board.getType(i + 1, j + 1) == bType) + (board.getType(i + 2, j + 2) == bType) + (board.getType(i + 3, j + 3) == bType) + (board.getType(i + 4, j + 4) == bType)) == k
		&& ((board.getType(i + 1, j + 1) == 0) + (board.getType(i + 2, j + 2) == 0) + (board.getType(i + 3, j + 3) == 0) + (board.getType(i + 4, j + 4) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 1, j + 1) == aType //��б��
		&& ((board.getType(i - 1, j - 1) == bType) + (board.getType(i - 2, j - 2) == bType) + (board.getType(i - 3, j - 3) == bType) + (board.getType(i - 4, j - 4) == bType)) == k
		&& ((board.getType(i - 1, j - 1) == 0) + (board.getType(i - 2, j - 2) == 0) + (board.getType(i - 3, j - 3) == 0) + (board.getType(i - 4, j - 4) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i - 1, j + 1) == aType //��б��
		&& ((board.getType(i + 1, j - 1) == bType) + (board.getType(i + 2, j - 2) == bType) + (board.getType(i + 3, j - 3) == bType) + (board.getType(i + 4, j - 4) == bType)) == k
		&& ((board.getType(i + 1, j - 1) == 0) + (board.getType(i + 2, j - 2) == 0) + (board.getType(i + 3, j - 3) == 0) + (board.getType(i + 4, j - 4) == 0)) == 4 - k)

	{
		score[i][j] += (int)pow(10, k);
	}
	if (board.getType(i + 1, j - 1) == aType //��б��
		&& ((board.getType(i - 1, j + 1) == bType) + (board.getType(i - 2, j + 2) == bType) + (board.getType(i - 3, j + 3) == bType) + (board.getType(i - 4, j + 4) == bType)) == k
		&& ((board.getType(i - 1, j + 1) == 0) + (board.getType(i - 2, j + 2) == 0) + (board.getType(i - 3, j + 3) == 0) + (board.getType(i - 4, j + 4) == 0)) == 4 - k)
	{
		score[i][j] += (int)pow(10, k);
	}
}

//����ţ� ���
void AIPlayer::two(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j)
{
	if (board.getType(i, j) == 0 && board.getType(i, j + 1) == 0 && board.getType(i, j + 2) == type && board.getType(i, j + 3) == type && board.getType(i, j + 4) == 0 && board.getType(i, j + 5) == 0)
	{//��
		score[i][j] = 100;
		if (j + 1 < CHESS_SIZE)	{ score[i][j + 1] += 1000; }
		if (j + 4 < CHESS_SIZE)	{ score[i][j + 4] += 100; }
		if (j + 5 < CHESS_SIZE)	{ score[i][j + 5] += 1000; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j) == 0 && board.getType(i + 2, j) == type && board.getType(i + 3, j) == type && board.getType(i + 4, j) == 0 && board.getType(i + 5, j) == 0)
	{//��
		score[i][j] = 100;
		if (i + 1 < CHESS_SIZE)	{ score[i + 1][j] += 1000; }
		if (i + 4 < CHESS_SIZE)	{ score[i + 4][j] += 100; }
		if (i + 5 < CHESS_SIZE)	{ score[i + 5][j] += 1000; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j + 1) == 0 && board.getType(i + 2, j + 2) == type && board.getType(i + 3, j + 3) == type && board.getType(i + 4, j + 4) == 0 && board.getType(i + 5, j + 5) == 0)
	{//��б��
		score[i][j] = 100;
		if (i + 1 < CHESS_SIZE && j + 1 < CHESS_SIZE)	{ score[i + 1][j + 1] += 1000; }
		if (i + 4 < CHESS_SIZE && j + 4 < CHESS_SIZE)	{ score[i + 4][j + 4] += 100; }
		if (i + 5 < CHESS_SIZE && j + 5 < CHESS_SIZE)	{ score[i + 5][j + 5] += 1000; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j - 1) == 0 && board.getType(i + 2, j - 2) == type && board.getType(i + 3, j - 3) == type && board.getType(i + 4, j - 4) == 0 && board.getType(i + 5, j - 5) == 0)
	{//��б��
		score[i][j] = 100;
		if (i + 1 < CHESS_SIZE && j - 1 >= 0)	{ score[i + 1][j - 1] += 1000; }
		if (i + 4 < CHESS_SIZE && j - 4 >= 0)	{ score[i + 4][j - 4] += 100; }
		if (i + 5 < CHESS_SIZE && j - 5 >= 0)	{ score[i + 5][j - 5] += 1000; }
	}
}

//���ʮ�� ��  �� 
void AIPlayer::oneBone(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j)
{
	if (board.getType(i, j) == 0 && board.getType(i, j + 1) == type && board.getType(i, j + 2) == 0 && board.getType(i, j + 3) == type && board.getType(i, j + 4) == 0)
	{//��
		if (j + 2 < CHESS_SIZE)	{ score[i][j + 2] += 1000; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j) == type && board.getType(i + 2, j) == 0 && board.getType(i + 3, j) == type && board.getType(i + 4, j) == 0)
	{//��
		if (i + 2 < CHESS_SIZE)	{ score[i + 2][j] += 1000; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j + 1) == type && board.getType(i + 2, j + 2) == 0 && board.getType(i + 3, j + 3) == type && board.getType(i + 4, j + 4) == 0)
	{//��б��
		if (i + 2 < CHESS_SIZE && j + 2 < CHESS_SIZE)	{ score[i + 2][j + 2] += 1000; }
	}
	if (board.getType(i, j) == 0 && board.getType(i + 1, j - 1) == type && board.getType(i + 2, j - 2) == 0 && board.getType(i + 3, j - 3) == type && board.getType(i + 4, j - 4) == 0)
	{//��б��
		if (i + 1 < CHESS_SIZE && j - 1 > CHESS_SIZE)	{ score[i + 2][j - 1] += 1000; }
	}
}

//���ʮһ�� ��
void AIPlayer::one(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j)
{
	if (board.getType(i, j) == type && ((board.getType(i, j - 1) == 0) + (board.getType(i, j + 1) == 0) + (board.getType(i - 1, j) == 0) + (board.getType(i + 1, j) == 0)
		+ (board.getType(i + 1, j - 1) == 0) + (board.getType(i -1 , j + 1) == 0) + (board.getType(i - 1, j - 1) == 0) + (board.getType(i + 1, j + 1) == 0)) != 0)
	{
		if (j - 1 >= 0)	{ score[i][j - 1] += 100; }
		if (i - 1 >= 0)	{ score[i - 1][j] += 100; }
		if (j + 1 < CHESS_SIZE)	{ score[i][j + 1] += 100; }
		if (i + 1 < CHESS_SIZE)	{ score[i + 1][j] += 100; }
		if (i + 1 < CHESS_SIZE && j + 1 < CHESS_SIZE) { score[i + 1][j + 1] += 100; }
		if (i + 1 < CHESS_SIZE && j - 1 >= 0) { score[i + 1][j - 1] += 100; }
		if (j + 1 < CHESS_SIZE && i - 1 >= 0) { score[i - 1][j + 1] += 100; }
		if (i - 1 >= 0 && j - 1 >= 0) { score[i - 1][j - 1] += 100; }
	}
}