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
	turn = 1;//黑方先下
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
			Player currentPlayer;
			Piece currentPiece(-1, -1, 2);
			//开始下棋
			while (true)//
			{
				//黑方下子1
				if (turn == 1)
				{
					currentPiece = getPieceInput(screener, board, judger, currentPiece);
					bPlayer.placePiece(board, currentPiece);
				}
				//白方下子2
				else
				{
					currentPiece = getPieceInput(screener, board, judger, currentPiece);
					wPlayer.placePiece(board, currentPiece);
				}
				//判断是否胜利/平局
				currentPlayer = turn == 1 ? bPlayer : wPlayer;
				if (judger.isWin(board, currentPlayer))
				{
					screener.showWinerBoard(board, currentPlayer);
					break;
				}
				else if (judger.isaDraw(board))
				{
					screener.showDrawBoard(board);
					break;
				}
				turn = ++turn % 2;//轮流落子
			}			
		}

		//人机对战
		else
		{
			Player hmPlayer(1);//人黑方
			AIPlayer aiPlayer(2);//电脑白方
			Piece currentPiece(-1, -1, 2);
			//开始下棋
			while (true)//
			{
				//黑方下子1
				if (turn == 1)
				{
					currentPiece = getPieceInput(screener, board, judger, currentPiece);
					hmPlayer.placePiece(board, currentPiece);
				}
				//白方(电脑)下子2
				else
				{
					currentPiece = aiPlayer.getMaxScorePiece(board, judger);
					aiPlayer.placePiece(board, currentPiece);
				}
				//判断是否胜利/平局
				if (judger.isWin(board, turn))
				{
					screener.showWinerBoard(board, turn);
					break;
				}
				else if (judger.isaDraw(board))
				{
					screener.showDrawBoard(board);
					break;
				}
				turn = ++turn % 2;//轮流落子
			}
		}
		//是否再玩一次
		if (!isPlayAgain(screener, board))
		{
			//showGoodBye();
			break;
		}
	}
}

Piece Organizer::getPieceInput(Screener& screener, Chessboard& board, Judger& judger, const Piece& lastPiece)
{
	system("cls");
	screener.showBoard(board);
	
	string opo, name;
	int type;
	if (lastPiece.type == 1)
	{
		opo = "黑方";
		name = "白方";
		type = 2;
	}
	else
	{
		if (mode == 1)
		{
			opo = "电脑";
			name = "您";
			type = 1;
		}
		else
		{
			opo = "白方";
			name = "黑方";
			type = 1;
		}
	}
	if (lastPiece.x != -1)
	{
		cout << "【" << opo << "】落子于: " << lastPiece.x << " " << lastPiece.y << endl;
	}	
	cout << "请【" << name << "】输入落子坐标：";
	
	int x, y;
	cin >> x >> y;
	Piece piece(x, y, type);

	//判断位置合规性、以及黑子否禁手
	while (cin.fail() || !judger.isValidPosition(board, piece)
		|| ((1 == type) ? judger.isForbidden(board, piece) : false))
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//忽略缓冲区中的多余输入

		cout << "==== 输入错误，请重新输入 ====" << endl;
		cout << "请【" << name << "】输入落子坐标：";
		cin >> x >> y;
		piece.setVal(x, y, type);
	}

	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//忽略缓冲区中的多余输入
	return piece;
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
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//忽略缓冲区中的多余输入

		cout << endl;
		cout << "==== 输入错误，请重新输入 ====" << endl;
		cout << "是否再来一盘？" << endl;
		cout << "是(y)/否(n):";
		cin >> c;
	}
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//忽略缓冲区中的多余输入
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
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~~~ 欢迎进入五子棋对战 ~~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "您想参与哪个对战模式？" << endl;
	cout << "双人对战模式(0)/人机对战模式(1)：";

	int m;
	cin >> m;
	while (cin.fail() || (m != 0 && m != 1))
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//忽略缓冲区中的多余输入

		cout << "==== 输入错误，请重新输入 ====" << endl;
		cout << "您想参与哪个对战模式？" << endl;
		cout << "双人对战模式(0)/人机对战模式(1)：";
		cin >> m;
	}

	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//忽略缓冲区中的多余输入
	mode = m;
}