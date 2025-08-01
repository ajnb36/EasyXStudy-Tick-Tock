#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <vector>

int main() {
    int width = 800, height = 800;
    initgraph(width, height);
    BeginBatchDraw();
    // setlinecolor(WHITE);
    line(0, height / 3, width, height / 3);
    line(0, height / 3 * 2, width, height / 3 * 2);
    line(width / 3, 0, width / 3, height);
    line(width / 3 * 2, 0, width / 3 * 2, height);
    FlushBatchDraw();
    int r = width / 6;
    // 九个中心点
    std::vector<std::pair<int, int> > nineCenter = {
        {r, r}, {r * 3, r}, {r * 5, r},
        {r, r * 3}, {r * 3, r * 3}, {r * 5, r * 3},
        {r, r * 5}, {r * 3, r * 5}, {r * 5, r * 5},
    };
    std::vector<int> whoUsed(9, -1);
    // 0表示圆，1表示x
    int currentShape = 0;
    while (true) {
        ExMessage msg;
        while (peekmessage(&msg)) {
            // printf("等待指令");
            if (msg.message == WM_LBUTTONDOWN) {
                // printf("鼠标按下了");
                int mouseX = msg.x, mouseY = msg.y;
                for (int i = 0;i<9;i++) {
                    auto point = nineCenter[i];
                    if (mouseX <= point.first + r && mouseX >= point.first - r &&
                        mouseY <= point.second + r && mouseY >= point.second - r) {
                        if (whoUsed[i] == -1) {
                            if (currentShape) {
                                line(point.first - r / 2, point.second + r / 2, point.first + r / 2, point.second - r / 2);
                                line(point.first - r / 2, point.second - r / 2, point.first + r / 2, point.second + r / 2);
                            }else {
                                circle(point.first, point.second, r/2);
                            }
                            whoUsed[i] = currentShape;
                            currentShape = !currentShape;
                        }

                        FlushBatchDraw();
                        // 判断谁赢
                        // 判断横三或竖三一样
                        if (whoUsed[0] == whoUsed[1] && whoUsed[1] == whoUsed[2]) {
                            std::string who = whoUsed[0] == 0? "circle win":"fork win";
                            printf_s("%s\n", who.c_str());
                        }
                        break;
                    }
                }
            }
        }
    }
    EndBatchDraw();
    return 0;
}
