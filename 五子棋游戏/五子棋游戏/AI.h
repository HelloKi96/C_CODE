#pragma once
#include"Chess.h"
class AI
{
public:
	void init(Chess*chess);//��ʼ������
	void go();


private:
	Chess* chess;
	vector<vector<int>>scoreMap;


private:
	void calculateScore();//����ÿ��λ�õĵ÷�
	ChessPos think();

};

