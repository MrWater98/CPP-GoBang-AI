#include "Tools.h"
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
void SetColor(int colorID)//设置文本颜色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}
