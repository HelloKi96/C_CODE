#include "ChessGame.h"
#include <iostream>

using namespace std;

// 构造函数
ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
    this->man = man;
    this->ai = ai;
    this->chess = chess;

    // 初始化人类玩家和AI与棋盘的关系
    man->init(chess);
    ai->init(chess);
}

// 对局（开始游戏）
void ChessGame::play()
{
    chess->init(); // 初始化棋盘
    while (true)
    {
        // 人先走棋
        cout << "人类玩家下棋：" << endl;
        man->go();
        if (chess->checkOver()) {
            cout << "人类获胜！" << endl;
            chess->init(); // 初始化棋盘以便重新开始
            continue;
        }

        // 电脑走棋
        cout << "电脑下棋：" << endl;
        ai->go();
        if (chess->checkOver()) {
            cout << "电脑获胜！" << endl;
            chess->init(); // 初始化棋盘以便重新开始
            continue;
        }
    }
}
