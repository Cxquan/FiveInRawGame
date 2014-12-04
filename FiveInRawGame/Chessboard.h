#ifndef Chessboard_H
#define Chessboard_H
#include "Piece.h"

#define CHESS_SIZE 15

//������

class Chessboard {
public:
	Chessboard();
	~Chessboard();

	//��ȡ��Ӧλ�õķ���λ������
	int getSymble(const int x, const int y);

	//��ȡ��Ӧλ�õ��״̬type��0�����ӣ�1���ӣ�2���ӣ�
	int getType(const int x, const int y);

	//��������Ӧλ�÷�������
	void setPiece(Piece& piece);


private:
	//��¼ÿ��λ�õ�����,��ʼΪx=-1;y=-1;type=0;
	Piece pieceBoard[CHESS_SIZE][CHESS_SIZE];

	//����
	//int (*symbleBoard)[CHESS_SIZE];//��������ʽ��¼ÿ��λ��Ӧ����ʾʲô����

};

#endif