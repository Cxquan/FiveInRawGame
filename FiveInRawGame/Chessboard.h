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
	void setPiece(const Piece& piece);

	bool check(int x, int y);


private:
	//��¼ÿ��λ�õ�����,��ʼΪx=-1;y=-1;type=0;symble=*
	Piece **pieceBoard;

};

#endif