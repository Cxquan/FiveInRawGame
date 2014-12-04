#ifndef Judger_H
#define Judger_H


class Judger {
public:
	Judger();
	~Judger();

	bool isValidPos(int x, int y);//
	bool isWin();
	bool isADraw();

};

#endif