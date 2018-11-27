#include <iostream>
#include"Player.h"
#include"AIPlayer1.h"
#include<windows.h>
#include "GameController.h"
#include "Tools.h"
#include "AIPlayer1.h"
#include "AIPlayer2.h"
#include "AIPlayer3.h"
using namespace std;
int main()
{
    HideCursor();
    Player BlackPlayer(BLACK);
    AIPlayer3 WhitePlayer(WHITE);

    while(true)
    {
        //ChessBoard::getInstance()->print(pair<short,short>(0,0));
        BlackPlayer.Start();
        //Sleep(200);
        //system("cls");
        //ChessBoard::getInstance()->print(pair<short,short>(0,0));
        WhitePlayer.Start();
        //Sleep(200);
    }
    return 0;
}
