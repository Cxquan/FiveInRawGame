#ifndef AIPlayer_H
#define AIPlayer_H

#include "Chessboard.h"
#include "Judger.h"
#include "Piece.h"
#include <cmath>

class AIPlayer {
public:
	AIPlayer(int type);
	~AIPlayer();

	//���Ӻ���
	void placePiece(Chessboard& board, Piece& piece);
	//�������̷���������Ϊ����ܵ����
	Piece getMaxScorePiece(Chessboard& board, Judger& judger);

	//���һ�� �����
	void four(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade);
	//������� ���  ���  �� ��  ���� �� ����  ��
	void twoBtwo(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade);
	//������� ����
	void three(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade);
	//����ģ� ���  ����  ���
	void twoBone(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j, const int grade);
	
	//����壺 ���ա���������
	void twoBonePone(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k);
	//������� ��ա� ���������
	void oneBonePtwo(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k);
	//����ߣ� �����������ա�
	void twoPoneBone(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k);
	//����ˣ� ����������ա��
	void onePoneBtwo(Chessboard& board, int score[][CHESS_SIZE], const int aType, const int bType, const int i, const int j, const int k);
	//����ţ� ���
	void two(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j);
	//���ʮ�� ��  �� 
	void oneBone(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j);
	//���ʮһ�� ��
	void one(Chessboard& board, int score[][CHESS_SIZE], const int type, const int i, const int j);

private:
	int type;//�׷�
};

#endif