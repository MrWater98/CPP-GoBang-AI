#include <iostream>
#include"Player.h"
#include<windows.h>
#include "GameController.h"
#include "Tools.h"
#include "AIPlayer1.h"
#include "AIPlayer2.h"
#include "AIPlayer3.h"
#include "AIPlayer4.h"
#include "AIPlayer5.h"
#pragma GCC optimize(3)
#include "GameController.h"
/*
int main()//程序入口
{
    GameController c;//声明一个Controller类
    c.Game();//整个游戏循环
    return 0;
}
*/

using namespace std;
int main()
{
    HideCursor();
    AIPlayer5 BlackPlayer(BLACK);
    AIPlayer3 WhitePlayer(WHITE);
    while(true)
    {
        ChessBoard::getInstance()->print(pair<short,short>(0,0));
        BlackPlayer.Start();
        Sleep(200);
        system("cls");
        ChessBoard::getInstance()->print(pair<short,short>(0,0));
        WhitePlayer.Start();
        Sleep(200);
    }
    getchar();
    return 0;
}


