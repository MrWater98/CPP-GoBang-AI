#include <iostream>
#include"Player.h"
#include"AIPlayer1.h"
#include<windows.h>
#include "GameController.h"
#include "Tools.h"
#include "AIPlayer1.h"
#include "AIPlayer2.h"
using namespace std;
int main()
{
    HideCursor();
    AIPlayer2 WhitePlayer(WHITE);
    Player BlackPlayer(BLACK);
    while(true)
    {
        BlackPlayer.Start();
        WhitePlayer.Start();
    }
    return 0;
}
