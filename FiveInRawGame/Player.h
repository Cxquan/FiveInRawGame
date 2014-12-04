#ifndef Player_H
#define Player_H

class Player {
public:
	Player(int type);
	~Player();

	int getType();

private:
	int type;//黑方or白方
	//记录悔棋数
	//记录下子数（禁手？）

};

#endif