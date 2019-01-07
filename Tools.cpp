#include "Tools.h"
#include<string.h>
void HideCursor()// hide the cursor
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO myCursorInfo;
    GetConsoleCursorInfo(handle,&myCursorInfo);
    myCursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle,&myCursorInfo);
}
void SetCursorPos(pair<short,short> pos)//Set the cursor position
{
    COORD Pos;
    Pos.X = 2*pos.first;
    Pos.Y = pos.second;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
}
void SetColor(int colorID)//Set the background color
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}
void copyArray(char cloneChessboard[15][15],char temp[15][15])
{
    memcpy(temp,cloneChessboard,15*15*sizeof(char));
}

void SetWindowSize(int cols, int lines)//set the windows size
{
    system("title FSTONE Author:Zheng Ziyue   Zhang Chenhao");//Set the title
    char cmd[30];
    sprintf(cmd, "mode con cols=%d lines=%d", cols * 2, lines);//One ■ Obtain two charater，So multiple two
    system(cmd);//system(mode con cols=88 lines=88)Set the windows size
}

void SetCursorPosition(const int x, const int y)//Set the cursor position
{
    COORD position;
    position.X = x * 2;
    position.Y = y-2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}



void SetBackColor()//Set the text background color
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_BLUE |
                            BACKGROUND_BLUE |
                            BACKGROUND_GREEN |
                            BACKGROUND_RED );
}
