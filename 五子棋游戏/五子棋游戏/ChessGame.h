#include "Man.h"
#include "AI.h"
#include "Chess.h"
#include<iostream>
using namespace std;
class ChessGame {
public:
    ChessGame(Man* man, AI* ai, Chess* chess);
    void play();

private:
    Man* man;
    AI* ai;
    Chess* chess;
};

// 人类玩家类的实现
void Man::init(Chess* chess) {
    this->chess = chess; // 关联棋盘
}

void Man::go() {
    ChessPos pos;

    // 假设这里有一个函数用于获取用户输入
    //while (true) {
    //    if (getUserInput(&pos)) { // 函数：getUserInput获取用户点击位置
    //        if (chess->getChessData(&pos) == 0) { // 检查该位置是否有效
    //            chess->chessDown(&pos, CHESS_BLACK); // 黑棋为人类
    //            break;
    //        }
    //    }
    //}
}


// AI 玩家类的实现
void AI::init(Chess* chess) {
    this->chess = chess; // 关联棋盘
}

void AI::go() {
    ChessPos pos;
    //// 假设AI的决策算法会产生一个棋步
    //pos = decisionAlgorithm(); // 该函数需要你自己实现，返回AI选择的位置

    //if (chess->getChessData(&pos) == 0) { // 检查该位置是否有效
    //    chess->chessDown(&pos, CHESS_WHITE); // 白棋为AI
    //}
}

// 对局（开始游戏）
//void ChessGame::play()
//{
//    chess->init(); // 初始化棋盘
//    while (true)
//    {
//        // 人先走棋
//        man->go();
//        if (chess->checkOver()) {
//            // 显示胜利信息或处理逻辑
//            cout << "人类获胜！" << endl;
//            chess->init(); // 初始化棋盘以便重新开始
//            continue;
//        }
//
//        // 电脑走棋
//        ai->go();
//        if (chess->checkOver()) {
//            // 显示胜利信息或处理逻辑
//            cout << "电脑获胜！" << endl;
//            chess->init(); // 初始化棋盘以便重新开始
//            continue;
//        }
//    }
//}
