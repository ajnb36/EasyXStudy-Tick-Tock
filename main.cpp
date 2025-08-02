#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <windows.h>

std::vector<std::vector<int> > whoUsed(3, std::vector<int>(3, -1));
int width = 800, height = 800;
int everyL = width / 3;
// 0表示圆，1表示x
int currentShape = 0;

// 检查圆或叉谁获胜
bool check(const int who) {
    if (who == whoUsed[0][0] && who == whoUsed[0][1] && who == whoUsed[0][2]) return true;
    if (who == whoUsed[1][0] && who == whoUsed[1][1] && who == whoUsed[1][2]) return true;
    if (who == whoUsed[2][0] && who == whoUsed[2][1] && who == whoUsed[2][2]) return true;
    if (who == whoUsed[0][0] && who == whoUsed[1][0] && who == whoUsed[2][0]) return true;
    if (who == whoUsed[0][1] && who == whoUsed[1][1] && who == whoUsed[2][1]) return true;
    if (who == whoUsed[0][2] && who == whoUsed[1][2] && who == whoUsed[2][2]) return true;
    if (who == whoUsed[0][0] && who == whoUsed[1][1] && who == whoUsed[2][2]) return true;
    if (who == whoUsed[0][2] && who == whoUsed[1][1] && who == whoUsed[2][0]) return true;
    return false;
}

// 检查是否平局
bool checkTie() {
    int flag = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (whoUsed[i][j] == -1) {
                flag = false;
                return flag;
            }
        }
    }
    return flag;
}

// 绘制棋子
void drawPiece() {
    for (int i = 0; i < whoUsed.size(); i++) {
        for (int j = 0; j < whoUsed[i].size(); j++) {
            if (whoUsed[i][j] == 1) {
                line(i * everyL, j * everyL, (i + 1) * everyL, (j + 1) * everyL);
                line((i + 1) * everyL, j * everyL, i * everyL, (j + 1) * everyL);
            }else if (whoUsed[i][j] == 0) {
                circle((i+0.5)*everyL, (j+0.5)*everyL, everyL/2);
            }
        }
    }
}


// 绘制棋盘
void drawBoard(int width, int height) {
    line(0, height / 3, width, height / 3);
    line(0, height / 3 * 2, width, height / 3 * 2);
    line(width / 3, 0, width / 3, height);
    line(width / 3 * 2, 0, width / 3 * 2, height);
}

// 绘制提示信息
void drawText() {
    static TCHAR text[64];
    char t = currentShape?'X':'O';
    _stprintf(text,  _T("当前棋子为:%c"), t);
    settextcolor(YELLOW);
    outtextxy(0, 0, text);
}

int main() {
    initgraph(width, height);
    BeginBatchDraw();
    drawText();
    drawBoard(width, height);
    FlushBatchDraw();


    int running = true;
    while (running) {
        DWORD begin = GetTickCount();
        ExMessage msg;
        while (peekmessage(&msg)) {
            if (msg.message == WM_LBUTTONDOWN) {
                int mouseX = msg.x, mouseY = msg.y;
                int indexX = mouseX / everyL, indexY = mouseY / everyL;
                if (whoUsed[indexX][indexY] == -1) {
                    whoUsed[indexX][indexY] = currentShape;
                    currentShape = !currentShape;
                }
            }
        }

        cleardevice();
        drawBoard(width, height);
        drawPiece();
        drawText();
        FlushBatchDraw();
        if (check(0)) {
            MessageBox(GetHWnd(), "圆获胜", "游戏结束", MB_OK);
            running = false;
        } else if (check(1)) {
            MessageBox(GetHWnd(), "叉获胜", "游戏结束", MB_OK);
            running = false;
        } else if (checkTie()) {
            MessageBox(GetHWnd(), "平局", "游戏结束", MB_OK);
            running = false;
        }

        DWORD end = GetTickCount();
        if (end - begin < 1000 / 60) {
            Sleep(1000 / 60 - end + begin);
        }

    }
    EndBatchDraw();
    return 0;
}
