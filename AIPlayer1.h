#ifndef AIPLAYER1_H
#define AIPLAYER1_H
#include "Player.h"
#include<map>
#include<cfloat>
using namespace std;
class AIPlayer1 : public Player
{
public:
    AIPlayer1(ChessType Color);
    float Score[15][15];
    void playChess();
    virtual ~AIPlayer1();
protected:
private:
};

#endif // AIPLAYER1_H
