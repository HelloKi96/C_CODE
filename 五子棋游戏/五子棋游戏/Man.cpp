#include "Man.h"

void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::play()
{
}

void Man::go()
{
	MOUSEMSG msg;//鼠标点击
	ChessPos pos;

	
	while (1) {
		//获取鼠标点击消息
		msg = GetMouseMsg();

		//通过chess,判断落子位置是否有效
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
			break;

		}
	}
	//落子
	chess->chessDown(&pos, CHESS_BLACK);
}
