#include "AI.h"

void AI::init(Chess* chess)
{
	this->chess = chess;

	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++) {
		vector<int> row;
			for (int j = 0;j < size; j++) {
				row.push_back(0);
			}

			scoreMap.push_back(row);
	}
}

void AI::go()
{
	ChessPos pos = think();
	Sleep(1000);
	chess->chessDown(&pos, CHESS_WHITE);
}

//ai算分
void AI::calculateScore()
{
	int personNum = 0;//黑棋多少个连续的棋子
	int aiNum = 0;//白棋多少个连续的棋子
	int emptyNum = 0;//该方向上空白位的个数

	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap.size(); j++) {
			scoreMap[i][j] = 0;
		}
	}

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			personNum = 0;//每次循环前重置
			aiNum = 0;
			emptyNum = 0;

			//计算每个点的得分
			if (chess->getChessData(row, col) == 0) continue;

			for (int y = -1; y <= 1; y++) {
				for (int x = -1; x <= 1; x++) {
					if (x == 0 && y == 0) continue;

					//黑棋落在该位置，会构成哪些阵型：八个方向
					for (int i = 0; i <= 4; i++) {
						int curRow = row + y * i;
						int curCol = col + x * i;
						 
						if(curRow>=0&&curRow<size&&
							curCol>=0&&curCol<size&&
							chess->getChessData(curRow, curCol) == 1) {
							personNum++; 
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
						}
						else {
							break;
						}
					}

					if (personNum == 1) {
						scoreMap[row][col] += 10;
					}
					else if(personNum == 2) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 30;
						}
						else if(emptyNum == 2){ 
							scoreMap[row][col] += 40;
						}						
					}
					else if (personNum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] = 60;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] = 200;
						}

					else if (personNum == 4) {
							scoreMap[row][col] = 2000;
						}
					}

					//假设白棋落在此位置，会构成哪些棋型
					for (int i = 0; i < 4; i++) {
						int curRow = row + y * i;
						int curCol = col + x * i;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1) {
							aiNum++;
						}
						else if(curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}
						
					for (int i = 0; i < 4; i++) {
						int curRow = row - y * i;
						int curCol = col - x * i;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1) {
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}
					
					if (aiNum == 0) {
						scoreMap[row][col] += 5;

					}
					else if (aiNum == 1) {
						scoreMap[row][col] += 10;
					}
					else if (aiNum == 2) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 25;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 50;
						}						
					}
					else if (aiNum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 55;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 10000;
						}
					}
					else if (aiNum >= 4) {						
							scoreMap[row][col] += 30000;					
					}
				}
			}


			
		}
	}
}

ChessPos AI::think()//算分后思考
{
	calculateScore();

	vector<ChessPos>maxPoints;
	int maxScore = 0;
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (chess->getChessData(row,col) == 0) {
				if (scoreMap[row][col] > maxScore) {
					maxScore = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));

				}
				else if (scoreMap[row][col] == maxScore) {
					maxPoints.push_back(ChessPos(row, col));

				}
			}
		}
	}

	int index = rand() % maxPoints.size();//伪随机数
	return maxPoints[index];
}
