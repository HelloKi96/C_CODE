#pragma once
#include"Chess.h"
class Man
{
public:
	void init(Chess* chess);
	void play();
	void go();

private:
	Chess* chess;
};

