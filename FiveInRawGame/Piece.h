#ifndef Piece_H
#define Piece_H

class Piece {
public:
	Piece();
	~Piece();
	Piece(int x, int y, int type);
	Piece(int x, int y, int type, int symble);
	void setVal(int x, int y, int type);
	//void operator=(const Piece& Piece);
	//bool operator==(const Piece& Piece);

	int x;
	int y;
	int type;
	int symble;
};

#endif
