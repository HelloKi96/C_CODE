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

// ����������ʵ��
void Man::init(Chess* chess) {
    this->chess = chess; // ��������
}

void Man::go() {
    ChessPos pos;

    // ����������һ���������ڻ�ȡ�û�����
    //while (true) {
    //    if (getUserInput(&pos)) { // ������getUserInput��ȡ�û����λ��
    //        if (chess->getChessData(&pos) == 0) { // ����λ���Ƿ���Ч
    //            chess->chessDown(&pos, CHESS_BLACK); // ����Ϊ����
    //            break;
    //        }
    //    }
    //}
}


// AI ������ʵ��
void AI::init(Chess* chess) {
    this->chess = chess; // ��������
}

void AI::go() {
    ChessPos pos;
    //// ����AI�ľ����㷨�����һ���岽
    //pos = decisionAlgorithm(); // �ú�����Ҫ���Լ�ʵ�֣�����AIѡ���λ��

    //if (chess->getChessData(&pos) == 0) { // ����λ���Ƿ���Ч
    //    chess->chessDown(&pos, CHESS_WHITE); // ����ΪAI
    //}
}

// �Ծ֣���ʼ��Ϸ��
//void ChessGame::play()
//{
//    chess->init(); // ��ʼ������
//    while (true)
//    {
//        // ��������
//        man->go();
//        if (chess->checkOver()) {
//            // ��ʾʤ����Ϣ�����߼�
//            cout << "�����ʤ��" << endl;
//            chess->init(); // ��ʼ�������Ա����¿�ʼ
//            continue;
//        }
//
//        // ��������
//        ai->go();
//        if (chess->checkOver()) {
//            // ��ʾʤ����Ϣ�����߼�
//            cout << "���Ի�ʤ��" << endl;
//            chess->init(); // ��ʼ�������Ա����¿�ʼ
//            continue;
//        }
//    }
//}
