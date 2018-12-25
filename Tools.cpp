#include "Tools.h"
#include<string.h>
void HideCursor()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO myCursorInfo;
    GetConsoleCursorInfo(handle,&myCursorInfo);
    myCursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle,&myCursorInfo);
}
void SetCursorPos(pair<short,short> pos)
{
    COORD Pos;
    Pos.X = 2*pos.first;
    Pos.Y = pos.second;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
}
void SetColor(int colorID)//ÉèÖÃÎÄ±¾ÑÕÉ«
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}
void copyArray(char cloneChessboard[15][15],char temp[15][15])
{
    /*
    for(int i = 0;i < 15;i++)
    {
        for(int j = 0;j < 15;j++)
        {
            temp[i][j] = cloneChessboard[i][j];
        }
    }*/
    memcpy(temp,cloneChessboard,15*15*sizeof(char));
}

//以下是从贪吃蛇里copy的东西
void SetWindowSize(int cols, int lines)//设置窗口大小
{
    system("title 贪吃蛇");//设置窗口标题
    char cmd[30];
    sprintf(cmd, "mode con cols=%d lines=%d", cols * 2, lines);//一个图形■占两个字符，故宽度乘以2
    system(cmd);//system(mode con cols=88 lines=88)设置窗口宽度和高度
}

void SetCursorPosition(const int x, const int y)//设置光标位置
{
    COORD position;
    position.X = x * 2;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}



void SetBackColor()//设置文本背景色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_BLUE |
                            BACKGROUND_BLUE |
                            BACKGROUND_GREEN |
                            BACKGROUND_RED );
}
