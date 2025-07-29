#include "ChessGame.h"
#include <iostream>

using namespace std;

// ���캯��
ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
    this->man = man;
    this->ai = ai;
    this->chess = chess;

    // ��ʼ��������Һ�AI�����̵Ĺ�ϵ
    man->init(chess);
    ai->init(chess);
}

// �Ծ֣���ʼ��Ϸ��
void ChessGame::play()
{
    chess->init(); // ��ʼ������
    while (true)
    {
        // ��������
        cout << "����������壺" << endl;
        man->go();
        if (chess->checkOver()) {
            cout << "�����ʤ��" << endl;
            chess->init(); // ��ʼ�������Ա����¿�ʼ
            continue;
        }

        // ��������
        cout << "�������壺" << endl;
        ai->go();
        if (chess->checkOver()) {
            cout << "���Ի�ʤ��" << endl;
            chess->init(); // ��ʼ�������Ա����¿�ʼ
            continue;
        }
    }
}
