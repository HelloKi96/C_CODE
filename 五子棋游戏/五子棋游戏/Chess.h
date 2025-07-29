#pragma once
#include<graphics.h>//easyx的图形库的头文件
#include<vector>  //容器
using namespace std;
//下棋位置
struct ChessPos
{
	int row;
	int col;

	ChessPos(int r=0,int c=0):row(r),col(c){}
};

typedef enum
{
	CHESS_WHITE = -1,//白棋
    CHESS_BLACK = 1//黑棋
}chess_kind_t;
class Chess
{
public:
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);
	void init();//初始化棋盘
	bool clickBoard(int x, int y, ChessPos* pos);//点击棋盘
	int getGradeSize();//获取棋盘大小:15*15
	int getChessData(ChessPos* pos);//获取棋子数据，黑，白，还是空白
	int getChessData(int row, int col);// 
	bool checkOver();//判断是否结束

	//使用图形库，显示棋盘和棋子
	//下载easyx

private:
	IMAGE imgBoard;//棋盘图片
	IMAGE chessBlackImg;//黑棋图片
	IMAGE chessWhiteImg;//白棋图片
	
	int gradeSize;//棋盘大小：15*15
	int margin_x;//棋盘左侧边界
	int margin_y;//上册边界
	float chessSize;//棋子大小：像素

	//棋子分布数据：1：黑，-1：白，0：空
	//chessMap[3][4];//表示第3行第4列的棋子数据
	vector<vector<int>>chessMap;//二维数组

	//现在该谁下棋
	bool playerFlag;//true:黑子走，false:白子走

	//更新棋子数据
	void updateGameMap(ChessPos* pos);
};

