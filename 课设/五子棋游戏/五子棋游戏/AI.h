#pragma once
#include"Chess.h"
class AI
{
public:
	void init(Chess*chess);//初始化棋盘
	void go();


private:
	Chess* chess;
	vector<vector<int>>scoreMap;


private:
	void calculateScore();//计算每个位置的得分
	ChessPos think();

};

