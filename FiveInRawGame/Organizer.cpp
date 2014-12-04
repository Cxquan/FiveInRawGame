#include "Organizer.h"
#include "AIPlayer.h"
#include "Judger.h"
#include "Chessboard.h"
#include "Screener.h"
#include "Piece.h"
#include "Player.h"

using namespace std;

Organizer::Organizer()
{
	turn = 1;
}

Organizer::~Organizer()
{
}

void Organizer::startGame()
{
	while (true)
	{
		Chessboard board;
		Screener screener;
		Judger judger;

		//选择模式
		getModeInput(screener, board);

		//双人对战
		if (mode == 0)
		{
			Player bPlayer(1);//黑方
			Player wPlayer(2);//白方

			//开始下棋
			while (true)//
			{
				//黑方下子
				if (turn == 1)
				{
					//getPieceInput();
					//bPlayer.placePiece();
				}
				//白方下子
				else
				{
					//getPieceInput();
					//wPlayer.placePiece();
				}
				
				//judger.isForbidden();

				//judger.isWin//平手判断？

			}
			
		}
		//人机对战
		else
		{
			Player hmPlayer(1);//人黑方
			AIPlayer aiPlayer(2);//电脑白方
			
			//黑方下子
			if (true == 1)
			{
				//getPieceInput();
				//hmPlayer.placePiece();
			}
			//白方下子
			else
			{
				//getPieceInput();
				//aiPlayer.placePiece();
			}

			//judger.isForbidden();

			//judger.isWin//平手判断？
		}

		//是否再玩一次
		if (!isPlayAgain(screener, board))
		{
			//showGoodBye();
			break;
		}
	}
}

bool Organizer::isPlayAgain(Screener& screener, Chessboard& board)
{
	system("cls");
	screener.showBoard(board);
	cout << "是否再来一盘？" << endl;
	cout << "是(y)/否(n):";
	char c;
	cin >> c;
	while (cin.fail() || (c != 'y' && c != 'n'))
	{
		cin.clear();
		cin.ignore();

		cout << endl;
		cout << "!!!输入错误，请重新输入!!!" << endl;
		cout << "是否再来一盘？" << endl;
		cout << "是(y)/否(n):";
		cin >> c;
	}
	if (c == 'y')
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Organizer::getModeInput(Screener& screener, Chessboard& board)
{
	system("cls");
	screener.showBoard(board);
	cout << "双人对战模式(0);人机对战模式(1)" << endl;
	cout << "请选择游戏模式：";

	int m;
	cin >> m;
	while (cin.fail() || (m != 0 && m != 1))
	{
		cin.clear();
		cin.ignore();

		cout << "!!!输入错误，请重新输入!!!" << endl;
		cout << "双人对战模式(0);人机对战模式(1)" << endl;
		cout << "请选择游戏模式：";
		cin >> m;
	}
	mode = m;
}