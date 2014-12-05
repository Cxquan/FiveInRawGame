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
			Piece currentPiece;
			//开始下棋
			while (true)//
			{
				//黑方下子1
				if (turn == 1)
				{
					currentPiece = getPieceInput(screener, board, bPlayer, judger);
					bPlayer.placePiece(board, currentPiece);
				}
				//白方下子2
				else
				{
					currentPiece = getPieceInput(screener, board, wPlayer, judger);
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
			Piece piece;
			//开始下棋
			while (true)//
			{
				//黑方下子1
				if (turn == 1)
				{
					piece = getPieceInput(screener, board, hmPlayer, judger);
					hmPlayer.placePiece(board, piece);
				}
				//白方(电脑)下子2
				else
				{
					piece = aiPlayer.getMaxScorePiece(board, judger);
					aiPlayer.placePiece(board, piece);
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

Piece Organizer::getPieceInput(Screener& screener, Chessboard& board, Player& player, Judger& judger)
{
	system("cls");
	screener.showBoard(board);

	string name = player.getType() == 1 ? "黑方" : "白方";
	cout << "请【" << name << "】输入落子坐标(e.g. 8 8)：";
	
	int x, y;
	cin >> x >> y;
	Piece piece(x, y, player.getType());

	//判断位置合规性、以及黑子否禁手
	while (cin.fail() || !judger.isValidPosition(board, piece)
		|| ((1 == player.getType()) ? judger.isForbidden(board, piece) : false))
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//忽略缓冲区中的多余输入

		cout << "====!输入错误，请重新输入!====" << endl;
		cout << "请【" << name << "】输入落子坐标(例: 8 10)：";
		cin >> x >> y;
		piece.setVal(x, y, player.getType());
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
		cout << "====!输入错误，请重新输入!====" << endl;
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
	cout << "双人对战模式(0);人机对战模式(1)" << endl;
	cout << "请选择游戏模式：";

	int m;

	cin >> m;
	while (cin.fail() || (m != 0 && m != 1))
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//忽略缓冲区中的多余输入

		cout << "====!输入错误，请重新输入!====" << endl;
		cout << "双人对战模式(0);人机对战模式(1)" << endl;
		cout << "请选择游戏模式：";
		cin >> m;
	}

	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//忽略缓冲区中的多余输入
	mode = m;
}