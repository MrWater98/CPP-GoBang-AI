#ifndef TOOLS_H
#define TOOLS_H
#include<iostream>
#include<windows.h>
using namespace std;
void HideCursor();
void SetCursorPos(pair<short,short> pos);
float getTotalScore(pair<short,short> p);
float getLineScore(pair<short,short> p,pair<short,short> offset);
#endif // TOOLS_H
