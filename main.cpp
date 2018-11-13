#include <iostream>
#include"Player.h"
#include"AIPlayer1.h"
#include<windows.h>
#include "GameController.h"
#include "Tools.h"
using namespace std;
int main()
{
    HideCursor();
    Player BlackPlayer(BLACK);
    Player WhitePlayer(WHITE);
    while(true)
    {
        BlackPlayer.Start();
        WhitePlayer.AIStart();
    }
    return 0;
}
