#ifndef TOOLS_H
#define TOOLS_H
#include<iostream>
#include<windows.h>
using namespace std;
void HideCursor();
void SetCursorPos(pair<short,short> pos);
float getTotalScore(pair<short,short> p);
float getLineScore(pair<short,short> p,pair<short,short> offset);
void SetColor(int colorID);//设置文本颜色
#endif // TOOLS_H
