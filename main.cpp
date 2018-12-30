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
#pragma GCC optimize(2)
#include "GameController.h"
/*
int main()
{
    HideCursor();//hide the cursor 隐藏鼠标
    GameController c;//declare a GameController
    c.Game();//begin the game
    return 0;
}
*/
/*
using namespace std;
int main()
{
    HideCursor();
    AIPlayer4 BlackPlayer(BLACK);
    AIPlayer5 WhitePlayer(WHITE);
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
*/

