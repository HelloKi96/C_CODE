#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include"ChessGame.h"
using namespace std;

//1.�����Щ��
//
int main() {
	Man man;
	//Chess chess;
	Chess chess(15, 44, 43, 67.3);


	AI ai;
	ChessGame game(&man, &ai, &chess);

	game.play();

	return 0;
}