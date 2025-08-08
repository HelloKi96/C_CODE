#pragma once
#include<graphics.h>//easyx��ͼ�ο��ͷ�ļ�
#include<vector>  //����
using namespace std;
//����λ��
struct ChessPos
{
	int row;
	int col;

	ChessPos(int r=0,int c=0):row(r),col(c){}
};

typedef enum
{
	CHESS_WHITE = -1,//����
    CHESS_BLACK = 1//����
}chess_kind_t;
class Chess
{
public:
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);
	void init();//��ʼ������
	bool clickBoard(int x, int y, ChessPos* pos);//�������
	int getGradeSize();//��ȡ���̴�С:15*15
	int getChessData(ChessPos* pos);//��ȡ�������ݣ��ڣ��ף����ǿհ�
	int getChessData(int row, int col);// 
	bool checkOver();//�ж��Ƿ����

	//ʹ��ͼ�ο⣬��ʾ���̺�����
	//����easyx

private:
	IMAGE imgBoard;//����ͼƬ
	IMAGE chessBlackImg;//����ͼƬ
	IMAGE chessWhiteImg;//����ͼƬ
	
	int gradeSize;//���̴�С��15*15
	int margin_x;//�������߽�
	int margin_y;//�ϲ�߽�
	float chessSize;//���Ӵ�С������

	//���ӷֲ����ݣ�1���ڣ�-1���ף�0����
	//chessMap[3][4];//��ʾ��3�е�4�е���������
	vector<vector<int>>chessMap;//��ά����

	//���ڸ�˭����
	bool playerFlag;//true:�����ߣ�false:������

	//������������
	void updateGameMap(ChessPos* pos);
};

