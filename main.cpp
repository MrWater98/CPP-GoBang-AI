#include <iostream>
#include"Player.h"
#include"AIPlayer1.h"
#include<windows.h>
#include "GameController.h"
#include "Tools.h"
#include "AIPlayer1.h"
using namespace std;
int main()
{
    HideCursor();
    AIPlayer1 WhitePlayer(BLACK);
    Player BlackPlayer(WHITE);
    while(true)
    {
        BlackPlayer.Start();
        WhitePlayer.Start();
    }
    return 0;
}
