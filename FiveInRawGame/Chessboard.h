#ifndef Chessboard_H
#define Chessboard_H
#include "Piece.h"

#define CHESS_SIZE 15

//棋盘类

class Chessboard {
public:
	Chessboard();
	~Chessboard();

	//获取相应位置的符号位置索引
	int getSymble(const int x, const int y);

	//获取相应位置点的状态type：0无落子；1黑子；2白子；
	int getType(const int x, const int y);

	//设置在相应位置放置棋子
	void setPiece(Piece& piece);


private:
	//记录每个位置的落子,初始为x=-1;y=-1;type=0;
	Piece pieceBoard[CHESS_SIZE][CHESS_SIZE];

	//棋盘
	//int (*symbleBoard)[CHESS_SIZE];//以索引形式记录每个位置应该显示什么符号

};

#endif