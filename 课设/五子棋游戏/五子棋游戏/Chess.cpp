#include "Chess.h"
#include "mmsystem.h" // 音乐播放
#pragma comment(lib, "winmm.lib")

Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
    this->gradeSize = gradeSize; // 棋盘大小
    this->margin_x = marginX;
    this->margin_y = marginY;
    this->chessSize = chessSize; // 棋子大小
    playerFlag = CHESS_BLACK;

    for (int i = 0; i < gradeSize; i++) {
        vector<int> row(gradeSize, 0);
        chessMap.push_back(row);
    }
}

IMAGE img;

void Chess::init()
{
    // 创建窗口
    initgraph(500, 500, EW_SHOWCONSOLE);

    // 显示棋盘
    loadimage(0, "E:\\code\\2025\\C++\\2025-college-grade2\\res\\qipan.jpg");

    // 播放开始提示音
    mciSendString("play res/start.wav", 0, 0, 0);

    // 加载棋子图片
    loadimage(&chessBlackImg, "E:\\code\\2025\\C++\\2025-college-grade2\\res\\black.jpg", chessSize, chessSize, true);
    loadimage(&chessWhiteImg, "E:\\code\\2025\\C++\\2025-college-grade2\\res\\white.jpg", chessSize, chessSize, true);

    // 清理棋盘
    for (int i = 0; i < gradeSize; i++) {
        fill(chessMap[i].begin(), chessMap[i].end(), 0);
    }

    playerFlag = CHESS_BLACK; // 初始玩家设为黑棋
}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
    int col = (x - margin_x) / chessSize;
    int row = (y - margin_y) / chessSize;
    int leftTopX = margin_x + chessSize * col;
    int leftTopY = margin_y + chessSize * row;
    int offset = chessSize * 0.4;

    bool ret = false;

    if (row >= 0 && row < gradeSize && col >= 0 && col < gradeSize) {
        // 检查点击的角落是否有效
        for (int dx = 0; dx <= 1; ++dx) {
            for (int dy = 0; dy <= 1; ++dy) {
                int checkCol = col + dx;
                int checkRow = row + dy;
                if (checkCol < gradeSize && checkRow < gradeSize) {
                    int cornerX = leftTopX + dx * chessSize;
                    int cornerY = leftTopY + dy * chessSize;
                    int len = sqrt((x - cornerX) * (x - cornerX) + (y - cornerY) * (y - cornerY));
                    if (len < offset && chessMap[checkRow][checkCol] == 0) {
                        pos->row = checkRow;
                        pos->col = checkCol;
                        ret = true;
                        break;
                    }
                }
            }
        }
    }

    return ret;
}

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
    int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
    int y = margin_y + chessSize * pos->row - 0.5 * chessSize;

    if (kind == CHESS_WHITE) {
        putimage(x, y, &chessWhiteImg);
    }
    else {
        putimage(x, y, &chessBlackImg);
    }

    // 更新游戏状态
    updateGameMap(pos);
}

int Chess::getGradeSize()
{
    return gradeSize;
}

int Chess::getChessData(ChessPos* pos)
{
    if (pos->row < 0 || pos->row >= gradeSize || pos->col < 0 || pos->col >= gradeSize) {
        return -1; // 无效位置
    }
    return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
    if (row < 0 || row >= gradeSize || col < 0 || col >= gradeSize) {
        return -1; // 无效位置
    }
    return chessMap[row][col];
}

//检查
bool Chess::checkOver()
{

    
    for (int i = 0; i < gradeSize; i++) {
        for (int j = 0; j < gradeSize; j++) {
            if (chessMap[i][j] != 0) {
                // Check horizontal
                if (j + 4 < gradeSize && chessMap[i][j] == chessMap[i][j + 1] &&
                    chessMap[i][j] == chessMap[i][j + 2] &&
                    chessMap[i][j] == chessMap[i][j + 3] &&
                    chessMap[i][j] == chessMap[i][j + 4]) {
                    return true;
                }

                // Check vertical
                if (i + 4 < gradeSize && chessMap[i][j] == chessMap[i + 1][j] &&
                    chessMap[i][j] == chessMap[i + 2][j] &&
                    chessMap[i][j] == chessMap[i + 3][j] &&
                    chessMap[i][j] == chessMap[i + 4][j]) {
                    return true;
                }

                // Check diagonal (top-left to bottom-right)
                if (i + 4 < gradeSize && j + 4 < gradeSize &&
                    chessMap[i][j] == chessMap[i + 1][j + 1] &&
                    chessMap[i][j] == chessMap[i + 2][j + 2] &&
                    chessMap[i][j] == chessMap[i + 3][j + 3] &&
                    chessMap[i][j] == chessMap[i + 4][j + 4]) {
                    return true;
                }

                // Check diagonal (top-right to bottom-left)
                if (i + 4 < gradeSize && j - 4 >= 0 &&
                    chessMap[i][j] == chessMap[i + 1][j - 1] &&
                    chessMap[i][j] == chessMap[i + 2][j - 2] &&
                    chessMap[i][j] == chessMap[i + 3][j - 3] &&
                    chessMap[i][j] == chessMap[i + 4][j - 4]) {
                    return true;
                }
            }
        }
    }
    return false; 
}

void Chess::updateGameMap(ChessPos* pos)
{

    if (chessMap[pos->row][pos->col] == 0) {
        chessMap[pos->row][pos->col] = playerFlag; 
        playerFlag = (playerFlag == CHESS_BLACK) ? CHESS_WHITE : CHESS_BLACK; 
    }
}
