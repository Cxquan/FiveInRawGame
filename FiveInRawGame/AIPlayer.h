#ifndef AIPlayer_H
#define AIPlayer_H


class AIPlayer {
public:
	AIPlayer(int type);
	~AIPlayer();
	int getType();

private:
	int type;//�ڷ�or�׷�
};

#endif